#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#include <Wire.h>
RF24 radio(9,10);
void setup() {
  pinMode(2,INPUT);
  // 通信開始
  radio.begin();

  // リトライ回数の設定
  radio.setRetries(15,15);

  // 書き込み用のパイプを開く
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  // 読み込み用のパイプを開く
  radio.openReadingPipe(1, 0xF0F0F0F0D2LL);
}
byte button;
void loop() {
  if(digitalRead(2) == HIGH){
    button = 1;
  }else{
    button = 0;
  }
  if(radio.write( &button,1)){
    delay(500);
  }
}
