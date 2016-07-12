 #include "rcreader.h"

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

// ask Arduino for SBUS and PWM signals 
int rcreader::get_readings(int channels[4]){	
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

// initializing the SBUS buffer, obtained through reversed engineering - complicated due to SBUS "secret" design 
void rcreader::parse_SBus(int* channels, double* SBus_channels_d){
	// This can be rewritten for better efficiency!
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
	SBus_channels_d[8]  = ((SBus_buffer[12] 		| SBus_buffer[13] << 8) & 0x07FF);
	SBus_channels_d[9]  = ((SBus_buffer[13] >> 3  	| SBus_buffer[14] << 5) & 0x07FF);
	SBus_channels_d[10] = ((SBus_buffer[14] >> 6  	| SBus_buffer[15] << 2 	| SBus_buffer[16] << 10) & 0x07FF);
	SBus_channels_d[11] = ((SBus_buffer[16] >> 1  	| SBus_buffer[17] << 7) & 0x07FF);
	SBus_channels_d[12] = (SBus_buffer[18] & 0b1000) >> 3; // Contains two digital channels on 0b0001 and 0b0010 as well as lost packet flag 0b0100 and fail safe active flag 0b1000
	
	for(int i = 0; i < 12; i++){
		SBus_channels_d[i] = (SBus_channels_d[i] - 352) / 1344;
	}
}


				