#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

char ssid[] = "unko";
char pass[] ="tomato0922";
ESP8266WebServer server(80);

void ledOn(){
  digitalWrite(14,HIGH);
  server.send(200, "text/html","ON");
  
}
void ledOff(){
  digitalWrite(14,LOW);
  server.send(200, "text/html","OFF");
}

void setup() {
  pinMode(14,OUTPUT);
  digitalWrite(14,LOW);
  Serial.begin(115200);
  // put your setup code here, to run once:
  WiFi.softAP(ssid, pass);
  IPAddress ip = WiFi.softAPIP();
  Serial.println("");
  Serial.println(ssid + String(" starts..")); 
  Serial.print("this AP : "); 
  Serial.println(ip);
 
  server.on("/off", ledOff);
  server.on("/on", ledOn);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() { 
  server.handleClient();
  delay(1);
}
