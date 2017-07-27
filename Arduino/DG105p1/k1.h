#define swue 12
#define swsita 11
#define swmigi 10
#define swhidari 9


//ポート初期化用
void portSetup(void){
  pinMode(2,INPUT);//INT
  pinMode(3,OUTPUT);//バックライト
  pinMode(4,OUTPUT);//LCDPOWER
  pinMode(5,OUTPUT);//ORANGELED
  pinMode(6,OUTPUT);//BLUELED
  pinMode(7,OUTPUT);//焦電リレー
  pinMode(8,OUTPUT);//ブザー
  pinMode(A3,INPUT);//焦電センサー入力
  pinMode(A2,INPUT);//光センサー入力
  pinMode(A1,INPUT);//温度センサー
  pinMode(A0,INPUT);//距離センサー
  pinMode(12,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}
//RTC時刻設定用関数
void rtcLcd(void){
  //各種変数
  char Year1 =0;
  char Year2 =0;
  char Mon1 = 0;
  char Mon2 = 0;
  char mDay1 = 0;
  char mDay2 = 0;
  char wDay = 0;
  char Hour = 0;
  char Min = 0;
  char Sec = 0;
  char cur = 3;
  //本文はここから
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  GLCD_Puts("RTCを初期化します\n");
  talk.SyntheP(PSTR("koreyo'ri/a-ruthi-shi'-o/sho'_ki/kashima'_su."));
  delay(500);
  //日付設定
  talk.SyntheP(PSTR("hizukeo/_shitei_shite/kudasa'i."));
top:
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  GLCD_Puts("日付を設定    してください\n");
  GLCD_Puts("20_");
  GLCD_PrintNumber(Year1);
  GLCD_PrintNumber(Year2);
  GLCD_Puts("年");
  GLCD_PrintNumber(Mon1);
  GLCD_PrintNumber(Mon2);
  GLCD_Puts("月");
  GLCD_PrintNumber(mDay1);
  GLCD_PrintNumber(mDay2);
  GLCD_Puts("日");
  while(1){
    //カーソル位置
    if( digitalRead(swmigi) == LOW){
      cur = cur + 1;
      if(cur == -1){
        cur = ;
      }
      
      


    if( digitalRead(swue) == LOW ){
      Year1 = Year1 + 1;
      if( Year1 == 10){
        GLCD_CursorTo(3,1);
        GLCD_PrintNumber(Year1);
        delay(100);
      }
    }
  }  
}

void opening(void){
  portSetup();
  delay(10);
  GLCD_Init(NON_INVERTED);
  delay(10);
  GLCD_ClearScreen();
  GLCD_DrawBitmap(gearLogo,0,0,BLACK);
  delay(10);
  talk.SyntheP(PSTR("_shisutemuche'xtu_ku _suta'-to."));
  delay(1500);
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  if(talk.IsActive() == false){
    GLCD_Puts("音声合成LSI エラーを確認\n");
    GLCD_Puts("システムを停止します\n");
    while(1){
    }//無限ループにより機能停止
  }
  else{
    GLCD_Puts("音声合成LSIチェック 正常\n");
    talk.SyntheP(PSTR("eruesuaichextu_kukuri'a."));
    delay(1500);
  }
  //EEPROM初期設定
  char romcheck[] = {
    105  };
  byte ans;
  ans = rom.Write(0,romcheck,1);
  if(ans == 0){
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/raitoche'xtu_ku kuri'a. "));
    GLCD_Puts("EEPROM書きこみ　成功\n");
    delay(2000);
  }
  else{
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/raitoche'xtu_ku fe'iru. "));
    GLCD_Puts("EEPROM書きこみ　失敗\n");
    GLCD_Puts("システムを停止します\n");
    while(1){
    }
  }
  ans = rom.Read(0,romcheck,1);
  if(ans == 0){
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/ri-doche'xtu_ku kuri'a. "));
    GLCD_Puts("EEPROM読みこみ　成功\n");//GLCD三行目
    delay(2000);
  }
  else{
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/ri-doche'xtu_ku fe'iru. "));
    GLCD_Puts("EEPROM読みこみ　失敗\n");
    GLCD_Puts("システムを停止します\n");
    while(1){
    }
  }


}







