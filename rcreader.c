#include "rcreader.h"
#include <stdint.h>
#include <cstdio>

rcreader::rcreader(){
	handle = 0;
	num_channels = 0;
}

rcreader::rcreader(int handle_, int num_channels_){
	handle = handle_;
	num_channels = num_channels_;
}


int rcreader::get_handle(){
	return handle;
}

void rcreader::set_handle(int handle_){
	handle = handle_;
}

int rcreader::get_num_channels(){
	return num_channels;
}

void rcreader::set_num_channels(int num_channels_){
	num_channels = num_channels_;
}

int rcreader::get_readings(int* channels){	
	unsigned char tmp[2*num_channels];	
	for(int i = 0; i < 2*num_channels; i++){
		tmp[i] = 0;
	}
	if(i2c_read(handle, tmp, 2*num_channels)){
		int vals[num_channels];
		for(int i = 0; i < num_channels; i++){
			channels[i] = tmp[2*i] << 8 | tmp[2*i+1];
		}
		return 1;
	}
	return 0;
}

void rcreader::parse_SBus(int* channels, double* SBus_channels_d){
	// This can be rewritten for better efficency!
	int SBus_buffer[20];
	for(int i = 0; i < 10; i++){
		SBus_buffer[2*i] = (channels[4 + i] & 0xFF00) >> 8;
		SBus_buffer[2*i + 1] = channels[4 + i] & 0x00FF;
	}
	
	SBus_channels_d[0]  = ((SBus_buffer[1] 			| SBus_buffer[2] << 8) 	& 0x07FF);
	SBus_channels_d[1]  = ((SBus_buffer[2] >> 3  	| SBus_buffer[3] << 5) 	& 0x07FF);
	SBus_channels_d[2]  = ((SBus_buffer[3] >> 6  	| SBus_buffer[4] << 2 	| SBus_buffer[5] << 10) & 0x07FF);
	SBus_channels_d[3]  = ((SBus_buffer[5] >> 1  	| SBus_buffer[6] << 7) 	& 0x07FF);
	SBus_channels_d[4]  = ((SBus_buffer[6] >> 4  	| SBus_buffer[7] << 4) 	& 0x07FF);
	SBus_channels_d[5]  = ((SBus_buffer[7] >> 7  	| SBus_buffer[8] << 1  	| SBus_buffer[9] << 9) 	& 0x07FF);
	SBus_channels_d[6]  = ((SBus_buffer[9] >> 2  	| SBus_buffer[10] << 6) & 0x07FF);
	SBus_channels_d[7]  = ((SBus_buffer[10] >> 5  	| SBus_buffer[11] << 3) & 0x07FF);
	SBus_channels_d[8]  = ((SBus_buffer[12] 			| SBus_buffer[13] << 8) & 0x07FF);
	SBus_channels_d[9]  = ((SBus_buffer[13] >> 3  	| SBus_buffer[14] << 5) & 0x07FF);
	SBus_channels_d[10] = ((SBus_buffer[14] >> 6  	| SBus_buffer[15] << 2 	| SBus_buffer[16] << 10) & 0x07FF);
	SBus_channels_d[11] = ((SBus_buffer[16] >> 1  	| SBus_buffer[17] << 7) & 0x07FF);
	SBus_channels_d[12] = (SBus_buffer[18] & 0b1000) >> 3; // Contains two digital channels on 0b0001 and 0b0010 as well as lost packet flag 0b0100 and failsafe active flag 0b1000
	
	for(int i = 0; i < 12; i++){
		SBus_channels_d[i] = (SBus_channels_d[i] - 352) / 1344;
	}
}
// set_pwm. Skickar fyra uint16_t-värden som 8 bytes över I2C till Arduinon. 
// Skifta bytes enligt arduino-koden. PWM-från Beaglen är 0.0-1.0. 

void rcreader::set_pwm(double* pwm, int ch){
	int pwm_us[ch];
	uint8_t buffer[ch*2];
	
	for(int i = 0; i < ch; i++){
		// Convert to cycle time
		if(pwm[i]<0){
			pwm[i]=0;
		}
		pwm_us[i] = (1000*pwm[i]+1000);  // (Val * (max_time - min_time))+min_time)
		//std::printf("Motor %i: %f => %i  ", i+1, pwm[i], pwm_us[i]);
		// Split data to write buffer
		buffer[2*i] = pwm_us[i] >> 8; // MSB right shift to LSB
		buffer[2*i + 1] = pwm_us[i] & 0xFF; // LSB. MSB masked out.
		//if(i==2){
		//std::printf("Motor 3. Value: %i \t %#x tMSB: %#x \tLSB: %#x", pwm_us[i], pwm_us[i], buffer[2*i], buffer[2*i+1]);}
	}
	//std::printf("\n");
	i2c_write(handle, buffer, 8);
}
				