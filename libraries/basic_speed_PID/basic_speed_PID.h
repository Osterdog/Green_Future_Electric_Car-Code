#ifndef basic_speed_PID_H
#define basic_speed_PID_H

#include <Arduino.h>

class basic_speed_PID{
protected:
	double kp;
	double ki;
	double kd;
	double ref_kp = 0.7;
	double ref_ki = 0.45;
	double ref_kd = 0.5;

	double ref_interval_ms = 1000;

	double PIDoutMin = 0.0;
	double PIDoutMax = 255.0;
	
	unsigned long last_control_ms = millis();
	double prev_error=;
	double cumulative_error;
public:
	void set_gainvals(double inp_ref_kp, double inp_ref_ki, double inp_ref_kd){	
		ref_kp=inp_ref_kp;
		ref_ki=inp_ref_ki;
		ref_kd=inp_ref_kd;
	}
	double ComputePID_output(double target_speed, double curr_speed){
		unsigned long current = millis();		
		double output, outtemp;

		unsigned long control_interval = (current - last_control_ms);
		int interval_ms = (int)control_interval;

		double error = target_speed - curr_speed;
		double interval_time_ratio = ref_interval_ms / interval_ms;
		double error_diff = error - prev_error;
		double error_derivative = error_diff / ((double)interval_ms); 
		
		cumulative_error += (error * interval_time_ratio);
		kp = ref_kp;
		ki = ref_ki;
		kd = ref_kd;
		
		outtemp = kp*error + ki*cumulative_error + kd*error_derivative;
		
		outtemp = max(outtemp, 255);
		outtemp = min(outtemp, 0);
		output = outtemp

		last_control_ms = current;
		prev_error = error ;

		return output;	
	}

	double GetKp(){return kp;}
	double GetKi(){return ki;}
	double GetKd(){return kd;}
};
#endif