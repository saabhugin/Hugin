#include <iostream>
#include "i2cfunc.h"
#include "PCA9685.h"
#include "GPIO.h"
#include "rcreader.h"


int main() {
	// initialization 
	PCA9685 pwm_out(i2c_open(1, 0x40));
	pwm_out.init(50);
	
	GPIO OE(49);
	OE.init(1, 0);
	
	double ctrlSignal[4];
	/*int counter = 0;
	int sum = 0;*/
	while(1) {
		// Automatic signal 
		for(int i = 0; i<4; i++) {
			ctrlSignal[i] = 0;
		}
		pwm_out.signal(ctrlSignal);
		usleep(1000000);
		for(int i = 0; i<4; i++) {
			ctrlSignal[i] = 0.5;
		}
		pwm_out.signal(ctrlSignal);
		usleep(500000);
		for(int i = 0; i<4; i++) {
			ctrlSignal[i] = 1;
		}
		pwm_out.signal(ctrlSignal);
		usleep(500000);
		
		// Manual input 
		/*std::cout << "Enter a control signal between 0 and 1: \n" ;
		for(int i=0; i<4; i++) {
			std::cout << "Servo " << i+1 << ": "; 
			std::cin >> ctrlSignal[i];
			sum += ctrlSignal[i];
		}
		if(sum > 3) {
			counter++;
		}
		else {
			counter = 0;
		}
		// PWM outputs
		if(counter > 2) {
			OE.write(1);
		}
		else {
			OE.write(0);
		}
		pwm_out.signal(ctrlSignal);
		//sum = 0;*/
		
	}
}