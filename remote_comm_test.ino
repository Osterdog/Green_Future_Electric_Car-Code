#include <SoftwareSerial.h>
#define Rx 0
#define Tx 1
SoftwareSerial xbee(Rx, Tx);


void setup() {
  // put your setup code here, to run once:
pinMode(Rx,INPUT);
pinMode(Tx,OUTPUT);
  Serial.begin(9600);
  xbee.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 // xbee.print('H');
  Serial.println('H');
  delay(100);
  Serial.println('L');
 // xbee.print('L');
  delay(100);
}
