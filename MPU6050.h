#ifndef MPU6050_H
#define MPU6050_H

#include <cstdint>

#define INT16_T_MAX		32767

#define SELF_TEST_X		0x0D
#define SELF_TEST_Y		0x0E
#define SELF_TEST_Z		0x0F
#define SELF_TEST_A		0x10
#define SMPLRT_DIV		0x19
#define CONFIG 			0x1A
#define GYRO_CONFIG 		0x1B
#define ACCEL_CONFIG		0x1C
#define MOT_THR 			0x1F
#define FIFO_EN 			0x23
#define I2C_MST_CTRL 	0x24
#define I2C_SLV0_ADDR 	0x25
#define I2C_SLV0_REG 	0x26
#define I2C_SLV0_CTRL 	0x27
#define I2C_SLV1_ADDR 	0x28
#define I2C_SLV1_REG 	0x29
#define I2C_SLV1_CTRL 	0x2A
#define I2C_SLV2_ADDR 	0x2B
#define I2C_SLV2_REG 	0x2C
#define I2C_SLV2_CTRL 	0x2D
#define I2C_SLV3_ADDR 	0x2E
#define I2C_SLV3_REG 	0x2F
#define I2C_SLV3_CTRL 	0x30
#define I2C_SLV4_ADDR 	0x31
#define I2C_SLV4_REG 	0x32
#define I2C_SLV4_DO 		0x33
#define I2C_SLV4_CTRL 	0x34
#define I2C_SLV4_DI 		0x35
#define I2C_MST_STATUS 	0x36
#define INT_PIN_CFG 		0x37
#define INT_ENABLE 		0x38
#define INT_STATUS 		0x3A

#define ACCEL_OUT			0x3B
#define TEMP_OUT			0x41
#define GYRO_OUT			0x43

#define I2C_SLV0_DO 		0x63
#define I2C_SLV1_DO 		0x64
#define I2C_SLV2_DO 		0x65
#define I2C_SLV3_DO 		0x66
#define I2C_MST_DELAY_CTRL	0x67
#define SIGNAL_PATH_RESET 	0x68
#define USER_CTRL 		0x6A
#define PWR_MGMT_1 		0x6B
#define PWR_MGMT_2 		0x6C

#define PWR_MGMT_1_SLEEP			0x40
#define PWR_MGMT_1_DEVICE_RESET 	0x80

#define I2C_BYPASS_EN_BIT    0x02
#define USERCTRL_I2C_MST_EN_BIT		0x10


#define AFS_SEL_2G		0x00
#define AFS_SEL_4G		0x08
#define AFS_SEL_8G		0x10
#define AFS_SEL_16G		0x18
#define AFS_SEL			0x18

#define FS_SEL_250		0x00
#define FS_SEL_500		0x08
#define FS_SEL_1000		0x10
#define FS_SEL_2000		0x18
#define FS_SEL			0x18


class MPU6050{
	public:
	MPU6050();
	MPU6050(int handle_);
	
	void init();
	void reset();
	
	int get_handle();
	void set_handle(int handle_);
	
	int get_sleep_mode();
	void set_sleep_mode(int sleep_mode);	
	
	void set_range_acceleration(unsigned char range);
	unsigned char get_range_acceleration();
	int16_t get_fs_acceleration();

	void set_range_gyroscope(unsigned char range);
	unsigned char get_range_gyroscope();
	int16_t get_fs_gyroscope();
	void calibrate_gyroscope();
	
	void get_accelerations(int16_t *ax, int16_t *ay, int16_t *az);
	void get_accelerations(double *adx, double *ady, double *adz);
	void get_accelerations(double *ad);

	void get_angular_velocities(int16_t *gx, int16_t *gy, int16_t *gz);
	void get_angular_velocities(double *gdx, double *gdy, double *gdz);
	void get_angular_velocities(double *gd);

	int16_t get_raw_temperature();
	double get_temperature();
	
	
	private:
	int handle; // I2C handle for use with i2cfunc
	
	unsigned char fs_acceleration;
	unsigned char fs_gyroscope;
	
	double gox, goy, goz;
};
#endif