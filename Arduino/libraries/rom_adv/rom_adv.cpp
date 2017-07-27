//-----------------------------------------------------------------------
//　rom_adv.cpp
//　内蔵EEPROM読書補佐ライブラリ　version0.1.1
//
//　このライブラリーはArduinoに内蔵されるEEPROMの読み書きを簡単にする
//　ラッパーライブラリーです。
//　
//　Arduino言語の仕様上、内蔵EEPROMにはbyte型しか読書できません。
//　その他の型を読書するにはByte型に分割する必要があります。
//
//　Byte型への分割と統合は泥臭く面倒くさいのでライブラリー化しました。
//
//　各変数型を自動的にキャストして指定したメモリー位置から読書を行います。
//
//　注意事項
//　・このライブラリーはファイルシステムのようにどこにどの情報を記憶しているか
//　管理しません。型によって必要になるByte数は変わるので、意識してプログラムを
//　しないとデーターが化けます。つまり、番地管理は頑張れ！
//
//　・Stringは255Byte以上を扱うことは出来ません。またUTF-8で記憶するため、
//　半角カナでも日本語文字は3Byte消費します。漢字を記憶することも可能です。
//　番地管理の時は気をつけてください。
//
//　アップデート履歴
//　0.1.1　2015/05/15 String書き込み時に戻り値で使用したByte数を返す様に変更
//　0.1.0　2015/05/01 初回作成
//
//　ライセンス
//　Copyright (C) 2015 infernoayase.net ふさもふ<<齋藤 みつる>>
//
//　このプログラムはフリーソフトウェアです。あなたはこれを、
//　フリーソフトウェア財団によって発行されたGNU 一般公衆利用許諾書
//　(バージョン3かそれ以降のバージョンのうちどれか)が定める条件の下で
//　再頒布または改変することができます。
//
//　このプログラムは有用であることを願って頒布されますが、*全くの無保証 *です。
//　商業可能性の保証や特定目的への適合性は、言外に示されたものも
//　含め、全く存在しません。詳しくはGNU 一般公衆利用許諾書をご覧ください。
//
//　あなたはこのプログラムと共に、GNU 一般公衆利用許諾書のコピーを
//　一部受け取っているはずです。
//　もし受け取っていなければ、<http://www.gnu.org/licenses/> をご覧ください。
//
//-----------------------------------------------------------------------
#include <Arduino.h>
#include <EEPROM.h>
#include "rom_adv.h"

//-----------------------------------------------------------------------　
//
//  コンストラクター
//  初期化処理関数
//
//  ☆戻り値→void
//
//  ☆引数
//　int address 使用するマイコンで最大のアドレス番地を指定して処理
//
//-----------------------------------------------------------------------
rom_adv::rom_adv(int address) {
  //搭載されているMaxのEEPROMのアドレスを指定
  maxaddress = address;
}

//-----------------------------------------------------------------------
//　float型をEEPROMに書き込むメソッド
//
//　☆戻り値→bool型
//　　問題なし→ture
//　　エラー→false
//
//　☆引数
//　　float f 内容
//　　int address 書き込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
bool rom_adv::f_Write(float f, int address) {
  memo = 4;//何バイト確保するか?
  _f_cast temp;
  temp.f = f;

  if (!Writing(address, temp.Byte, memo)) {
    return false;//書き込み失敗
  }

  return true;
}

//-----------------------------------------------------------------------
//　int型をEEPROMに書き込むメソッド
//
//　☆戻り値→bool型
//　　問題なし→ture
//　　エラー→false
//
//　☆引数
//　　int i 内容
//　　int address 書き込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
bool rom_adv::i_Write(int i, int address) {
  memo = 2;//何バイト確保するか?
  _i_cast temp;
  temp.i = i;

  if (!Writing(address, temp.Byte, memo)) {
    return false;//書き込み失敗
  }

  return true;
}

//-----------------------------------------------------------------------
//　unsigned int型をEEPROMに書き込むメソッド
//
//　☆戻り値→bool型
//　　問題なし→ture
//　　エラー→false
//
//　☆引数
//　　unsigned int i 内容
//　　int address 書き込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
bool rom_adv::ui_Write(unsigned int ui, int address) {
  memo = 2;//何バイト確保するか?
  _ui_cast temp;
  temp.ui = ui;

  if (!Writing(address, temp.Byte, memo)) {
    return false;//書き込み失敗
  }

  return true;
}

