#ifndef INTERVALCHECK_H
#define INTERVALCHECK_H


#ifdef COMPILE_CPP_NOT_ARDUINO
#include "..\All_Arduino_or_Cpp_symboldefines\All_Arduino_or_Cpp_symboldefines.h"
#else
#include <Arduino.h>
#endif // COMPILE_CPP_NOT_ARDUINO

class IntervalCheck {
protected:
	unsigned long int last_checked, min_interval_ms;
	static const unsigned long int default_min_interval_ms = 100;
public:
	IntervalCheck() {
		last_checked = 0;
		min_interval_ms = default_min_interval_ms;
	}
	void setInterval(int inp_interval_ms) {
		inp_interval_ms = abs(inp_interval_ms); //input is always positive
		min_interval_ms = inp_interval_ms;
	}
	int getInterval() {
		return min_interval_ms;
	}
	boolean MinIntervalElapsed() {
		unsigned long int current = millis();
		if ((current - last_checked) >= min_interval_ms) {
			return true;
		}
		if (current < last_checked) { // reset if overflow
			updateCheck();
		}
		return false;
	}
	void updateCheck() {
		last_checked = millis();
	}
	bool MinIntervalElapsedUpdate() {
		bool TimeToUpdate = MinIntervalElapsed();
		if (TimeToUpdate) {
			updateCheck();
		}
		return TimeToUpdate;
	}
};
#endif