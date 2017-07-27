/*******************************************************************************
*  MC24.pde - EEPROM(24LC256)を使った読み書きテストサンプル                    *
*                                                                              *
* ============================================================================ *
*  VERSION DATE        BY                    CHANGE/COMMENT                    *
* ---------------------------------------------------------------------------- *
*  1.00    2012-01-26  きむ茶工房(きむしげ)  Create                            *
*******************************************************************************/
#include <Wire.h>
#include <skMC24xxx.h>

skMC24xxx MEM(0,0,0) ;        // EEPROM関数の生成を行う(A0/A1/A2端子は全てGNDに配線)

/*******************************************************************************
*  電源起動時とリセットの時だけのみ処理される関数(初期化と設定処理)            *
*******************************************************************************/
void setup()
{
     Serial.begin(9600) ;     // シリアル通信の初期化
}
/*******************************************************************************
*  繰り返し実行される処理の関数(メインの処理)                                  *
*******************************************************************************/
void loop()
{
     int  ans ;
     char dt1[4], dt2[4] ;

     dt1[0] = 1 ;
     dt1[1] = 2 ;
     dt1[2] = 3 ;
     // EEPROMの0番地から３バイト書き込む
     ans = MEM.Write(0x00,dt1,3) ;
     if (ans == 0) {
          Serial.println("EEPROM Write Success") ;
     } else {
          Serial.print("EEPROM Write Error ans=") ;
          Serial.println(ans) ;
     }
     // EEPROMの0番地から３バイト読み出す
     ans = MEM.Read(0x00,dt2,3) ;
     if (ans == 0) {
          Serial.print(dt2[0],HEX) ;
          Serial.print(' ') ;
          Serial.print(dt2[1],HEX) ;
          Serial.print(' ') ;
          Serial.print(dt2[2],HEX) ;
     } else {
          Serial.print("EEPROM Read Error ans=") ;
          Serial.println(ans) ;
     }
     while(1) ;               // 処理中断
}
