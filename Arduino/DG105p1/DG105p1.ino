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
  rtcLcd();
  
  
}

void loop(){

}
