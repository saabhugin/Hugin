#include "HMC5883L.h"
#include "i2cfunc.h"
#include <stdio.h>

HMC5883L::HMC5883L(){
	handle = 0;
}

HMC5883L::HMC5883L(int handle_){
	handle = handle_;
}

int HMC5883L::get_handle(){
	return handle;
}

void HMC5883L::set_handle(int handle_){
	handle = handle_;
}

void HMC5883L::init(){
	delay_ms(6); // Wait at least 5 ms after powerup before initializing.
	unsigned char tmp[1];
	tmp[0]= 0x70;
	i2c_write_pos(handle, tmp, 1, MAG_REG_A);
	set_gain(MAG_GAIN_3);
	delay_ms(100);
	set_mode(MAG_MODE_CONT);
}

void HMC5883L::set_gain(unsigned char gain){
	unsigned char tmp[1];
	tmp[0] = gain;
	i2c_write_pos(handle, tmp, 1, MAG_REG_B);
	gain_ = gain;
}

unsigned char HMC5883L::get_gain(){
	unsigned char tmp[1];
	i2c_read_pos(handle, tmp, 1, MAG_REG_B);
	return tmp[0];	
}

void HMC5883L::set_mode(unsigned char mode){
	/* Posible modes:
		0 - Continous sampling
		1 - Single mode
		2 - Idle mode
		*/	
	if (mode>2) {
		return;
	}
	i2c_write_pos(handle, &mode, 1, MAG_REG_MODE);
	delay_ms(100);
}

/*
void HMC5883L::reset(){
	i2c_write_bit(handle, PWR_MGMT_1_DEVICE_RESET, 1, PWR_MGMT_1);
	fs_acceleration = AFS_SEL_2G;
	fs_gyroscope = FS_SEL_250;
}

*/
int16_t HMC5883L::get_fs_magnetometer(){
	switch(gain_){
		case MAG_GAIN_0: return 1370;
		case MAG_GAIN_1: return 1090;
		case MAG_GAIN_2: return 820;
		case MAG_GAIN_3: return 660;
		case MAG_GAIN_4: return 440;
		case MAG_GAIN_5: return 390;
		case MAG_GAIN_6: return 330;
		case MAG_GAIN_7: return 230;
		default: return 1090;
	}
}

void HMC5883L::get_magnetometer_data(double *md){
	get_magnetometer_data(&md[0], &md[1], &md[2]);
}

/* Private Methods */

void HMC5883L::get_magnetometer_data(int16_t* mx, int16_t* my, int16_t* mz){
	unsigned char tmp[6];
	i2c_read_pos(handle, tmp, 6, MAG_OUT);
	// HMC5883l sends data in X,Z,Y-order.
	*mx = ((int16_t) tmp[0] << 8) | tmp[1];
	*mz = ((int16_t) tmp[2] << 8) | tmp[3];
	*my = ((int16_t) tmp[4] << 8) | tmp[5];
}

void HMC5883L::get_magnetometer_data(double* mdx, double* mdy, double* mdz){
	int16_t mx, my, mz;
	get_magnetometer_data(&mx, &my, &mz);
	double divider = get_fs_magnetometer();
	*mdx = (double)mx / divider;
	*mdy = (double)my / divider;
	*mdz = (double)mz / divider;
}
