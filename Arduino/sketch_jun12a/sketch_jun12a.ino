void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("START");
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  
  digitalWrite(5,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("GO!!");
  delay(2000);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  delay(1000);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  delay(2000);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  delay(1000);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
}
