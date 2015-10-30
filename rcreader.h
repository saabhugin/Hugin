#ifndef RCREADER_H
#define RCREADER_H
#include "i2cfunc.h"
#include <stdint.h>


class rcreader{
	public:
	rcreader();
	rcreader(int handle_, int num_channels_);
		
	int get_handle();
	void set_handle(int handle_);
	int get_num_channels();
	void set_num_channels(int num_channels_);
	
	int get_readings(int* channels);
	void parse_SBus(int* channels, double* SBus_channels_d);
	
	void set_pwm(double* pwm, int ch); // PWM 4 doubles 0-1;
	private:
	int handle; // I2C handle for use with i2cfunc
	int num_channels;
};


#endif