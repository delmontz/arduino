#include <Watchdog.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <Wire.h>

RF24 radio(9, 10);
//グローバル変数
int time = 11; //カーテン開け閉め時間(秒)
byte date = 0;
void do_sleep(void);
WatchdogClass WD = WatchdogClass();
bool done = false;
bool repeat = true;
void moter();
void setRepeat();

void do_sleep(void)
{
  // sets mcu sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // sleep mcu
  sleep_enable();
  sleep_mode();

  // wake mcu and radio upon watchdog timeout
  sleep_disable();
  radio.powerUp();
}
void setup(void)
{
  WD.systemResetEnable(false);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(5, HIGH);
  // 通信開始
  radio.begin();
  //速度
  radio.setDataRate(RF24_250KBPS);
  // リトライ回数の設定
  radio.setRetries(15, 15);
  // 書き込み用のパイプを開く
  radio.openWritingPipe(0xF0F0F0F0D2LL);
  // 読み込み用のパイプを開く
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);

  radio.startListening();
}
void loop() {
  WD.attachInterrupt(setRepeat);
  WD.enable(WatchdogClass::TimeOut500ms);
  radio.startListening();
  while (repeat) {
    moter();
  }
  repeat = true;
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  WD.enable(WatchdogClass::TimeOut4s);
  radio.powerDown();
  do_sleep();
}
void moter() {
  done = false;
  if (radio.available()) {
    radio.stopListening();
    setRepeat();
    while (!done) {
      done = radio.read( &date, 1);
      delay(20);
    }
  }
  if (date == 3) {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    delay(time * 1000);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  } else if (date == 2) {
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    delay(time * 1000);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }
  date = 0;
}
void setRepeat() {
  repeat = false;
  WD.disable();
  WD.detachInterrupt();
}

