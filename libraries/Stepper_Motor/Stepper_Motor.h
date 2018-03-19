#ifndef STEPPER_MOTOR_h
#define STEPPER_MOTOR_h

#ifdef COMPILE_CPP_NOT_ARDUINO
#include ".../All_Arduino_or_Cpp_symboldefines/All_Arduino_or_Cpp_symboldefines.h"
#else
#include <Arduino.h>
#endif

#include "..\IntervalCheck\IntervalCheck.h"

/*
micro		sw1		sw2		sw3		/	curr		sw4		sw5		sw6
1			1		1		1		/	3.0A		1		1		1
1/2			0		1		1		/	2.4A		0		1		1
1/4			1		0		1		/	2.1A		1		0		1
1/8			0		0		1		/	1.8A		0		0		1
1/16		1		1		0		/	1.5A		1		1		0
1/32		0		1		0		/	1.2A		0		1		0
1/64		1		0		0		/	0.9A		1		0		0
1/128		0		0		0		/	0.6A		0		0		0
*/

class Stepper_Motor {
protected:
	IntervalCheck dir_check;
	int directionPin, pulsePin;
	const int steps = 500;
	const int step_sense = 400;
	bool left, right;
public:
	//If use enable pin as well, which allows motor to go on and off then adjust.
	// Might not be necessary, need to test current functionality
	// However not difficult to implement, 
	void set_driver(int dir_pin, int pulse_pin) {
		directionPin = dir_pin;
		pulsePin = pulse_pin;
		pinMode(directionPin, OUTPUT);
		pinMode(pulsePin, OUTPUT);
		left = false;
		right = false;
		dir_check.setInterval(100);
	}
	//Motor Operation
	void step_size() {
		int count = 0;
		while (count <= steps) {
			digitalWrite(pulsePin, HIGH);
			delayMicroseconds(step_sense);
			digitalWrite(pulsePin, LOW);
			delayMicroseconds(step_sense);
			count++;
		}
	}
	void go_left() {
		digitalWrite(directionPin, HIGH);
		step_size();
		right = false;
	}
	void go_right() {
		digitalWrite(directionPin, LOW);
		step_size();
		left = false;
	}

	//DIRECTIONAL BEHAVIOR

	void turn_left() {
		if (right) { //going right
			go_left();
			go_left();
			left = true;
		}
		else if (!left && !right) { //going straight
			go_left();
			left = true;
		}
		else { //already left
			return 0;
		}
	}
	void turn_right() {
		if (left) {
			go_right();
			go_right();
			right = true;
		}
		else if (!left && !right) {
			go_right();
			right = true;
		}
		else {
			return 0;
		}
	}
	void straight() {
		if (left) {
			go_right();
		}
		else if (right) {
			go_left();
		}
		else {
			return 0;
		}
	}
	void testing() {
		turn_left();
		delay(4000);
		straight();
		delay(4000);
		turn_right();
		delay(4000);
		straight();
		delay(4000);
	}
};

#endif