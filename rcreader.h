/*
 * rcreader.h
 *
 * Class file for rcreader class. 
 *
 * rcreader is the object that handles all connection between the ATmega and the BeagleboneBlack.
 * The communication protocol is i2c, but the common user does not need to understand the 
 * i2c protocol to use the rcreader class.
 *
 * Functions for fetching PWM and SBUS readings from ATmega and function to command the ATmega to set new PWM signals.
 */

#ifndef RCREADER_H
#define RCREADER_H
#include "i2cfunc.h"
#include <stdint.h>
#include <cstdio>


class rcreader{
	
public:
	rcreader();
	rcreader(int handle_, int num_channels_);
	
	// I2C communication support functions
	int get_handle();
	void set_handle(int handle_);
	int get_num_channels();
	void set_num_channels(int num_channels_);
	
	// Asks the ATmega for latest PWM and SBUS readings.
	int get_readings(int* channels);
	
	// PWM reading protocol using pin interrupt
	volatile int pwm_value;
	volatile int prev_time;
	void setup();
	void rising();
	void falling();
	//void loop();
	
	// Function for unpacking the SBUS values fetched using get_readings()
	void parse_SBus(int* channels, double* SBus_channels_d);
	
	// Sends command to ATmega to apply new PWM signals to the motors.
	void set_pwm(double* pwm, int ch); // pwm* array with doubles (0-1) ch number of values in pwm*;
	
private:
	int handle; // I2C handle for use with i2cfunc
	int num_channels;
};


#endif