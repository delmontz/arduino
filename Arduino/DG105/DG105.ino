#include <Wire.h>
#include <skRTClib.h>
#include <skMC24xxx.h>
#include <ks0108w.h>
#include <AquesTalk.h>
#include <k1.h>
#include <ArduinoIcon.h>
//各種ライブラリの初期設定みたいな
//てかインスタンス
AquesTalk talk;
skMC24xxx rom(0,0,0);
//外部ヘッダーファイルを読み込むおまじない、てかなんだよこれ
extern "C" {
  #include "k1.h"　
}
//以降本文
void setup(){
  portSetup();
  delay(10);
  GLCD_Init(NON_INVERTED);
  delay(10);
  GLCD_ClearScreen();
  GLCD_DrawBitmap(gearLogo,0,0,BLACK);
  delay(10);
  talk.SyntheP(PSTR("_shisutemuche'xtu_ku _suta'-to."));
  delay(2000);
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  if(talk.IsActive() == false){
    GLCD_Puts("音声合成LSI エラーを確認\n");
    GLCD_Puts("システムを停止します\n");
    while(1){}//無限ループにより機能停止
  }else{
  GLCD_Puts("音声合成LSIチェック 正常\n");
  talk.SyntheP(PSTR("eruesuaichextu_kukuri'a."));
  delay(2000);
  }
  char romcheck[] = {105};
  byte ans;
  ans = rom.Write(0,romcheck,1);
  if(ans == 0){
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/raitoche'xtu_ku kuri'a. "));
    GLCD_Puts("EEPROM書きこみ　成功\n");
    delay(2000);
  }else{
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/raitoche'xtu_ku fe'iru. "));
    GLCD_Puts("EEPROM書きこみ　失敗\n");
    GLCD_Puts("システムを停止します\n");
    while(1){}
  }
  ans = rom.Read(0,romcheck,1);
  if(ans == 0){
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/ri-doche'xtu_ku kuri'a. "));
    GLCD_Puts("EEPROM読みこみ　成功\n");//GLCD三行目
    delay(2000);
  }else{
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/ri-doche'xtu_ku fe'iru. "));
    GLCD_Puts("EEPROM読みこみ　失敗\n");
    GLCD_Puts("システムを停止します\n");
    while(1){}
  }
  digitalWrite(7,HIGH); //焦電センサON
  
   
  
  
  

  
  
}

void loop(){
  if(analogRead(A3) > 100){
    digitalWrite(5,HIGH);
    delay(500);
    digitalWrite(5,LOW);
  }
  if(digitalRead(12) == LOW ){
    digitalWrite(6,HIGH);
  }else{
    digitalWrite(6,LOW);
  }
}
