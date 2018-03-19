#include <DC_Function.h>
#include <IntervalCheck.h>
#include <SoftwareSerial.h>
#define Rx 0
#define Tx 1

SoftwareSerial xbee(Rx, Tx);
Rear_Control motor;
IntervalCheck dircheck;
const int checkInt = 10;

const int PWM_outL = 9;
const int dir_Left = 8;
const int PWM_readL = 5;

const int PWM_outR = 10;
const int dir_Right = 11;
const int PWM_readR = 4;

int def_speed = 60;

char msg = ' ';
void setup() {
  // put your setup code here, to run once:
  pinMode(Rx, INPUT);
  pinMode(Tx, OUTPUT);
  motor.setup_Rear_Control(PWM_outL, PWM_outR, dir_Left, dir_Right, PWM_readL, PWM_readR);
  dircheck.setInterval(checkInt);
  Serial.begin(9600);
  xbee.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 /*while (Serial.available() > 0) {
    msg = xbee.read();
    Serial.println(msg);
    if(dircheck.MinIntervalElapsedUpdate()){
      switch(msg){
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
  }*/
  //motor.DC_TEST();
  motor.Left_Forward(60);
  delay(100);
}
