#include <DC_motor_control.h>
#include <IntervalCheck.h>
#include <SoftwareSerial.h>
#define Rx 0
#define Tx 1

SoftwareSerial xbee(Rx,Tx);
DC_motor control;
DC_motor control2;
IntervalCheck dircheck;

const int checkInt = 100;

int PWM_pin=9;
int dir_pin=8;
int read_pin=3;

int PWM_pinL=10;
int dir_pinL=11;
int read_pinL=2;

int delaytime=3000; //3seconds
char msg = ' ';

void setup() {
pinMode(Rx,INPUT);
pinMode(Tx,OUTPUT);
control.setup_DC(PWM_pin,dir_pin,read_pin);
control2.setup_DC(PWM_pinL,dir_pinL,read_pinL);
digitalWrite(dir_pin,HIGH);
digitalWrite(dir_pinL,LOW);
dircheck.setInterval(checkInt);
control.fwd();
control2.bkw();
Serial.begin(9600);
xbee.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
/*control.set_speed(80);
control2.set_speed(80);
delay(3000);
control.change_dir();
control2.change_dir();
*/
while(Serial.available()>0){
msg = xbee.read();
Serial.println(msg);
if(dircheck.MinIntervalElapsedUpdate()){
  if(msg == '7'){
      control2.bkw();
      control2.set_speed(80);
  }
  if(msg == '8'){
      control2.fwd();
      control2.set_speed(80);
  }
  if(msg == 'N'){
   msg == '9'){
      control.fwd();
      control.set_speed(80);
  }
  if(msg =='0'){
      control.bkw();
      control.set_speed(80);
  }
  if(msg == 'S'){
      control.stop_motor();
  }   control2.stop_motor();
  }
  if(
}
}
