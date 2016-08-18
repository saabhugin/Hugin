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
#include <chrono>
#include "MPU6050.h"
#include "HMC5883L.h"
#include "i2cfunc.h"
#include "bsocket.h"
#include "rcreader.h"
#include "VC01.h"
#include "led.h"
#include "PCA9685.h"
#include "GPIO.h"

// to use the timer class just uncomment these two and remove <time.h>
//#include <chrono>
//#include "timer.h"
#include<time.h>


int main(){	
	// Create socket and set listen time out
	bsocket sock(65536);
	sock.set_listen_timeout(1000);
	unsigned int data_size;
	
	// Values that are updated from socket
	const int num_socket_vals = 2;
	socket_val socket_vals[num_socket_vals] = {
		socket_val(INTEGER, 25001, 1, "Ready val"),
		socket_val(DOUBLE, 25002, 4, "PWM out")
	};
	
	// Initialise RC reader - Reads PWM and S.Bus signals from the receiver via the Atmega's I2C.
	const int num_channels = 15; // 4 PWM channels, 12 SBus channels and one SBus info byte with 2 digital values, packet loss and failsafe flag.
	const int num_sbus_channels = 13;
	int sbus_size;
	rcreader rcr(i2c_open(1, 0x05), num_channels);
	int channels[num_channels];
	double ext_channels_d[4];
	double sbus_channels_d[num_sbus_channels];
	int print_counter = 0;
	usleep(50000);
	
	// Initialise IMU
	MPU6050 imu(i2c_open(1, 0x68));
	imu.init();
	
	imu.set_range_acceleration(AFS_SEL_8G); // Change accelerometer range. 2G was not enough, 8G works!
	usleep(50000); 							// Makes sure the IMU with gyro is up and running (min 30 ms)
	
	// Initialize magnetometer (part of FreeIMU)
	HMC5883L mag(i2c_open(1,MAG_ADDR));
	mag.init();
	usleep(50000);

	// Declare values to hold IMU readings
	double acc_d[3];
	double gyro_d[3];
	double mag_d[3];
	
	// Init VC01
	VC01 distance_sensor(1);
	// Declare values to hold VC01 
	double distance[1]; 
	
	// Init LED
	int light  = 1;
	int led_counter = 0;
	GPIO led("30");
	led.init(1, light);		// direction = OUT, value = HIGH
	
	// Init PWM 
	PCA9685 pwm_out(i2c_open(1, 0x40));
	usleep(50000);
	pwm_out.init(50);						// frequency 50 Hz 
	//GPIO OE("49");						// OE is controlled by a button at the moment, this can be useful later 
	//OE.init(1, 0);						// direction = OUT, value = LOW
	double ctrl_signal[4] = {0, 0, 0, 0};	// initial control signal to the servos
	pwm_out.signal(ctrl_signal);
	
	// Init TIMER
	//timer Timer;		// declare more objects of class timer if you wish to clock several things at the same time
	
	// Variables for the clock() function (bad resolution) - remove when timer class is used
	clock_t start;
	clock_t stop;
	clock_t flag_;
	
	// INITIALIZATION COMPLETED
	
	printf("Hugin program started!\n");
	
	// Flushing UDP buffers
	for(int i=0; i<1000; i++) {
		printf("Flushing: %i \n", i);
		data_size = sock.listen();
		if(data_size > 0) {
			if(socket_vals[0].i_vals[0]){
				sock.process_packet(data_size, socket_vals, num_socket_vals);		// flushing Simulink --> C buffer
				sock.send(LOCAL_HOST, 22101, sbus_channels_d, num_sbus_channels);	// flushing C --> Simulink buffer 
			}
		}
	}
	printf("\n**Flushing completed** \n");
	// data size should be 32 after, if not, increase the upper limit for i (2-1000)
	printf("Initial Data size: %d \n\n", data_size);
	usleep(1000000);
	printf("Ready to receive control signals");
	usleep(1000000);
	
	while(1){
		// Listen for packets and process if new packets have arrived 
		data_size = sock.listen();		// returns the number of bytes received
		if(data_size > 0){
			sock.process_packet(data_size, socket_vals, num_socket_vals);
			
			// Pace keeper packet received (i.e. flag)
			if(socket_vals[0].i_vals[0]){
				//Timer.start();
				start = clock();
				socket_vals[0].i_vals[0] = 0;		// reset the flag, i_vals accesses the ready signal
				
				// Set PWM outputs
				// socket is sometimes 0.00, we do not want to send that to the servos (why is it 0?)
				if(socket_vals[1].d_vals[0] > 0.01){				//d_vals acceses the motor signals from Simulink
					pwm_out.signal_s(socket_vals[1].d_vals[0], 0);	//sending socket signal 0 to servo 0 
					pwm_out.signal_s(sbus_channels_d[0], 1);		//sending sbus signal 0 to servo 1 for time delay comparison (not through simulink)
				}
				
				// Get IMU readings
				imu.get_accelerations(acc_d);
				imu.get_angular_velocities(gyro_d);	
				mag.get_magnetometer_data(mag_d);
				
				// Get RC readings (SBUS)
				rcr.parse_SBus(channels, sbus_channels_d);
				
				// Get distance values
				distance[0] = distance_sensor.get_distance();
				
				// Get RC readings (PWM)
				print_counter++;
				rcr.get_readings(channels);
				for(int i = 0; i < 2; i++){
					ext_channels_d[i] = (double)channels[i];
				}
				
				// printing signals for comparison
				for(int i = 0; i < 2; i++) {		// when we can run all servos, change upper limit for i to 4
					printf("SBUS signal: \t%d \t%f \n", i, sbus_channels_d[i]);
					printf("Socket value: \t%d \t%f \n", i, socket_vals[1].d_vals[i]);
					printf("PWM reading: \t%d \t%f \n\n", i, (ext_channels_d[i]-564)/1860);		// might need to have different scaling for each servo
				}
				
				// Send updates via UDP
				sock.send(LOCAL_HOST, 22001, acc_d, 3);
				sock.send(LOCAL_HOST, 22002, gyro_d, 3);
				sock.send(LOCAL_HOST, 22003, mag_d, 3);
				sock.send(LOCAL_HOST, 22006, distance, 1);
				sock.send(LOCAL_HOST, 22101, sbus_channels_d, num_sbus_channels);
				sock.send(LOCAL_HOST, 22102, ext_channels_d, 4);
								
				// Blink LED every 10th sent package
				led_counter++;
				if(led_counter > 10){
					light = !light;
					led.write(light);
					led_counter = 0;
				}
				
				// Stop timer and print total elapsed time
				/*Timer.stop();
				printf("Elapsed time (ms): %f \n\n", Timer.millis());
				//printf("Elapsed time (us): %f \n\n", Timer.micros());*/

				// Stop the (bad) timer and print run time for loop and time between flags (should be 20 ms = 50 Hz)
				stop = clock();
				/*printf("Loop run time (ms): \t %f \n", ((float)(stop-start))/CLOCKS_PER_SEC*1000); 
				printf("Time between flags (ms): %f \n\n",((float)(start-flag_))/CLOCKS_PER_SEC*1000);*/
				flag_ = start;
			}
		}
	}
}
