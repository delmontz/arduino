#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#include <Wire.h>
//グローバル変数
byte date[16];
byte tmp;
bool done = false;

//プロトタイプ宣言
void sendDate();
void CheckMan();
void checkLight();
//RF24コンストラクター
RF24 radio(9,10);


void setup(){
  Serial.begin(9600);
  Wire.begin(0x04);
  Wire.onRequest(sendDate);
  Wire.onReceive(resDate);
//  // 通信開始
//  radio.begin();
//  //出力最大
//  radio.setPALevel( RF24_PA_MAX );
//  //速度
//  radio.setDataRate(RF24_250KBPS);
//  //リトライ回数
//  radio.setRetries(15,15);
//  //書き込みパイプ
//  radio.openWritingPipe(0xF0F0F0F0E1LL);
//  //読み込みパイプ
//  radio.openReadingPipe(1,0xF0F0F0F0D2LL);
//  //発信まで節電
//  radio.powerDown();
  //光センサーアナログ3
  date[1] = 0;
}

void sendDate(){
  Wire.write(date,16);
  date[1] = 0;
}
void resDate(int b){
  while(Wire.available() > 0){
    tmp = Wire.read();
  }
//  //カーテン開閉機能
//  if(tmp == 3 || tmp == 4){
//    done = radio.write(&tmp,1);
//    date[0] = done;
//    if(date[0] == 1){
//      radio.powerDown();
//    }
//  }
  //ドアロック
  if(tmp == 5){
    Serial.print("open?");
  }else if(tmp == 6){
    Serial.print("close?");
  }else if(tmp == 7){
    Serial.print("regist?");
  }
}
void checkLight(){
  if(analogRead(A3) > 50){
    date[1] = 1;
  }else{
    date[1] = 0;
  }
}
void  loop(){
  checkLight();
}


