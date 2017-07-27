#include <Wire.h>
#include <ks0108w.h>

char str[512] = {0};
byte i = 0;
byte x = 0;
byte u = 1;
void setup(){
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  Serial.begin(9600);
  delay(500);
  GLCD_Init(NON_INVERTED);   // initialise the library, non inverted writes pixels onto a clear screen
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  GLCD_Puts("起動\nうんこ");
}
void loop(){
  if(Serial.available() > 0){
    x = Serial.read();
    str[i] = x;
    i = i + 1;
    u = 0;
    }
   if(Serial.available() <= 0 && u == 0){
     GLCD_CursorTo(0,0);
     GLCD_Puts(str);
     u = 1;
   }
}
