/*
 * Protocol for converting i2c to pwm 
 * using Adafruit PCA9685 pwm card
 * with 16 output pins (we use pin 0-3)
 *
 */

#ifndef PCA9685_H
#define PCA9685_H

#include "i2cfunc.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define PCA9685_MODE1 0x0
#define PCA9685_MODE2 0x1
#define PCA9685_PRESCALE 0xFE
#define PCA9685_LED0_ON 0x6

// Hard limits for test bench servos
#define SERVOMIN   110
#define SERVOMAX   470

class PCA9685{

public:
	PCA9685();
	PCA9685(int handle_);
	void init(int freq_); // min freq 24 Hz
	void reset();
	void set_freq(int freq_);
	//unsigned int get_freq();
	void signal(double ctrlSignal[4]);
	void signal_s(double ctrlSignal, int servoNum);
	void set_OE();

private:
	int pwmFreq;
	int handle;	
	int servoMin[4]; 
	int servoMax[4];
	void pwm_write(unsigned int on, unsigned int off[4]);
	void pwm_write_single(unsigned int on, unsigned int off, int servoNum);
	unsigned int pwmPulse[4];
	unsigned int pwmPulse_s;
	//int pwm_read();
};

#endif 