/*******************************************************************************
*  Repeat.pde - ＲＴＣ－８５６４ＮＢを使ったテストサンプル                     *
*                                                                              *
*  delay(1000)1秒毎で自己ループしてそのタイミングでRTCから時刻を読み取って表示 *
*  アラーム機能も起動から１分後に出力、さらに１分後にアラーム機能停止          *
* ============================================================================ *
*  VERSION DATE        BY                    CHANGE/COMMENT                    *
* ---------------------------------------------------------------------------- *
*  1.00    2012-01-15  きむ茶工房(きむしげ)  Create                            *
*******************************************************************************/
#include <Wire.h>
#include <skRTClib.h>


/*******************************************************************************
*  電源起動時とリセットの時だけのみ処理される関数(初期化と設定処理)            *
*******************************************************************************/
void setup()
{
     int ans ;

     Serial.begin(9600) ;                    // シリアル通信の初期化
     ans = RTC.begin(0,12,1,10,2,15,30,0) ;  // 2012/01/10 火 15:30:00 でRTCを初期化する
     if (ans == 0) {
          Serial.println("Successful initialization of the RTC") ;// 初期化成功
     } else {
          Serial.print("Failed initialization of the RTC ans=") ; // 初期化失敗
          Serial.println(ans) ;
          while(1) ;                         // 処理中断
     }
     RTC.SetAlarm(15,31,0xff,0xff) ;         // アラームを１分後に設定する
}
/*******************************************************************************
*  繰り返し実行される処理の関数(メインの処理)                                  *
*******************************************************************************/
void loop()
{
     byte tm[7] ; 
     char buf[24] ;

     RTC.rTime(tm) ;                         // RTCから現在の日付と時刻を読込む
     RTC.cTime(tm,(byte *)buf) ;             // 日付と時刻を文字列に変換する
     Serial.println(buf) ;                   // シリアルモニターに表示
     if ((tm[1]==0x32)&&(tm[0]==0x00)) {     // ３２分になったら機能終了
            RTC.StopAlarm() ;                // アラーム機能終了し無効にする
     }
     delay(1000) ;                           // １秒後に繰り返す
}
