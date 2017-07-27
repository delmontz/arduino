//-----------------------------------------------------------------------
//　rom_adv.h
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
#ifndef rom_adv_h
#define rom_adv_h
#include <Arduino.h>
#include <EEPROM.h>

/*float型変換用の共有体*/
typedef union _f_cast {
  float f;//
  byte Byte[3];
};

/*int型変換用の共有体*/
typedef union _i_cast {
  int i;
  byte Byte[1];
};

/*unsigned int型変換用の共有体*/
typedef union _ui_cast {
  unsigned int ui;
  byte Byte[1];
};


/*word型変換用の共有体*/
typedef union _w_cast {
  word w;
  byte Byte[1];
};

/*long型変換用の共有体*/
typedef union _l_cast {
  long  l;
  byte Byte[3];
};

/*unsigned long型変換用の共有体*/
typedef union _ul_cast {
  unsigned long  ul;
  byte Byte[3];
};

//　EEPROM読書補佐ライブラリ
// クラス名・コンストラクタ名・関数名や使用する変数名を定義します。
//
//　各変数型を自動的にキャストして指定したメモリー位置から読書を行う
//　☆Stringは255Byte以上を扱うことは出来ません。
//
class rom_adv
{
  public:
    rom_adv(int address);
    bool f_Write(float f, int address);
    bool i_Write(int i, int address);
    bool ui_Write(unsigned int ui, int address);
    bool w_Write(word w, int address);
    bool l_Write(long l, int address);
    bool ul_Write(unsigned long ul, int address);
    int s_Write(String *s, int address);
    float f_Read(int address);
    int i_Read(int address);
    unsigned int ui_Read(int address);
    word w_Read(int address);
    long l_Read(int address);
    unsigned long ul_Read(int address);
    bool s_Read(String *s,int address);

  private:
    byte memo;
    int maxaddress;//アドレスの最大番地
    bool Writing(int address, byte *data, int num); //実際の書込用プライベートメソッド
    bool Reading(int address, byte *data, int num); //実際の読込用プライベートメソッド
    bool Reading(int address, char *data, int num); //実際の読込用プライベートメソッド
};


#endif

