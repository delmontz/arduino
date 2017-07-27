#include <Wire.h>
#include <skRTClib.h>
#include <skMC24xxx.h>
#include <ks0108w.h>
#include <AquesTalk.h>
#include <ArduinoIcon.h>

//******************************************
//定数設定
//********************************************
#define swue 12
#define swsita 11
#define swmigi 10
#define swhidari 9
#define orled 5
#define blled 6

//*******************************************
//グローバル変数
//********************************************
 char cur = 0;
 int val1 = 0;
 int val2 = 0;
 int avr = 0;
 int counter  = 0;
 
 


//各種ライブラリの初期設定みたいな
//てかインスタンス
AquesTalk talk;
skMC24xxx rom(0,0,0);
//外部ヘッダーファイルを読み込むおまじない、てかなんだよこれ
extern "C" {
  #include "k1_function.h"
  #include "k1_sub.h"
}

//以降本文
void setup(){
  //オープニング
  portSetup();
  delay(10);
  GLCD_Init(NON_INVERTED);
  delay(10);
  GLCD_ClearScreen();
  //焦電センサーON
  digitalWrite(7,HIGH);
  Serial.begin(9600);
  avr = analogRead(A2) - 100;

  GLCD_DrawBitmap(gearLogo,0,0,BLACK);
  delay(10);
  rtcLcd();
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  GLCD_Puts("システムチェッククリア");
  talk.SyntheP(PSTR("_shisutemuchekkuo-ruguri'-nn"));
  delay(1000);
  GLCD_ClearScreen();
  GLCD_DrawBitmap(gearLogo,0,0,BLACK);
  delay(2000);
  GLCD_DrawBitmap(dg105,0,0,BLACK);
  talk.SyntheP(PSTR("nichijo-gaje'tto da'i/_hito'maru/<NUMK VAL=5 COUNTER=go'-ki MODE=AaA> kido-  "));
  delay(8000);

  //メイン
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  GLCD_Puts("画面に向かって手をふってね\n");
  GLCD_Puts("動きに反応してLEDが光るよ！\n");
  GLCD_Puts("ガジェット上部に手を当てると。。\n");
  talk.SyntheP(PSTR("nama+i yu'-_su/keyo-/demoshi'_sutemuo/kido-shima'_su"));
  delay(1000);
  talk.SyntheP(PSTR("te'o/futtekudasa'i,ugoki'ni/hannno-_shite,erui'-dhi-ga/tennto-shima'_su"));
  talk.SyntheP(PSTR("mata gajettojo'-buni/te'o/atetekudasa'i"));
  
  //mainMenu();
    
}


void loop(){
  val1 = analogRead(A3);    
  val2 = analogRead(A2);
  Serial.println(val2);
  delay(500);
  if(val1 > 0){
  digitalWrite(5,HIGH);
  delay(500);
  }
  if(val1 == 0){
  digitalWrite(5,LOW);
  }
  if(counter == 2){
  avr = analogRead(A2) - 100; 
  counter = 0;
  }
  
  if( avr > analogRead(A2)){
  digitalWrite(6,HIGH);
  GLCD_ClearScreen();
  talk.SyntheP(PSTR("nama/iku'nn tennsai kakkoi'i"));
  GLCD_DrawBitmap(namai,0,0,BLACK);
  delay(2500);
  digitalWrite(6,LOW);
  GLCD_DrawBitmap(unko,0,0,BLACK);
  
  }
  
  counter++;
  
  
  
    
}
