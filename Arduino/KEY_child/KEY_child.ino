#include <rom_adv.h>
#include <Servo.h>
#include <EEPROM.h>

const int openAngle = 90;
const int closeAngle = 0;
String tmpStr;
Servo servo;
long x;
long def = 944;
int nok_count = 0;
long nok_start_time = 0;
int nok_mili_second = 5000;
int cc[80] = {};
int def_av_count = 80;
int average_stack = 0;
int average = 0;
long counts = 0;
int tt = 0;
int noc_true_counts = 0;
int noc_false_counts = 0;
//nok_type 
//0は学習モード
//1は解錠モード
int nok_type = 1;
long time_array[10] = {};
int time_array_count = 0;
long eeprom_data[10] = {};
int after_time_array[10] = {};
rom_adv rom(1024);

void reset(){
   nok_count = 0;
   nok_start_time = 0;
   counts = 0;
   tt = 0;
   noc_true_counts = 0;
   noc_false_counts = 0;
   time_array_count = 0;
   average = 0;
   for (int uu = 0 ; uu < 9 ; uu++) {
     time_array[uu] = 0; 
   }

   for (int rr = 0 ; rr < 9 ; rr++) {
     after_time_array[rr] = 0; 
   }

   //setup();
}

void reset_eeprom(){

  //リセット
  for (int i = 0 ; i < 256 ; i++) {
    EEPROM.write(i, 0);
  }
}

void write_eeprom(int wed[10]){
  int o = 0;
  int cct = 0;
  int losc;
  reset_eeprom();
  for (losc = 0; losc < 9 ; losc++) {
    rom.l_Write(wed[losc],cct);
    cct  = 3 +cct;
    delay(500);
  }

}

void read_eeprom(){
   for (int ii = 0 ; ii < 9 ; ii++) {
     eeprom_data[ii] = 0; 
   }
  int h, l, ret;
  l = 0;
  h = 0;
  for (l = 0 ; l < 256 ; l = 3+l){
    ret = rom.l_Read(l);
    delay(5);
    Serial.println(ret);
    if(ret >= 1){
      eeprom_data[h++] = ret;
    }else{
      break;
    }
  }
  
}


int check_nok(){
  while(true){
    //終了時間を確認するロジック
    if (nok_start_time > 0)
    {
      //現在時刻から開始時刻を引いて経過時間を算出して、期限時間（nok_mili_second）以上の場合終了させる
      if ( (millis()-nok_start_time) >= nok_mili_second )
      {
          for (int i = 0 ; i < nok_count -1 ; i++){

            after_time_array[i] = time_array[i+1] - time_array[i];
            Serial.println(after_time_array[i]);
        } 
          return 1;
      }
    }
    


   x = analogRead(A5) ; // Ｘ軸
   if (x > def){
      if(counts == def_av_count -1){
        counts = 0;

        for (int pyy = 0; pyy < def_av_count ; pyy++) {
          average_stack += cc[pyy];
          cc[pyy] = 0;
        }
        average = (average_stack/def_av_count);
        average_stack = 0;

        //Serial.println(average);
        if(average >= 40){
          //一回目の時にタイムスタートを入れる
          if (nok_count == 0)
          {
            nok_start_time =  millis();
            time_array[nok_count]  =  millis();
          }else{
            //ノックがあった時間を入れる
            time_array[nok_count]  =  millis();
          }
          
          if (nok_count == 9)
          {
            return 0;
          }

          nok_count++;
        }

      }else{
        cc[counts] = (x-def);
        counts ++;
      }

   }else{
    //Serial.println(0);
   }
  }
}
int  noc_learning(){
    while(true){
      if(check_nok() == 1){
        break;
      }
    }
    
    //学習させる
    
    if (after_time_array[0] == 0){
    }else{

      //学習データを保存させる
      write_eeprom(after_time_array);
      //解錠モードにする
      nok_type = 1;
      read_eeprom();
      //リセットする
      reset();
      return 1;
    }
}
int noc_open(){

    noc_true_counts = 0;
    noc_false_counts = 0;

   for (int pp = 0 ; pp < 9 ; pp++){
      Serial.println(eeprom_data[pp]);
    }

    //解錠モード
    //Serial.println("解錠モード");
    //ノックを取得する
    while(true){
      if(check_nok() == 1){
        break;
      }
    }

    //正しい解錠パターンとノックを比較する
    for (int i = 0 ; i < 9 ; i++){
      tt = eeprom_data[i];
      //Serial.println(tt);
      if(tt > 0){
          if(abs(tt - after_time_array[i]) < 500){
             noc_true_counts ++;
          }else{
             noc_false_counts ++;
          }
      }

    }

    if ( (((double) noc_true_counts / (double) (noc_true_counts + noc_false_counts))* 100)  > (double)70){
      //Serial.println("解錠");
      reset();
      return 1;
    }else{
      reset();
    }
    
  
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);
  servo.attach(8);
  servo.write(openAngle);
  delay(2000);
  servo.detach();
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);
  if(nok_type == 0){

  }else{
    //解錠モード
    
    //解錠パターンをEEPROMから取得する
    read_eeprom();
  }
  
  
  
}

void loop() {
  if ( Serial.available() > 0 ) {
    tmpStr = Serial.readStringUntil(0x3f);
    if(tmpStr == "open"){
      servo.attach(8);
      servo.write(openAngle);
      delay(2000);
      servo.detach();
    }
    if(tmpStr == "close"){
      servo.attach(8);
      servo.write(closeAngle);
      delay(2000);
      servo.detach();
    }
    if(tmpStr == "regist"){
      if(noc_learning() == 1){
        digitalWrite(9,HIGH);
        delay(2000);
        digitalWrite(9,LOW);
      }
    }
  }

  if(noc_open() == 1){
    servo.attach(8);
      servo.write(openAngle);
      delay(2000);
      servo.detach();
  }  
}
