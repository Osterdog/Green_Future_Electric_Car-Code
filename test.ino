#include <DC_motor_control.h>

DC_motor control;
DC_motor control2;

const int PWM_pin=9;
const int dir_pin=8;
const int read_pin=3;

const int PWM_pinL=10;
const int dir_pinL=11;
const int read_pinL=2;

int delaytime=3000; //3seconds

void setup() {
  // put your setup code here, to run once:
  control.setup_DC(PWM_pin,dir_pin);
  control2.setup_DC(PWM_pinL,dir_pinL);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(dir_pin,HIGH);
analogWrite(PWM_pin,128);
delay(3000);
analogWrite(PWM_pin,0);
digitalWrite(dir_pin,LOW);
delay(3000);
analogWrite(PWM_pin,128);
delay(3000);
analogWrite(PWM_pin,0);
delay(3000);

}
