#ifndef DC_FUNCTION_h
#define DC_FUNCTION_h

#ifdef COMPILE_CPP_NOT_ARDUINO
#include ".../All_Arduino_or_Cpp_symboldefines/All_Arduino_or_Cpp_symboldefines.h"
#else
#include <Arduino.h>
#endif

#include "..\DC_motor_control\DC_motor_control.h"
#include "..\basic_speed_PID\basic_speed_PID.h"
#include "..\IntervalCheck\IntervalCheck.h"

// WHEN LEFT_DIR=LOW THEN MOTOR IS FORWARD
// WHEN RIGHT_DIR=HIGH THEN MOTOR IS FORWARD

class rotary_encoder {
protected:
	IntervalCheck checkRot;
	int ch_A;
	int A, prev_A;
	int velocity, counter, period, resolution;
	
	int timer = 200;

public:
	void setup_encoder(int A_channel) {
		ch_A = A_channel;
		pinMode(ch_A, INPUT);
		checkRot.setInterval(timer);
		resolution = 1000;  //if B
		//resolution = 1024; //if J
		period = timer/1000; //sampling time in seconds (1s = 1000ms)
	}
	void measure_encoder() {
		counter = 0;
		while (!checkRot.MinIntervalElapsedUpdate()){
			A = digitalRead(ch_A);
			if (A == HIGH && prev_A == LOW) {
				counter++;
			}
			prev_A = A;
		}
	}
	int calculate_speed() {
		measure_encoder();
		velocity = (counter * 60) / (period * resolution); //Calculating RPM of motor
		if (velocity < 0) {
			velocity = 0;
		}
		if (velocity > 2750) { //Motor rated speed is 2750 RPM ~~ 45.83 rev/sec
			velocity = 2750;
		}
		velocity = map(velocity, 0, 2750, 0, 255); //converts RPM to a PWM value
		return velocity;
	}
};

class Rear_Control {
protected:
	DC_motor MotorLeft, MotorRight;
	rotary_encoder speed_Left, speed_right;
	basic_speed_PID diffLeft,diffRight;
	IntervalCheck InstructCheck, AdjustCheck;
	double fadjust_L, fadjust_R;
	double PWM_measured_left, PWM_measured_right;
	int stop = 0;
	boolean motors_enabled;

	int Rx = 0;
	int Tx = 1;

public:
	void setup_Rear_Control(int PWM_outL, int PWM_outR, int dir_Left, int dir_Right, int PWM_readL, int PWM_readR) {
		MotorLeft.setup_DC(PWM_outL, dir_Left);
		MotorRight.setup_DC(PWM_outR, dir_Right);
		speed_Left.setup_encoder(PWM_readL);
		speed_right.setup_encoder(PWM_readR);
		//motor forward by default
		MotorLeft.bkw();
		AdjustCheck.setInterval(600);
		InstructCheck.setInterval(100);
		diffLeft.set_gainvals(0.5, 1, 0.7);
		diffRight.set_gainvals(0.5, 1, 0.7);
		fadjust_L = 0;
		fadjust_R = 0;
		motors_enabled = true;
	}
	void speed_adjustment(int target_speed) {
		PWM_measured_left = speed_Left.calculate_speed();
		PWM_measured_right = speed_right.calculate_speed();
		if (AdjustCheck.MinIntervalElapsedUpdate()) {
			Serial.println(PWM_measured_left);
			Serial.println(PWM_measured_right);
			fadjust_L = diffLeft.ComputePID_output(target_speed, PWM_measured_left);
			fadjust_R = diffRight.ComputePID_output(target_speed, PWM_measured_right);
			Serial.println(fadjust_L);
			Serial.println(fadjust_R);
		}
	}
	void Left_Instruction(char msg) {
		char instruction;
		instruction = msg;
		fadjust_L = 100; //for testing purpose of RC. This is not using differential control
		Serial.println(instruction);
		if (instruction == "7") {
			MotorLeft.bkw();
			MotorLeft.set_speed(fadjust_L);
		}
		else if (instruction == "8") {
			MotorLeft.set_speed(fadjust_L);
		}
		else if (instruction == "N"){
			MotorLeft.stop_motor();
		}
		else {
			return 0;
		}
	}
	void Right_Instruction(char msg) {
		char instruction;
		instruction = msg;
		Serial.println(instruction);
		fadjust_R = 100; //this does not use differential control. for testing only
		if (instruction == "9") {
			MotorRight.set_speed(fadjust_R);
			Serial.print("going forward");
		}
		else if (instruction == "0") {
			MotorRight.set_speed(fadjust_R);
		}
		else if (instruction == 'S'){
			MotorRight.stop_motor();
		}
		else {
			return 0;
		}
	}
	//Left motor
	void Left_Forward(int speed){
		MotorLeft.bkw();
		MotorLeft.set_speed(speed);
	}
	void Left_Backward(int speed) {
		MotorLeft.fwd();
		MotorLeft.set_speed(speed);
	}
	void Left_Neutral() {
		MotorLeft.stop_motor();
	}
	//Right motor
	void Right_Forward(int speed) {
		MotorRight.fwd();
		MotorRight.set_speed(speed);
	}
	void Right_Backward(int speed) {
		MotorRight.bkw();
		MotorRight.set_speed(speed);
	}
	void Right_Neutral() {
		MotorRight.stop_motor();
	}

	void DC_Instruction(char msg) {
		speed_adjustment(128);
		if (InstructCheck.MinIntervalElapsedUpdate()) {
			Left_Instruction(msg);
			Right_Instruction(msg);
		}
	}
	void DC_TEST() {
		speed_adjustment(60);
		//MotorLeft.set_speed(fadjust_L);
		//MotorRight.set_speed(fadjust_R);
	}
};
#endif