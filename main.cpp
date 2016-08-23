/* main.cpp
 *
 * main file for hugin c-program
 * 
 * Initializes the system, then waits for pace keeper to be recieved via UDP from Simulink (main.elf)
 *
 * When pace keeper is recieved, new PWM signals is commanded (if desired, comment or uncomment line bellow)
 * The the sensors are sampled and the PWM/SBUS is read from ATmega. 
 * 
 * Finally the sensor values and PWM/SBUS readings is sent to main.elf via UDP. 
 */

#include <stdio.h>
#include <unistd.h>

#include "MPU6050.h"
#include "HMC5883L.h"
#include "i2cfunc.h"
#include "bsocket.h"
#include "rcreader.h"
#include "led.h"
#include "PCA9685.h"

int main(){
	// Create socket and set listen timeout
	bsocket sock(65536);
	sock.set_listen_timeout(1000);
	unsigned int data_size = 0;
	
	// Values that are updated from socket
	const int num_socket_vals = 2;
	socket_val socket_vals[num_socket_vals] = {
		socket_val(INTEGER, 25001, 1, "Ready val"),
		socket_val(DOUBLE, 25002, 4, "PWM out")
	};
	
	// Initialise RC reader - Reads PWM and S.Bus signals from the receiver via the Atmega's I2C.
	const int num_channels = 15; // 4 PWM channels, 12 SBus channels and one SBus info byte with 2 digital values, packet loss and failsafe flag.
	const int num_sbus_channels = 13;
	const int num_pwm_channels = 4;
	rcreader rcr(i2c_open(1, 0x05), num_channels);
	int channels[num_channels];
	double pwm_readings_d[num_pwm_channels];
	double sbus_channels_d[num_sbus_channels];
	usleep(50000);
	
	// Initialise IMU
	MPU6050 imu(i2c_open(1, 0x68));
	imu.init();
	
	imu.set_range_acceleration(AFS_SEL_8G); // Change accelerometer range. 2G was not enough, 8G works!
	usleep(50000); // Makes sure the IMU with gyro is up and running (min 30 ms)
	
	// Initialize magnetometer (part of FreeIMU)
	HMC5883L mag(i2c_open(1,MAG_ADDR));
	mag.init();
	usleep(50000);

	// Declare values to hold IMU readings
	double acc_d[3];
	double gyro_d[3];
	double mag_d[3];
	
	
	// Init LED
	int light = 1;
	int led_counter = 0;
	led_init();
	led_write(light);
	
	// Init PWM 
	PCA9685 pwm_out(i2c_open(1, 0x40));
	usleep(50000);
	pwm_out.init(50);	
	double ctrl_signal[4] = {0,0,0,0};
	pwm_out.signal(ctrl_signal);
	
	// INITIALIZATION COMPLETED
	printf("Hugin program started!\n");
	while(1){
		// Listen for packets and process if new packets have arrived
		data_size = sock.listen();
		if(data_size > 0){
			sock.process_packet(data_size, socket_vals, num_socket_vals);
			// Ready to receive
			
			// Pace keeper packet received
			if(socket_vals[0].i_vals[0] == 1){
				socket_vals[0].i_vals[0] = 0;  // reset the flag, i_vals accesses the ready signal
				
				// Set PWM outputs
				// Test to use throttle as output for every motor
				for(int i= 0; i<4; i++){
					ctrl_signal[i]=socket_vals[1].d_vals[3];
				}
				pwm_out.signal(ctrl_signal);
				
				// Get IMU readings
				imu.get_accelerations(acc_d);
				imu.get_angular_velocities(gyro_d);	
				mag.get_magnetometer_data(mag_d);
				
				
				// Get RC readings
				rcr.get_readings(channels);
				for(int i = 0; i < 4; i++){
					// From range 900-2100 to 0.0-1.0 
					pwm_readings_d[i] = ((double)(channels[i]-900))/1200.0;  // (Val - min_time) / (max_time - min_time)
				}
				rcr.parse_SBus(channels, sbus_channels_d);
				
				// Send updates via UDP
				sock.send(LOCAL_HOST, 22001, acc_d, 3);
				sock.send(LOCAL_HOST, 22002, gyro_d, 3);
				sock.send(LOCAL_HOST, 22003, mag_d, 3);
			//	sock.send(LOCAL_HOST, 22006, distance, 1); // Socket 22006 is used for distance sensor. 
				sock.send(LOCAL_HOST, 22101, sbus_channels_d, num_sbus_channels);
				sock.send(LOCAL_HOST, 22102, pwm_readings_d, num_pwm_channels);
								
				// Blink LED every 10th sent package
				led_counter++;
				if(led_counter > 10){
					light = !light;
					led_write(light);
					led_counter=0;
				}
			}
		}
	}
}
