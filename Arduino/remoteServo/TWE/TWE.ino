#include <Servo.h>

String tmpStr;
Servo servo;
char numStr[4];
int i;
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  servo.attach(8);
  servo.write(0);
}

void loop() {
  if ( Serial.available() > 0 ) {
    tmpStr = Serial.readStringUntil(0x3f);
    tmpStr.toCharArray(numStr,4);
    i = atoi(&numStr[0]);
    Serial.println(i);
    servo.write(i);
    delay(100);
    digitalWrite(8,LOW);
  }
}
