#ifndef REMOTE_CONTROL_h
#define REMOTE_CONTROL_h

#ifdef COMPILE_CPP_NOT_ARDUINO
#include ".../All_Arduino_or_Cpp_symboldefines/All_Arduino_or_Cpp_symboldefines.h"
#else
#include <Arduino.h>
#endif

#include "..\IntervalCheck\IntervalCheck.h"
#include "..\Xbee_Communicator\Xbee_Communicator.h"

class Remote_Control {
protected:
	IntervalCheck buttoncheck;
	Xbee_send Xbee;
	int LM_left_pin, LM_right_pin, LM_Fwd_pin, LM_rev_pin;
	int LM_left, LM_right, LM_Fwd, LM_rev;

	int RM_left_pin, RM_right_pin, RM_Fwd_pin, RM_rev_pin;
	int RM_left, RM_right, RM_Fwd, RM_rev;
	char output_left, output_right, DC_left_dir, DC_right_dir;
	boolean Turn_Left_left, Turn_Right_right, Straight, fwd, bkw;

public:
	void setup_remote_control_buttons(int lm_left, int lm_right, int lm_fwd, int lm_rev, int rm_left, int rm_right, int rm_fwd, int rm_rev) {
		LM_left_pin = lm_left;
		LM_right_pin = lm_right;
		LM_Fwd_pin = lm_fwd;
		LM_rev_pin = lm_rev;
		RM_left_pin = rm_left;
		RM_right_pin = rm_right;
		RM_Fwd_pin = rm_fwd;
		RM_rev_pin = rm_rev;
		pinMode(LM_left_pin, INPUT);
		pinMode(LM_right_pin, INPUT);
		pinMode(LM_Fwd_pin, INPUT);
		pinMode(LM_rev_pin, INPUT);
		pinMode(RM_left_pin, INPUT);
		pinMode(RM_right_pin, INPUT);
		pinMode(RM_Fwd_pin, INPUT);
		pinMode(RM_rev_pin, INPUT);
	}
	//reads button input from controller
	void read_inputs() {
		LM_left = digitalRead(LM_left_pin);
		LM_right = digitalRead(LM_right_pin);
		LM_Fwd = digitalRead(LM_Fwd_pin);
		LM_rev = digitalRead(LM_rev_pin);
		RM_left = digitalRead(RM_left_pin);
		RM_right = digitalRead(RM_right_pin);
		RM_Fwd = digitalRead(RM_Fwd_pin);
		RM_rev = digitalRead(RM_rev_pin);
	}
	//Logic for the button inputs
	//Controlling signal sent for each individual motor based on buttons pressed
	int Left_steer_state() {
		if (LM_left == HIGH && LM_right == LOW) {
			output_left = '1';
		}
		else if (LM_right == HIGH && LM_left == LOW) {
			output_left = '2';
		}
		else {
			output_left = '3';
		}
		Serial.println(output_left);
		return output_left;
	}
	int Right_steer_state() {
		if (RM_left == HIGH && RM_right == LOW) {
			output_right = '4';
		}
		else if (RM_right == HIGH &&RM_left == LOW) {
			output_right = '5';
		}
		else {
			output_right = '6';
		}
		Serial.println(output_right);
		return output_right;
	}
	int DC_left() {
		if (LM_Fwd == HIGH && LM_rev == LOW) {
			DC_left_dir = '7';
		}
		else if (LM_rev == HIGH && LM_Fwd == LOW) {
			DC_left_dir = '8';
		}
		else {
			DC_left_dir = 'N';
		}
		Serial.println(DC_left_dir);
		return DC_left_dir;
	}
	int DC_right() {
		if (RM_Fwd == HIGH && RM_rev == LOW) {
			DC_right_dir = '9';
		}
		else if (RM_rev == HIGH && RM_Fwd == LOW) {
			DC_right_dir = '0';
		}
		else {
			DC_right_dir = 'S';
		}
		Serial.println(DC_right_dir);
		return DC_right_dir;
	}

};

#endif // !REMOTE_CONTROL_h
