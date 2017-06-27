#include "PCA9685.h"


PCA9685::PCA9685() {
	handle_ = 0;
}

PCA9685::PCA9685(int handle) {
	handle_ = handle;
}

void PCA9685::init(int freq) {
	pwmFreq_ = freq;
	reset();
	set_freq(pwmFreq_);
}

void PCA9685::reset(){
	unsigned char buffer[1];
	buffer[0] = 0x00;
	i2c_write_pos(handle_, buffer, 1, PCA9685_MODE1);
}

void PCA9685::set_freq(int freq){
	freq *= 0.9;  //" Correct for overshoot in the frequency setting" - Copied from the internetz. needs to be investigated further.
	float prescaleval = 25000000;		// internal oscillator clock for PWM card is 25 MHz 
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;		// want 0 to 4095 inclusive
	unsigned char prescale = floor(prescaleval + 0.5);

	unsigned char buffer[1];
	i2c_read_pos(handle_, buffer, 1, PCA9685_MODE1);
	unsigned char oldmode = buffer[0];
	unsigned char newmode = (oldmode&0x7F) | 0x10;

	buffer[0] = newmode;
	i2c_write_pos(handle_, buffer, 1, PCA9685_MODE1);

	buffer[0] = prescale;
	i2c_write_pos(handle_, buffer, 1, PCA9685_PRESCALE);

	buffer[0] = oldmode;
	i2c_write_pos(handle_, buffer, 1, PCA9685_MODE1);

	usleep(5000);
	buffer[0] = oldmode | 0xa1;
	i2c_write_pos(handle_, buffer, 1, PCA9685_MODE1);
	
	//calculate resolution of pulse bit
	resolution_ = 1000000; // 1e6 micro seconds = one second
	resolution_=resolution_/pwmFreq_; // maximum pulselength = 1e6/fequency in microseconds
	resolution_=resolution_/4096;		// calculate time per bit. 12 bits = 4096
}

// Sending one long i2c signal to all servos - not tested
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
	i2c_write(handle_, buffer, 17);
}*/

// Sending separate i2c signals to all servos, on and off are given in micro seconds
void PCA9685::pwm_write(unsigned int on_us, unsigned int off_us[4]) {
	unsigned int on = on_us/resolution_; // convert microseconds to bytes
	unsigned int off = 0;
	unsigned char buffer[5];
	// i2c can only send 1 byte at a time, message is address(1)+on(2)+off(2) = 5 bytes 
	// sending one message per servo (4) 
	for(int i = 0; i<4; i++) {
		off = (unsigned int)fmin(off_us[i]/resolution_, 4095);
		buffer[0] = PCA9685_LED0_ON + i*4;
		buffer[1] = on & 0xFF;
		buffer[2] = on>>8;
		buffer[3] = off & 0xFF;
		buffer[4] = off>>8;
		i2c_write(handle_, buffer, 5);
		usleep(5);
	}
}


// Sending i2c signal to one servo
void PCA9685::pwm_write_single(unsigned int on_us, unsigned int off_us, int servoNum) {
	unsigned int on = on_us/resolution_;
	unsigned int off = off_us/resolution_;
	unsigned char buffer[5];
	buffer[0] = PCA9685_LED0_ON + 4*servoNum;
	buffer[1] = on & 0xFF;
	buffer[2] = on>>8;
	buffer[3] = off & 0xFF;
	buffer[4] = off>>8;
	i2c_write(handle_, buffer, 5);
	usleep(5);
}

// Sending a control signal to all servos
void PCA9685::signal(double ctrlSignal[4]) {	
	// Translating the control signal to pwm pulse
	for(int i = 0; i<4; i++) {
		pwmPulse[i] = SERVOMIN + (SERVOMAX-SERVOMIN)*ctrlSignal[i];
		// checking servoMax is not exceeded,
		if(pwmPulse[i] > SERVOMAX) {
			pwmPulse[i] = SERVOMAX;
		}
		// checking servoMin is not exceeded,
		if(pwmPulse[i] < SERVOMIN) {		
			pwmPulse[i] = SERVOMIN;
		} 
	}
	pwm_write(0, pwmPulse);	// pwm signal out to pin 0-3 simultaneously, (start, stop)
}

// Sending a control signal to one servo 
void PCA9685::signal_s(double ctrlSignal, int servoNum) {	
	// Translating the control signal to pwm pulse
	pwmPulse_s = SERVOMIN + (SERVOMAX-SERVOMIN)*ctrlSignal;
	// checking servoMax is not exceeded,
	if(pwmPulse_s > SERVOMAX) {
		pwmPulse_s = SERVOMAX;
	}
	// checking servoMin is not exceeded,
	if(pwmPulse_s < SERVOMIN) {		
		pwmPulse_s = SERVOMIN;
	} 
	pwm_write_single(0, pwmPulse_s, servoNum);
}


// Predefined setting for OE pin, the system will stop when OE is HIGH
// Note that this is the default value, possible values are:
// 00 when OE=1 LEDN=0
// 01 when OE=1 LEDn=1 when OUTDRV=1 or LEDn=high-impedance when OUTDRV=0
// 1X when OE=1 LEDn=high-impedance
void PCA9685::set_OE() {
	unsigned char bit_pos_val_ = 0b00000011;
	i2c_write_bit(handle_, bit_pos_val_, 0, PCA9685_MODE2);
}
