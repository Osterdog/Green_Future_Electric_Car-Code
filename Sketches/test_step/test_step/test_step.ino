#include <IntervalCheck.h>
#include <Stepper_Motor.h>
#include <SoftwareSerial.h>
#define Rx 0
#define Tx 1

SoftwareSerial xbee(Rx,Tx);
Stepper_Motor Lmotor,Rmotor;
IntervalCheck dircheck;
const int checkInt = 10;

const int RdirectionPin = 13;
const int RpulsePin = 12;
const int LdirectionPin = 10;
const int LpulsePin = 9;

char msg = ' ';
void setup() {
  pinMode(Rx,INPUT);
  pinMode(Tx,OUTPUT);
  Lmotor.set_driver(LdirectionPin,LpulsePin);
  Rmotor.set_driver(RdirectionPin,RpulsePin);
  dircheck.setInterval(checkInt);
  Serial.begin(9600);
  xbee.begin(9600);
}

void loop() {
/*
  Lmotor.turn_left();
  Rmotor.turn_right();
  delay(3000);
  */
while(Serial.available()>0){
    msg = xbee.read();
    Serial.println(msg);
 if(dircheck.MinIntervalElapsedUpdate()){
    switch(msg){
      case '1':
        Lmotor.turn_left();
        Serial.print("L going left");
        break;
      case '2':
        Lmotor.turn_right();
        break;
      case '3':
        Lmotor.straight();
        break;
      case '4':
        Rmotor.turn_left();
        Serial.print("R going Left");
        break;
      case '5':
        Rmotor.turn_right();
        break;
      case '6':
        Rmotor.straight();
        break;
      default:
        break;
    }
  }
  delay(10);
}
}
