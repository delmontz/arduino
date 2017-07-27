
#ifndef IRrecive_h
#define IRrecive_h
#include "arduino.h"

// IRrecive クラスの設定
class IRrecive {
  public:
    IRrecive(unsigned char IR_PIN_ , unsigned char codeNum_ , unsigned char DATA_POINT_ , unsigned char *testByte_) ;
    unsigned char read(int) ;
    unsigned int test(void) ;
    int recive(void) ;
    void serialOut(void) ;
  private:
    int byteCount ;
    unsigned char IRbyte[10] ;  
    unsigned char IR_PIN_Int ;         // IR接続ピン
    unsigned char *testByte_Int ;     // リモコン固有番号照合データ
    unsigned char codeNum_Int ;     // 照合バイト数　　　
    unsigned char DATA_POINT_Int ;  // 受信するデータのデータ位置
} ;
#endif
