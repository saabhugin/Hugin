#include "rcreader.h"
#include <stdint.h>

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

int rcreader::get_readings(unsigned int* channels){	
	unsigned char tmp[2*num_channels];	
	for(int i = 0; i < 2*num_channels; i++){
		tmp[i] = 0;
	}
	if(i2c_read(handle, tmp, 2*num_channels)){
		unsigned int vals[num_channels];
		for(int i = 0; i < num_channels; i++){
			channels[i] = tmp[2*i] << 8 | tmp[2*i+1];
		}
		return 1;
	}
	return 0;
}