//-----------------------------------------------------------------------
//　word型をEEPROMに書き込むメソッド
//
//　☆戻り値→bool型
//　　問題なし→ture
//　　エラー→false
//
//　☆引数
//　　word w 内容
//　　int address 書き込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
bool rom_adv::w_Write(word w, int address) {
  memo = 2;//何バイト確保するか?
  _w_cast temp;
  temp.w = w;

  if (!Writing(address, temp.Byte, memo)) {
    return false;//書き込み失敗
  }

  return true;
}

//-----------------------------------------------------------------------
//　long型をEEPROMに書き込むメソッド
//
//　☆戻り値→bool型
//　　問題なし→ture
//　　エラー→false
//
//　☆引数
//　　long l内容
//　　int address 書き込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
bool rom_adv::l_Write(long l, int address) {
  memo = 4;//何バイト確保するか?
  _l_cast temp;
  temp.l = l;

  if (!Writing(address, temp.Byte, memo)) {
    return false;//書き込み失敗
  }

  return true;
}

//-----------------------------------------------------------------------
//　unsigned long型をEEPROMに書き込むメソッド
//
//　☆戻り値→bool型
//　　問題なし→ture
//　　エラー→false
//
//　☆引数
//　　unsigned long l内容
//　　int address 書き込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
bool rom_adv::ul_Write(unsigned long ul, int address) {
  memo = 4;//何バイト確保するか?
  _ul_cast temp;
  temp.ul = ul;

  if (!Writing(address, temp.Byte, memo)) {
    return false;//書き込み失敗
  }

  return true;
}

//-----------------------------------------------------------------------
//　String型をEEPROMに書き込むメソッド
//  注意：255文字までしか読み書き出来ません！先頭1Byteは文字数を管理する
//　　　　領域です。他のライブラリとの互換性は保証されません
//
//　☆戻り値→int
//　　問題なし→メモリー使用量域
//　　エラー→-1
//
//　☆引数
//　　String *s 文字列へのポインター。
//　　int address 書き込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
int rom_adv::s_Write(String *s, int address) {
  byte lengthnum = s->length();
  memo = lengthnum + 1;
  byte data[memo];
  data[0] = lengthnum;

  //配列の展開
  for (int i = 1; i < memo; i++) {
    data[i] = s->charAt(i - 1);
  }
  
  //配列の初期化
  if (!Writing(address, data, memo)) {
    return -1;//書き込み失敗
  }
  return memo;
}

//-----------------------------------------------------------------------
//　float型をEEPROMから読出メソッド
//
//　☆戻り値→float
//
//　☆引数
//　　int address 読み込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
float rom_adv::f_Read(int address) {
  memo = 4;//何バイト確保するか?
  _f_cast temp;

  if (!Reading(address, temp.Byte, memo)) {
    return NULL;//読み込み失敗
  }

  return temp.f;
}

//-----------------------------------------------------------------------
//　int型をEEPROMから読出メソッド
//
//　☆戻り値→int
//
//　☆引数
//　　int address 読み込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
int rom_adv::i_Read(int address) {
  memo = 2;//何バイト確保するか?
  _i_cast temp;

  if (!Reading(address, temp.Byte, memo)) {
    return NULL;//読み込み失敗
  }

  return temp.i;
}

//-----------------------------------------------------------------------
//　unsigned int型をEEPROMから読出メソッド
//
//　☆戻り値→unsigned int
//
//　☆引数
//　　int address 読み込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
unsigned int rom_adv::ui_Read(int address) {
  memo = 2;//何バイト確保するか?
  _ui_cast temp;

  if (!Reading(address, temp.Byte, memo)) {
    return NULL;//読み込み失敗
  }

  return temp.ui;
}

//-----------------------------------------------------------------------
//　word型をEEPROMから読出メソッド
//
//　☆戻り値→word
//
//　☆引数
//　　int address 読み込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
word rom_adv::w_Read(int address) {
  memo = 2;//何バイト確保するか?
  _w_cast temp;

  if (!Reading(address, temp.Byte, memo)) {
    return NULL;//読み込み失敗
  }

  return temp.w;
}

//-----------------------------------------------------------------------
//　long型をEEPROMから読出メソッド
//
//　☆戻り値→long
//
//　☆引数
//　　long address 読み込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
long rom_adv::l_Read(int address) {
  memo = 4;//何バイト確保するか?
  _l_cast temp;

  if (!Reading(address, temp.Byte, memo)) {
    return NULL;//読み込み失敗
  }

  return temp.l;
}

