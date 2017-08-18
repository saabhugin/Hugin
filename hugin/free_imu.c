#include "free_imu.h"

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <sys/ioctl.h>
#include <time.h>

static int fd; // file descriptor for the I2C bus
static signed char gyro_orientation[9] = {1,  0,  0,
        0, 1,  0,
        0,  0,  1};

int get_imu_data(float* angles){
	short accel[3], gyro[3], sensors[1];
    long quat[4];
    unsigned long timestamp;
    unsigned char more[0];
	
	int fifo_read = dmp_read_fifo(gyro, accel, quat, &timestamp, sensors, more);
    if (fifo_read != 0){
			return -1;
        }
		
	// rescale the quaternion values recieved from the IMU from longs to floats	
	rescale_l(quat, angles+9, QUAT_SCALE, 4);
	
	// rotate quaternion 180 degrees around x-axis
	float quat_rotation[4] = {0, 1, 0, 0};
	q_multiply(quat_rotation, angles+9, angles+9);	
	
	// rescale the gyro and accel values received from the IMU from shorts to floats
    rescale_s(gyro, angles+3, GYRO_SCALE, 3);
    rescale_s(accel, angles+6, ACCEL_SCALE, 3);
    // turn the quaternation (that is already in angles) into euler angles and store it in the angles array
    euler(angles+9, angles);
	
	return 0;
}

int init_imu(){
	open_bus();
	unsigned char whoami=0;
    i2c_read(MPU6050_ADDR, MPU6050_WHO_AM_I, 1, &whoami);
	
	struct int_param_s int_param;
	unsigned short dmp_features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL;
	
	if(	mpu_init(&int_param) || 
		mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL) ||
		mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL) ||
		dmp_load_motion_driver_firmware() ||
		dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)) ||
		dmp_enable_feature(dmp_features) || 
		dmp_set_fifo_rate(DEFAULT_MPU_HZ) ||
		mpu_set_dmp_state(1)
		){
		
		printf("Error initialzing IMU!");
		return -1; 
		}
	
	return 0;
}

int i2c_write(unsigned char slave_addr, unsigned char reg_addr,
        unsigned char length, unsigned char const *data){
    unsigned char tmp[length+1];
    tmp[0] = reg_addr;
    memcpy(tmp+1, data, length);
    if (write(fd, tmp, length+1) != length + 1){
        return -1;
    }
    return 0;
}
int i2c_read(unsigned char slave_addr, unsigned char reg_addr,
        unsigned char length, unsigned char *data){
    if (write(fd,&reg_addr, 1) != 1){
        return -1;
    }
    if  (read(fd,data, length) != length){
        return -2;
    }

    return 0;
}

int open_bus() {
    if ((fd = open(BBB_I2C_FILE, O_RDWR)) < 0) {
        /* ERROR HANDLING: you can check errno to see what went wrong */
        perror("Failed to open the i2c bus");
        return 1;
    }
    if (ioctl(fd, I2C_SLAVE, MPU6050_ADDR) < 0) {
        perror("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        return 1;
    }
    return 0;
}

// multiply two quaternions
int q_multiply(float* q1, float* q2, float* result) {
    float tmp[4];
    tmp[0] = q1[0]*q2[0] - q1[1]*q2[1] - q1[2]*q2[2] - q1[3]*q2[3];
    tmp[1] = q1[0]*q2[1] + q1[1]*q2[0] + q1[2]*q2[3] - q1[3]*q2[2];
    tmp[2] = q1[0]*q2[2] - q1[1]*q2[3] + q1[2]*q2[0] + q1[3]*q2[1];
    tmp[3] = q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1] + q1[3]*q2[0];
    memcpy(result, tmp, 4*sizeof(float));
    return 0;
}

// rescale an array of longs by scale factor into an array of floats
int rescale_l(long* input, float* output, float scale_factor, char length) {
    int i;
    for(i=0;i<length;++i)
        output[i] = input[i] * scale_factor;
    return 0;
}

// rescale an array of shorts by scale factor into an array of floats
int rescale_s(short* input, float* output, float scale_factor, char length) {
    int i;
    for(i=0;i<length;++i)
        output[i] = input[i] * scale_factor;
    return 0;
}

void delay_ms(unsigned long num_ms){

}
void get_ms(unsigned long *count){

}
void reg_int_cb(struct int_param_s *param){

}

inline int min ( int a, int b ){
    return a < b ? a : b;
}
inline void __no_operation(){

}

// turn quaternions into yaw/pitch/roll
void euler(float* q, float* euler_angles) {	
	euler_angles[2]  = atan2(2.0 * (q[3] * q[2] + q[0] * q[1]) , 1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2])); //roll
	euler_angles[1] = asin(2.0 * (q[2] * q[0] - q[3] * q[1])); // pitch
	euler_angles[0]   = atan2(2.0 * (q[3] * q[0] + q[1] * q[2]) , - 1.0 + 2.0 * (q[0] * q[0] + q[1] * q[1])); //yaw
}

// Functions for setting gyro/accel orientation
unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}