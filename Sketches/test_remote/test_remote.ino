#include <Remote_Control.h>
#include <SoftwareSerial.h>
#include <IntervalCheck.h>
#define Rx 0
#define Tx 1

SoftwareSerial xbee(Rx, Tx);
Remote_Control controller;
IntervalCheck buttoncheck;

const int checkInt = 100;

const int lm_left=13;
const int lm_right=3;
const int lm_fwd=10;
const int lm_rev=11;

const int rm_left=12;
const int rm_right=2;
const int rm_fwd=9;
const int rm_rev=8;

char Left=' ';
char Right=' ';
char DCleft=' ';
char DCright=' ';
void setup() {
  // put your setup code here, to run once:
  pinMode(Rx,INPUT);
  pinMode(Tx,OUTPUT);
  controller.setup_remote_control_buttons(lm_left,lm_right,lm_fwd,lm_rev,rm_left,rm_right,rm_fwd,rm_rev);
  buttoncheck.setInterval(checkInt);
  Serial.begin(9600);
  xbee.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(buttoncheck.MinIntervalElapsedUpdate()){
    controller.read_inputs();
    Left = controller.Left_steer_state();
    delay(10);
    Right = controller.Right_steer_state();
    delay(10);
    DCleft = controller.DC_left();
    delay(10);
    DCright = controller.DC_right();
    delay(10);
  }
}
