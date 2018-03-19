#ifndef INTERRUPT_INPUTS_H
#define INTERRUPT_INPUTS_H


#include <Arduino.h>
//using arduino UNO

const int MAX_INTERRUPTS = 6;
enum ArduinoInterrupts {
	int_0=0,int_1,
	int_max_plus_1
};
//array for measured speed
volatile unsigned long int inter_count_array[MAX_INTERRUPTS] = { 0, 0, 0, 0, 0, 0 };
//incremented counter
void increase_count_int0() {
	inter_count_array[int_0]++;
	inter_distancecount_array[int_0]++;
}
void increase_count_int1() {
	inter_count_array[int_1]++;
	inter_distancecount_array[int_1]++;
}
class InterruptCount {
protected:
	ArduinoInterrupts interrname;
	boolean enabled;
	int interr_mode;
	int interrupt_pin;
	unsigned long last_check_time_ms;

	void reset_interrupts_count() {
		if (enabled == true) {
			inter_count_array[interrname] = 0; //reset count for upcoming interrupt
			last_check_time_ms = millis(); //time update
		}
	}
	void attach_my_interrupt(int mode) {
		if (enabled == true) {
			interr_mode = mode;

			switch (interrname) {
			case int_0:
				attachInterrupt(int_0, increase_count_int0, mode);
				break;
			case int_1:
				attachInterrupt(int_1, increase_count_int1, mode);
			default:
				break;
			}
		}
	}
	int associatePinNumToInterruptName(ArduinoInterrupts in_interrname) {
		int required_pin = -1;
		switch (interrname) {
		case int_0:
			required_pin = 2;
			break;
		case int_1:
			required_pin = 3;
			break;
		default:
			break;
		}
		return required_pin;
	}
	void detach_my_Interrupt() {
		if (enabled == true) {
			detachInterrupt(interrname);
		}
	}
	void reattach_my_Interrupt() {
		if (enabled == true) {
			attach_my_interrupt(interr_mode);
		}
	}
	unsigned long int get_interrupt_count() { //interrupt number since last reset
		if (enabled == true) {
			return(inter_count_array[interrname]);
		}
		else {
			return 0;
		}
	}
public:
	InterruptCount() { enabled = false; }
	InterruptCount(ArduinoInterrupts in_interrname, int mode = FALLING) {
		enabled = false;
		setup_InterruptCount(in_interrname, mode);
	}
	~InterruptCount() {
		if (enabled == true) {
			detach_my_Interrupt();
		}
	}
	void setup_InterruptCount(ArduinoInterrupts in_interrname, int mode = FALLING) {
		int local_int_max_plus_1 = (int_1 + 1);
		if (enabled == false && in_interrname >= int_0 && in_interrname < local_int_max_plus_1) {
			interrname = in_interrname;
			enabled = true;
			reset_interrupts_count();
			attach_my_interrupt(mode);
		}
	}
	boolean check_update(unsigned long int& count, unsigned long int& interval_ms) {
		boolean success = false;
		if (enabled == true) {
			count = get_interrupt_count();//read count
			interval_ms = millis() - last_check_time_ms;//calculate interval
			reset_interrupts_count();//reset count and update time
			success = true;
		}
		return success;
	}
};