//-----------------------------------------------------------------------
//　unsigned long型をEEPROMから読出メソッド
//
//　☆戻り値→long
//
//　☆引数
//　　long address 読み込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
unsigned long rom_adv::ul_Read(int address) {
  memo = 4;//何バイト確保するか?
  _ul_cast temp;

  if (!Reading(address, temp.Byte, memo)) {
    return NULL;//読み込み失敗
  }

  return temp.ul;
}

//-----------------------------------------------------------------------
//　String型をEEPROMから読出メソッド
//  注意：255文字までしか読み書き出来ません！先頭1Byteは文字数を管理する
//　　　　領域です。他のライブラリとの互換性は保証されません
//
//　☆戻り値→long
//
//　☆引数
//    String *s 返す値を入れるためのStringオブジェクトのポインター
//　　int address 読み込む先頭アドレスを指定
//
//-----------------------------------------------------------------------
bool rom_adv::s_Read(String *s, int address) {
  byte lengthnum[0];
  //文字列の長さを取得
  if (!Reading(address, lengthnum, 1)) {
    return NULL;//読み込み失敗
  }
  char data[lengthnum[0]];
  //本体の読み込み
  if (!Reading(address + 1, data, lengthnum[0])) {
    return NULL;//読み込み失敗
  }
  //型変換
  *s = String(data);
  return true;

}

//-----------------------------------------------------------------------
//  ☆☆☆☆☆☆☆☆☆【プライベートメソッド】☆☆☆☆☆☆☆☆☆
//
//　実際の書き込みを行うメソッド
//
//☆戻り値→bool型
//　　問題なし→ture
//　　エラー→false
//
//　☆引数
//　　int address 書込む先頭アドレレス
//　　byte *data 書込むデーターの配列のポインター
//　　int num データーのサイズ
//-----------------------------------------------------------------------
bool rom_adv::Writing(int address, byte *data, int num) {

  //ROM容量が確保出来るか？
  if (address + num > maxaddress) {
    return false;//書き込みエラー
  }

  //書き込み動作
  int h_address;//書き込むアドレス
  for (int i = 0; i < num; i++) {
    h_address = address + i;
    EEPROM.write(h_address, data[i]);
  }
  return true;
}

//-----------------------------------------------------------------------
//  ☆☆☆☆☆☆☆☆☆【プライベートメソッド】☆☆☆☆☆☆☆☆☆
//
//　実際の読み込みを行うメソッド
//　渡すポインターに見合う要素数分ちゃんとリソースを確保すること。
//　オーバーランしちゃうよ！
//
//☆戻り値→bool型
//　　問題なし→ture
//　　エラー→false
//
//　☆引数
//　　int address 読み込む先頭アドレレス
//　　byte *data 読み込むデーターを確保する配列のポインター
//　　int num データーのサイズ
//-----------------------------------------------------------------------
bool rom_adv::Reading(int address, byte *data, int num) {
  //ROM容量が確保出来るか？
  if (address + num > maxaddress) {
    return false;//読み込みエラー
  }

  //読み込み動作
  int h_address;//書き込むアドレス
  for (int i = 0; i < num; i++) {
    h_address = address + i;
    data[i] = EEPROM.read(h_address);
  }
  return true;

}


//-----------------------------------------------------------------------
//  ☆☆☆☆☆☆☆☆☆【プライベートメソッド】☆☆☆☆☆☆☆☆☆
//
//　実際の読み込みを行うメソッド
//　渡すポインターに見合う要素数分ちゃんとリソースを確保すること。
//　オーバーランしちゃうよ！
//
//☆戻り値→bool型
//　　問題なし→ture
//　　エラー→false
//
//　☆引数
//　　int address 読み込む先頭アドレレス
//　　byte *data 読み込むデーターを確保する配列のポインター
//　　int num データーのサイズ
//-----------------------------------------------------------------------
bool rom_adv::Reading(int address, char *data, int num) {
  //ROM容量が確保出来るか？
  if (address + num > maxaddress) {
    return false;//読み込みエラー
  }

  //読み込み動作
  int h_address;//書き込むアドレス
  for (int i = 0; i < num; i++) {
    h_address = address + i;
    data[i] = EEPROM.read(h_address);
  }
  return true;

}
