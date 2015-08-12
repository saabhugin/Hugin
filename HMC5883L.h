#ifndef HMC5883L_H
#define HMC5883L_H
#include <cstdint>

#define INT16_T_MAX		32767

#define MAG_ADDR		0x1E

#define MAG_REG_A		0x00
#define MAG_REG_B		0x01
#define MAG_REG_MODE	0x02
#define MAG_OUT 		0x03

#define MAG_MODE_SINGLE	0x01
#define MAG_MODE_CONT	0x00

#define MAG_GAIN_0  	0x00
#define MAG_GAIN_1  	0x20
#define MAG_GAIN_2  	0x40
#define MAG_GAIN_3  	0x60
#define MAG_GAIN_4  	0x80
#define MAG_GAIN_5  	0xA0
#define MAG_GAIN_6  	0xC0
#define MAG_GAIN_7  	0xE0


class HMC5883L{
	public:
	HMC5883L();
	HMC5883L(int handle_);
	
	void init();
	//void reset();
	unsigned char get_gain();
	void set_gain(unsigned char gain);
	void set_mode(unsigned char mode);
	
	int get_handle();
	void set_handle(int handle_);
	
	int16_t get_fs_magnetometer();

	
	void get_magnetometer_data(double *md);	
	
	private:
	
	void get_magnetometer_data(int16_t *mx, int16_t *my, int16_t *mz);
	void get_magnetometer_data(double *mdx, double *mdy, double *mdz);
	
	int handle; // I2C handle for use with i2cfunc
	
	unsigned char gain_;
	
};

#endif