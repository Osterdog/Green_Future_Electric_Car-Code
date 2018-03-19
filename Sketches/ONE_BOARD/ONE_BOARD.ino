#include <DC_Function.h>
#include <IntervalCheck.h>
#include <Stepper_Motor.h>
#include <SoftwareSerial.h>
#define Rx 0
#define Tx 1

SoftwareSerial xbee(Rx,Tx);
Stepper_Motor Lmotor,Rmotor;
Rear_Control motor;
IntervalCheck dircheck;
const int checkInt = 10;

const int RdirectionPin = 13;
const int RpulsePin = 12;
const int LdirectionPin = 10;
const int LpulsePin = 9;

const int PWM_outL = 4;
const int dir_Left = 5;
const int PWM_readL = 3;

const int PWM_outR = 6;
const int dir_Right = 7;
const int PWM_readR = A1;
int def_speed = 128;
char msg = ' ';

void setup() {
  // put your setup code here, to run once:
  pinMode(Rx,INPUT);
  pinMode(Tx,OUTPUT);
  Lmotor.set_driver(LdirectionPin,LpulsePin);
  Rmotor.set_driver(RdirectionPin,RpulsePin);
  motor.setup_Rear_Control(PWM_outL, PWM_outR, dir_Left, dir_Right, PWM_readL, PWM_readR);
  dircheck.setInterval(checkInt);
  Serial.begin(9600);
  xbee.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly;

while(Serial.available()>0){
    msg = xbee.read();
    Serial.println(msg);
 if(dircheck.MinIntervalElapsedUpdate()){
    switch(msg){
      case '1':
       // Lmotor.turn_left();
        Lmotor.go_left();
        Serial.print("L going left");
        break;
      case '2':
       // Lmotor.turn_right();
        Lmotor.go_right();
        break;
      case '3':
        //Lmotor.straight();
        break;
      case '4':
        //Rmotor.turn_left();
        Rmotor.go_left();
        Serial.print("R going Left");
        break;
      case '5':
       // Rmotor.turn_right();
        Rmotor.go_right();
        break;
      case '6':
       // Rmotor.straight();
        break;
       case '7':
          motor.Left_Forward(def_speed);
          Serial.print("L forward");
          break;
        case '8':
          motor.Left_Backward(def_speed);
          break;
        case 'N':
          motor.Left_Neutral();
          break;
        case '9':
          motor.Right_Forward(def_speed);
          Serial.print("R forward");
          break;
        case '0':
          motor.Right_Backward(def_speed);
          break;
        case 'S':
          motor.Right_Neutral();
          break;
      default:
        break;
    }
  }
  delay(10);
}
}
