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

#define PCA9685_MODE1 0x0		// mode register 1 for i2c communication
#define PCA9685_MODE2 0x1		// mode register 2 for output enable function
#define PCA9685_PRESCALE 0xFE	// prescaler for PWM output frequency setting
#define PCA9685_LED0_ON 0x6		// PWM signal output port 0 pin 0 (i.e. first servo/motor), the rest are accessed in a for loop i=0:3, see pwm_write()

// Hard limits for test bench servos
#define SERVOMIN   600
#define SERVOMAX   2400

// Hard limits for Hugin speed controllers
//#define SERVOMIN 1000
//#define SERVOMAX 2000

class PCA9685{

public:
	PCA9685();
	PCA9685(int handle);
	void init(int freq); // min freq 24 Hz
	void reset();
	void set_freq(int freq);
	void signal(double ctrlSignal[4]);
	void signal_s(double ctrlSignal, int servoNum);
	void set_OE();

private:
	int pwmFreq_;
	int handle_;	
	void pwm_write(unsigned int on_us, unsigned int off_us[4]);
	void pwm_write_single(unsigned int on_us, unsigned int off_us, int servoNum);
	unsigned int pwmPulse[4];
	unsigned int pwmPulse_s;
	double resolution_;
};

#endif 