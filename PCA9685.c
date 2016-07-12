#include "PCA9685.h"


PCA9685::PCA9685() {
	handle = 0;
}

PCA9685::PCA9685(int handle_) {
	handle = handle_;
}

void PCA9685::init(int freq_) {
	pwmFreq = freq_;
	// Modified limits each servo 
	servoMin[0] = SERVOMIN; 
	servoMin[1] = SERVOMIN + 15; 
	servoMin[2] = SERVOMIN + 5; 
	servoMin[3] = SERVOMIN + 10; 
	servoMax[0] = SERVOMAX; 
	servoMax[1] = SERVOMAX + 15; 
	servoMax[2] = SERVOMAX + 5; 
	servoMax[3] = SERVOMAX + 10;
	reset();
	set_freq(pwmFreq);
}

void PCA9685::reset(){
	unsigned char buffer[1];
	buffer[0] = 0x00;
	i2c_write_pos(handle, buffer, 1, PCA9685_MODE1);
}

void PCA9685::set_freq(int freq){
	freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
	float prescaleval = 25000000;		// internal oscillator clock 25 MHz
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;		// want 0 to 4095 inclusive
	unsigned char prescale = floor(prescaleval + 0.5);

	unsigned char buffer[1];
	i2c_read_pos(handle, buffer, 1, PCA9685_MODE1);
	unsigned char oldmode = buffer[0];
	unsigned char newmode = (oldmode&0x7F) | 0x10;

	buffer[0] = newmode;
	i2c_write_pos(handle, buffer, 1, PCA9685_MODE1);

	buffer[0] = prescale;
	i2c_write_pos(handle, buffer, 1, PCA9685_PRESCALE);

	buffer[0] = oldmode;
	i2c_write_pos(handle, buffer, 1, PCA9685_MODE1);

	usleep(5000);
	buffer[0] = oldmode | 0xa1;
	i2c_write_pos(handle, buffer, 1, PCA9685_MODE1);
}

// Sending one i2c signal to 4 servos - not tested
/* 
void PCA9685::pwm_write(unsigned int on, unsigned int off[4]) {
	// Sending i2c to all pins 0-3 
	unsigned char buffer[17];
	buffer[0] = PCA9685_LED0_ON;
	for(int i = 0; i < 4; i++) {
		buffer[i*4+1] = on & 0xFF;
		buffer[i*4+2] = on>>8;
		buffer[i*4+3] = off[i] & 0xFF;
		buffer[i*4+4] = off[i]>>8;
  }
	i2c_write(handle, buffer, 17);
}*/

// Sending 4 i2c signals to 4 servos
void PCA9685::pwm_write(unsigned int on, unsigned int off[4]) {
	unsigned char buffer[5];
	for(int i = 0; i<4; i++) {
		buffer[0] = PCA9685_LED0_ON + i*4;
		buffer[1] = on & 0xFF;
		buffer[2] = on>>8;
		buffer[3] = off[i] & 0xFF;
		buffer[4] = off[i]>>8;
		i2c_write(handle, buffer, 5);
		usleep(5);
	}
}

void PCA9685::signal(double ctrlSignal[4]) {	
	// Translating the control signal to pwm pulse
	unsigned int pwmPulse[4];
	for(int i = 0; i<4; i++) {
		pwmPulse[i] = servoMin[i] + 360*ctrlSignal[i];
		// checking servoMax is not exceeded,
		if(pwmPulse[i] > servoMax[i]) {
			pwmPulse[i] = servoMax[i];
		}
		// checking servoMin is not exceeded,
		if(pwmPulse[i] < servoMin[i]) {		
			pwmPulse[i] = servoMin[i];
		} 
	}
		pwm_write(0, pwmPulse);	// pwm signal out to pin 0-3 simultaneously, (start, stop)
}

// Predefined setting for OE pin, the system will stop when OE is HIGH
// Note that this is the default value, possible values are 00, 01, 10, 11, see PCA9685 data sheet for function
void PCA9685::set_OE() {
	unsigned char bit_pos_val_ = 0b00000011;
	i2c_write_bit(handle, bit_pos_val_, 0, PCA9685_MODE2);
}
