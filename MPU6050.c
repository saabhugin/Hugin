#include "MPU6050.h"
#include "i2cfunc.h"
#include <stdio.h>

MPU6050::MPU6050(){
	handle = 0;
}

MPU6050::MPU6050(int handle_){
	handle = handle_;
	gox = 0;
	goy = 0;
	goz = 0;
}


int MPU6050::get_handle(){
	return handle;
	gox = 0;
	goy = 0;
	goz = 0;
}

void MPU6050::set_handle(int handle_){
	handle = handle_;
	gox = 0;
	goy = 0;
	goz = 0;
}


int MPU6050::get_sleep_mode(){
	int val = 0;
	i2c_read_bit(handle, PWR_MGMT_1_SLEEP, &val, PWR_MGMT_1);
	return val;
}

void MPU6050::set_sleep_mode(int mode){
	i2c_write_bit(handle, PWR_MGMT_1_SLEEP, mode, PWR_MGMT_1);
}


void MPU6050::init(){	
	set_sleep_mode(0);
	set_range_acceleration(AFS_SEL_2G);
	set_range_gyroscope(FS_SEL_250);
	fs_acceleration = AFS_SEL_2G;
	fs_gyroscope = FS_SEL_250;
}

void MPU6050::reset(){
	i2c_write_bit(handle, PWR_MGMT_1_DEVICE_RESET, 1, PWR_MGMT_1);
	fs_acceleration = AFS_SEL_2G;
	fs_gyroscope = FS_SEL_250;
}


void MPU6050::set_range_acceleration(unsigned char range){
	unsigned char tmp[1];
	i2c_read_pos(handle, tmp, 1, ACCEL_CONFIG);
	tmp[0] &= ~AFS_SEL;
	tmp[0] |= range;
	i2c_write_pos(handle, tmp, 1, ACCEL_CONFIG);
	fs_acceleration = range;
}

unsigned char MPU6050::get_range_acceleration(){
	unsigned char tmp[1];
	i2c_read_pos(handle, tmp, 1, ACCEL_CONFIG);
	tmp[0] &= AFS_SEL;
	return tmp[0];
}

int16_t MPU6050::get_fs_acceleration(){
	switch(fs_acceleration){
		case AFS_SEL_2G: return 2;
		case AFS_SEL_4G: return 4;
		case AFS_SEL_8G: return 8;
		case AFS_SEL_16G: return 16;
		default: return 2;
	}
}


void MPU6050::set_range_gyroscope(unsigned char range){
	unsigned char tmp[1];
	i2c_read_pos(handle, tmp, 1, GYRO_CONFIG);
	tmp[0] &= ~FS_SEL;
	tmp[0] |= range;
	i2c_write_pos(handle, tmp, 1, GYRO_CONFIG);
	fs_gyroscope = range;
}

unsigned char MPU6050::get_range_gyroscope(){
	unsigned char tmp[1];
	i2c_read_pos(handle, tmp, 1, GYRO_CONFIG);
	tmp[0] &= FS_SEL;
	return tmp[0];	
}

int16_t MPU6050::get_fs_gyroscope(){
	switch(fs_gyroscope){
		case FS_SEL_250: return 250;
		case FS_SEL_500: return 500;
		case FS_SEL_1000: return 1000;
		case FS_SEL_2000: return 2000;
		default: return 250;
	}
}

void MPU6050::calibrate_gyroscope(){
	double gx = 0, gy = 0, gz = 0;
	double gsx = 0, gsy = 0, gsz = 0;
	int num_cals = 1000;
	for(int i = 0; i < num_cals; i++){
		gx = 0; gy = 0; gz = 0;
		get_angular_velocities(&gx, &gy, &gz);
		gsx += gx;
		gsy += gy;
		gsz += gz;
	}
	gox = gsx / num_cals;
	goy = gsy / num_cals;
	goz = gsz / num_cals;
}


void MPU6050::get_accelerations(int16_t* ax, int16_t* ay, int16_t* az){
	unsigned char tmp[6];
	i2c_read_pos(handle, tmp, 6, ACCEL_OUT);
	*ax = ((int16_t) tmp[0] << 8) | tmp[1];
	*ay = ((int16_t) tmp[2] << 8) | tmp[3];
	*az = ((int16_t) tmp[4] << 8) | tmp[5];
}

void MPU6050::get_accelerations(double* adx, double* ady, double* adz){
	int16_t ax, ay, az;
	get_accelerations(&ax, &ay, &az);
	double divider = (double)(INT16_T_MAX)/get_fs_acceleration();
	*adx = ax / divider;
	*ady = ay / divider;
	*adz = az / divider;
}

void MPU6050::get_accelerations(double *ad){
	get_accelerations(&ad[0], &ad[1], &ad[2]);
}


void MPU6050::get_angular_velocities(int16_t *gx, int16_t *gy, int16_t *gz){
	unsigned char tmp[6];
	i2c_read_pos(handle, tmp, 6, GYRO_OUT);
	*gx = ((int16_t) tmp[0] << 8) | tmp[1];
	*gy = ((int16_t) tmp[2] << 8) | tmp[3];
	*gz = ((int16_t) tmp[4] << 8) | tmp[5];
}

void MPU6050::get_angular_velocities(double *gdx, double *gdy, double *gdz){
	int16_t gx = 0, gy = 0, gz = 0;
	get_angular_velocities(&gx, &gy, &gz);
	double divider = (double)(INT16_T_MAX)/((double)get_fs_gyroscope());
	*gdx = (gx / divider) - gox;
	*gdy = (gy / divider) - goy;
	*gdz = (gz / divider) - goz;
}

void MPU6050::get_angular_velocities(double *gd){
	get_angular_velocities(&gd[0], &gd[1], &gd[2]);
}


int16_t MPU6050::get_raw_temperature(){
	unsigned char tmp[2];
	i2c_read_pos(handle, tmp, 2, TEMP_OUT);
	return ((int16_t) tmp[0] << 8) | tmp[1];
}

// Returns degrees celcius as according to Invensense MPU6050 datasheet
double MPU6050::get_temperature(){
	return get_raw_temperature()/340.0 + 36.53;
}