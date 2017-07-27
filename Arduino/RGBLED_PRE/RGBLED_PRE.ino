#include <Adafruit_NeoPixel.h>

// RGBLEDに出力するピン番号
#define RGBLED_OUTPIN    3
// Arduinoにぶら下がっているRGBLEDの個数
#define NUMRGBLED        1

// RGBLEDのライブラリを生成する(色指定はRGBの並びで行う、LEDの速度は800KHzとする)
Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(NUMRGBLED, RGBLED_OUTPIN, NEO_RGB + NEO_KHZ800);

void setup()
{
     RGBLED.begin() ;                   // RGBLEDのライブラリを初期化する
     RGBLED.setPixelColor(0, RGBLED.Color(0,150,0)); // 適度に明るい緑の色。(R=0,G=150,B=0)
     RGBLED.show() ;                    // LEDにデータを送り出す
}
void loop()
{

}
