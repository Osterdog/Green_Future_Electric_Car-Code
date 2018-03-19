#include <SoftwareSerial.h>
#define Rx 0
#define Tx 1
SoftwareSerial xbee(Rx,Tx);

char msg = ' ';
int led = 13;

void setup() {
  // put your setup code here, to run once:
pinMode(Rx,INPUT);
pinMode(Tx,OUTPUT);
Serial.begin(9600);
xbee.begin(9600);
pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  msg=xbee.read();
  Serial.println(msg);
  delay(100);
}
