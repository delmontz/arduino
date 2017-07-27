//サンプルスケッチ[IRserialOut]
//
//IR受信ライブラリ
//
//int 受信バイト数 = IR.recive(void) ;
//
//　　IRリモコンからのデータを受信し、受信バイト数を返す
//
//unsigned int 制御用受信データ = IR.test(void) ;
//
//　　受信データ分析（リモコン照合、キー番号抽出）
//　　受信無し、リモコン照合できない場合は 0x0100を返す
//
//byte 受信データ = IR.read(int 読み出し位置) ;
//
//　　受信データを読み出す
//
//void IR.serialOut(void)
//
//    全受信データをシリアル出力する
//
//サンプルのリモコンは、キーを押すと5バイト出力される。
//[1][C1][DF][3][FC]   最初の3バイトがリモコン固有のコード(照合コード）。
//
//    4，5バイト目がキーによって変化するので、4バイト目を制御に使う
//    5バイト目が必要なら IR.read(4)で読み出す。
//    (注）
//     DATA_POINTは、受信バイトを１から数えるが、IR.Readでは0から数える。
//
//     以下のスケッチは、Exampleに入っているIRserialOutのスケッチ。
//     IRリモコンからのデータを受信し、全受信バイトをシリアル表示する。
//     リモコンが照合できたなら、制御に使用するDATA_POINT = 4位置のデータを
//         シリアル表示する。
//
//         さらに、5バイト目を個別にシリアル表示する。
//         これは、4バイト目だけでキーを識別できない特殊な状況を想定している。


#include <IRrecive.h>
// デジタルピン
#define IR_PIN     2  // 赤外線受信モジュール接続ピン番号

// ライブラリとの接続
const byte codeCount  =  3 ;    // リモコンの先頭固有バイト照合数
const byte DATA_POINT =  4 ;    // 受信するデータのバイト位置
// 固有バイト照合データ
byte testByte[codeCount] = { 0x01 , 0xC1 , 0xDF } ;
// IRreciveの初期化
IRrecive IR(IR_PIN , codeCount , DATA_POINT , testByte) ;

// 簡略すると以下でも良いが、testByteはポインタで接続されるため、
// 変数を事前に配置しておく必要がある。
// byte testByte[codeCount] = { 0x01 , 0xC1 , 0xDF } ;
// IRrecive IR ( 2 , 3  , 4 ,testByte ) ;  

// 初期化
void setup() {
  Serial.begin(9600) ;
  pinMode(IR_PIN, INPUT) ;
}

void loop() {
  int byteCount ;
  byte x ;
  unsigned int controlData ;
  byteCount = IR.recive() ;
  IR.serialOut() ;                 // 全受信バイトをシリアル出力
  x = IR.read ( 5 - 1 ) ;          // 5バイト目を読み出す
  controlData = IR.test() ;        // リモコン照合、制御バイト抽出

  // リモコンが照合できたか？
  if (controlData != 0x0100) {  
    // 0x0100 受信無し、またはリモコン照合できず
    Serial.print( "controlData = " ) ;
    Serial.println( controlData , HEX ) ;
    Serial.print( "5byteData   = " ) ;
    Serial.println( x , HEX ) ;
  }
}


