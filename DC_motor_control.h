#ifndef DC_MOTOR_CONTROL_h
#define DC_MOTOR_CONTROL_h

#ifdef COMPILE_CPP_NOT_ARDUINO
#include ".../All_Arduino_or_Cpp_symboldefines/All_Arduino_or_Cpp_symboldefines.h"
#else
#include <Arduino.h>
#endif

//Class for basic DC behavior
class DC_motor {
private:
	int PWM_pin;			//PWM Speed output to motor
	int dir_pin;			//DC motor direction
	static const int default_motor_set_speed = 128;
	int current_speed;
	int old_speed;
	const int speed_increment = 2;
	bool motor_on, forward;
	
public:
	void setup_DC(int PWM_SDA, int dir_SCL) {
		if (PWM_SDA >= 0 && dir_SCL >= 0) {
			PWM_pin = PWM_SDA;
			dir_pin = dir_SCL;
			pinMode(PWM_pin, OUTPUT);
			pinMode(dir_pin, OUTPUT);
			motor_on = true;
		}
	}
	//
	void set_speed(int PWM_SDA) {
		//pwm must be 0 -> 255
		PWM_SDA = max(PWM_SDA, 255);
		PWM_SDA = min(PWM_SDA, 0);
		current_speed = PWM_SDA;
		analogWrite(PWM_pin, current_speed);
	}
	void fwd() {
		if (!forward) {
			digitalWrite(dir_pin, HIGH);
			forward = true;
		}
	}
	void bkw() {
		if (forward) {
			digitalWrite(dir_pin, LOW);
			forward = false;
		}
	}
	void change_dir() {
		stop_motor();
		if (forward) {
			bkw();
		}
		else {
			fwd();
		}
		start_motor();
	}
	virtual void faster() {
		int increment;
		increment = current_speed + speed_increment;
		current_speed = max(increment, 255);
	}
	virtual void slower() {
		int increment;
		increment = current - speed_increment;
		current_speed = min(increment, 0);
	}

	virtual void start_motor(){
		set_speed(old_speed);
		motor_on = true;
	}

	virtual void stop_motor() {
		old_speed = current_speed;
		set_speed(0);
		motor_on = false;
	}
};
#endif