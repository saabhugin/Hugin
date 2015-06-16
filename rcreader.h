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
	
	int get_readings(unsigned int* channels);
	
	private:
	int handle; // I2C handle for use with i2cfunc
	int num_channels;
};


#endif