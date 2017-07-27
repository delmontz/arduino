#include "arduino.h"
#include "IRrecive.h"

// IRreciveインスタンス初期化
IRrecive::IRrecive( unsigned char IR_PIN_ , unsigned char codeNum_  ,  unsigned char DATA_POINT_ , unsigned char * testByte_ )
 {
  // private変数に導入
  IR_PIN_Int = IR_PIN_ ;              // IR接続ピン
  //IRbyte_Int = IRbyte_ ;           // 受信バイトバッファ（ポインタ）
  testByte_Int = testByte_ ;        // 固定バイト照合データ（ポインタ）
  codeNum_Int = codeNum_ ;      // リモコンの固有バイト照合数
  DATA_POINT_Int =  DATA_POINT_ ;  // 受信するデータのデータ位置
}

// メソッドread
// 受信バッファの読み出し
unsigned char IRrecive::read(int count) {
  return(IRbyte[count]) ;
}

// メソッドtest
// 機種照合と制御データ抽出 、受信した制御データを返す
// 0x100 受信したが機種照合できず
unsigned int IRrecive::test(void) {
  unsigned char test = 0 ;
  unsigned int recData = 0x100 ;

  if (byteCount > 0) {              // 受信あり
    for (int i = 0; i <= codeNum_Int - 1 ; i++) {
      if (IRbyte[i] == testByte_Int[i]) test++ ;  // 機種照合
    }
    if (test == codeNum_Int) {
      recData = IRbyte[DATA_POINT_Int - 1] ;
    }
  }
  return (recData) ;     // 受信データを返す　照合できねば0x100
}

// メソッドrecive
// 赤外線リモコンのデータ受信
int IRrecive::recive(void) {
  unsigned long tim = 0 ;
  unsigned char IRbit = 0;           // 8ビットのシリアルバッファ
  int bitCount = 0 ;       // ビット受信数
  //int byteCount = 0 ; // バイト単位の受信数
  int bitPoint = 0 ;        // IRbitのビット設定位置

  // バイトバッファ初期化
  byteCount = 0 ;
  for ( int x = 0 ; x < 10 ; x++)  IRbyte[x] = 0 ;
  // リーダ部のチェック
  if (!digitalRead(IR_PIN_Int) ) {
    tim = micros() ;
    while (!digitalRead(IR_PIN_Int) ) ;       // OFF時間測定
    tim = micros() - tim ;
  } else  return(0) ;
  // リーダ部(3.4ms以上のOFF)なら受信処理
  if (tim >= 3200) {                   // 標準3400、Sharp = 3300以下
    while (digitalRead(IR_PIN_Int)) ;      // ON部分捨てる
    while (1) {
      while (!digitalRead(IR_PIN_Int)) ;   // ONを待つ
      tim = micros() ;
      while (digitalRead(IR_PIN_Int)) {    // ON時間測定中
        if ((micros() - tim) >= 12000) break ;      // 12ms以上なら中断
      }
      // データの受信
      tim = micros() - tim ;                      // ON時間値
      if (tim >= 10000) break ;                  // ストップデータ
      bitCount++ ;
      if (tim >= 1000)  bitSet(IRbit, bitPoint) ; // ONが長い、データ = 1
      bitPoint++ ;
      if (byteCount < bitCount / 8) {           // バイトバッファに格納
        IRbyte[bitCount / 8 - 1 ] = IRbit ;
        byteCount = bitCount / 8 ;
        bitPoint = 0 ;
        IRbit = 0 ;
      }
    }
  }
  return (byteCount) ;
}

void IRrecive::serialOut(void) {
  if (byteCount > 0 ) {
    // リモコン分析データ表示
    for (int i = 0 ; i < byteCount ; i++) {
      Serial.print("[") ; Serial.print(read(i), HEX) ;
      Serial.print("]") ;
    }
    Serial.print(" total byte = ") ; Serial.print(byteCount) ;
    Serial.print(" DATA_POINT = ") ; Serial.print(DATA_POINT_Int) ;
    Serial.print(" [") ; Serial.print(read(DATA_POINT_Int - 1), HEX) ;
    Serial.println("]") ;
  }
}