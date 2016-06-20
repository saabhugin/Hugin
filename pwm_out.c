#include "i2cfunc.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6

// Limits for test bench servos
#define SERVOMIN1  110 
#define SERVOMAX1  470 

#define SERVOMIN2  125
#define SERVOMAX2  485 

#define SERVOMIN3  120 
#define SERVOMAX3  480 

#define SERVOMIN4  115 
#define SERVOMAX4  475 

void pwm_out::set_servoval() {
	servoval[0][0] = SERVOMIN1; servoval[0][1] = SERVOMAX1;
	servoval[1][0] = SERVOMIN2; servoval[1][1] = SERVOMAX2;
	servoval[2][0] = SERVOMIN3; servoval[2][1] = SERVOMAX3;
	servoval[3][0] = SERVOMIN4; servoval[3][1] = SERVOMAX4;
}

void pwm_out::reset(int pwm_handle){
	// write8(PCA9685_MODE1, 0x0);
	unsigned char buffer[1];
	buffer[0] = 0x00;
	i2c_write_pos(pwm_handle, buffer, 1, PCA9685_MODE1);
}

void pwm_out::set_freq(float freq, int pwm_handle){
  freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;
  unsigned char prescale = floor(prescaleval + 0.5);

  // uint8_t oldmode = read8(PCA9685_MODE1);
  unsigned char buffer[1];
  i2c_read_pos(pwm_handle, buffer, 1, PCA9685_MODE1);
  unsigned char oldmode = buffer[0];
  unsigned char newmode = (oldmode&0x7F) | 0x10; // sleep

	// write8(PCA9685_MODE1, newmode); // go to sleep
	buffer[0] = newmode;
	i2c_write_pos(pwm_handle, buffer, 1, PCA9685_MODE1);

	// write8(PCA9685_PRESCALE, prescale); // set the prescaler
	buffer[0] = prescale;
	i2c_write_pos(pwm_handle, buffer, 1, PCA9685_PRESCALE);

	// write8(PCA9685_MODE1, oldmode);
	buffer[0] = oldmode;
	i2c_write_pos(pwm_handle, buffer, 1, PCA9685_MODE1);

	// delay(5);
	usleep(5000);
	buffer[0] = oldmode | 0xa1;
	i2c_write_pos(pwm_handle, buffer, 1, PCA9685_MODE1);
	//  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);
}

void pwm_out::set(unsigned int on, unsigned int foff[4], int pwm_handle) {
  // Sending i2c to all pins 0-3 
  unsigned char buffer[20];
  for(int i = 0; i < 20; i+=5) {
	buffer[i] = LED0_ON_L+4*i;
	buffer[i+1] = on;
	buffer[i+2] = on>>8;
	buffer[i+3] = foff[i];
	buffer[i+4] = foff[i]>>8;
  }
	i2c_write(pwm_handle, buffer, 20);
}

void pwm_out::set_pin(unsigned char num, unsigned int val, bool invert, int pwm_handle)
{
  // Clamp value between 0 and 4095 inclusive.
  if(4095 < val) val = 4095;
  if (invert) {
    if (val == 0) {
      // Special value for signal fully on.
      pwm_out.set(num, 4096, 0, pwm_handle);
    }
    else if (val == 4095) {
      // Special value for signal fully off.
      pwm_out.set(num, 0, 4096, pwm_handle);
    }
    else {
      pwm_out.set(num, 0, 4095-val, pwm_handle);
    }
  }
  else {
    if (val == 4095) {
      // Special value for signal fully on.
      pwm_out.set(num, 4096, 0, pwm_handle);
    }
    else if (val == 0) {
      // Special value for signal fully off.
      pwm_out.set(num, 0, 4096, pwm_handle);
    }
    else {
      pwm_out.set(num, 0, val, pwm_handle);
    }
  }
}

void pwm_out::signal(double ctrl_signal[4], int pwm_handle){	
	// Translating the control signal to pwm pulse signal 
	int pwm_pulse[4];
	for(int i = 0; i<4; i++) {
		pwm_pulse[i] = servoval[i][0] + 360*ctrl_signal[i];		// servomin + percent of interval between max and min, 360 corresponds to 180 - wrong scale somewhere...
		if(pwm_pulse[i] > servoval[i][1]) {						// checking servomax is not exceeded, bad for servo 
			pwm_pulse[i] = servoval[i][1];
		}
		if(pwm_pulse[i] < servoval[i][0]) {
			pwm_pulse[i] = servoval[i][0];
		} 
	}
		pwm_set(0, pulselen, pwm_handle);	// pwm signal out to pin 0-3 simultaneously, (start, stop, address)
	}
			
	}