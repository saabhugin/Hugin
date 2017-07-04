#define SBus Serial
#include <Wire.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

  
// PWM reading
volatile unsigned int pin_value=0;
volatile unsigned long time_interrupt=0;
int current_value=0;
int previous_value=0;
int changed_pin=0;
int isChanged=0;
unsigned long time_=0;
unsigned long start_time[4]={0,0,0,0};
unsigned long stop_time[4]={0,0,0,0};
//unsigned long mean_val[4]={0,0,0,0};
//unsigned int pulse_iter[4] = {1, 1, 1, 1};
const int num_pwm_channels = 4;
unsigned long prev_time[4] = {0, 0, 0, 0};

// SBus variables
const int sBus_bytes = 18; // 11 bits per channel + 1 byte for fail-safe, packet drop and two digital channels
uint8_t sBuffer[25];

// Common variables
const int buffer_size = 2*num_pwm_channels + sBus_bytes + 1; // 2 bytes per PWM channel, 1 extra empty byte
uint8_t buffer[buffer_size];

// Digital outputs - variables
unsigned int counter = 0; // Counter to check when to turn led on/off
unsigned int light = 1; 
unsigned int LED = 13; // PIN number for LED
unsigned int PWM_OutputEnable = 12; // PIN number for output enable on PWM board PCA9685  

// Activate pins and set up i2c communication
void setup(){  
  cli();    // disables interrupts

  // PWM output enable init
  pinMode(PWM_OutputEnable,OUTPUT);
  digitalWrite(PWM_OutputEnable,HIGH);
  
  // Set input pins
  PCICR |= 0b00000001;    // turn on port B for interrupts
  PCMSK0 |= 0b00011110;   // mask out pins PB1-4, for pwm reading
  SBus.begin(100000); 
  delay(500000);
  Wire.begin(5);
  delay(500000);
  Wire.onRequest(requestEvent);

  yield(); //not sure what this does
  
  // LED out
  pinMode(LED , OUTPUT);
  digitalWrite(LED, light);

  sei();    // enables interrupts
}

// ISR to be called for each interrupt
ISR(PCINT0_vect) {
  time_interrupt = micros(); 
  pin_value = (PINB&B00011110)>>1;
}

void loop(){
 // PWM signal timer
  // if pin_value XOR previous_value = TRUE an interrupt occured
  if(pin_value^previous_value) {
    // atomic block makes sure the values are copied without getting interrupted
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      time_ = time_interrupt;
      current_value = pin_value;
    }
    PWM_reading(time_, current_value, previous_value);
    previous_value = current_value;
  }
  check_SBus();    // Read SBus signal
}

// Function gets called everytime an interrupt occurs (i.e. a pin changes)
void PWM_reading(unsigned long time_, int current_value, int previous_value){
  changed_pin = current_value ^ previous_value;
  for(int i=0; i<4; i++) {
    isChanged = (changed_pin >> i) & 1;   // shift down 0,1,2,3 bits and pick out the last one to check if changed (1) or not (0)
    // if TRUE, index i changed --> check if HIGH or LOW
    if(isChanged) {
      // if TRUE, pin is HIGH --> start timer
      if((current_value >> i) & 1) {
        start_time[i] = time_;
       }
      // if FALSE, pin is LOW --> stop timer
      else {
        stop_time[i] = time_ - start_time[i];
        //mean_val[i] = mean_val[i]*(pulse_iter[i]-1)/pulse_iter[i] + stop_time[i]/pulse_iter[i];  // mean value 
        //pulse_iter[i]++;
      }
    }
  }
}
     
// On I2C request, put all channel values in a buffer and send buffer
// Send PWM and SBUS to BBB
void requestEvent(){
  // Send PWM signal measurements 
  // for loop is inverted because PWM signal 3 will be checked first in PWM reading and thus correspond to inedex 0 in stop_time
  for(int i = 3; i > -1; i--){
    // An unsigned int consists of two bytes and i2c can only send 1 byte at a time
    buffer[2*i] = stop_time[i] >> 8;
    buffer[2*i+1] = stop_time[i] & 0xFF;

    // sending the mean value instead of last measured value
    //buffer[2*i] = mean_val[i] >> 8;
    //buffer[2*i+1] = mean_val[i] & 0xFF;
    //pulse_iter[3-i] = 1;
  }  
 
  // Fix SBus data
  for(int i = 2*num_pwm_channels; i < 2*num_pwm_channels + sBus_bytes; i++){
    buffer[i] = sBuffer[i-(2*num_pwm_channels)];
  }
  buffer[buffer_size - 1] = sBuffer[23];
  
  Wire.write(buffer, (uint8_t)(buffer_size));

   // LED turns off/on every 10th i2c message sent
   counter++;
  if(counter > 10){
    light = !light;
    digitalWrite(LED, light);
    counter = 0;
  }
}

void check_SBus(){
  if(SBus.available() > 24){
    int pos = 0;
    while(SBus.available()){
      uint8_t data = SBus.read();
      sBuffer[pos++] = data;
      if(pos == 24){
        while(SBus.available()){
          char data = SBus.read();
        }
      }
    }
  }

  // check if output enable is sent on SBus channel 11
  double sbus_channels_d[13];
  parse_SBus(sBuffer, sbus_channels_d);
  if(sbus_channels_d[11] > 0.7){
    digitalWrite(PWM_OutputEnable,LOW);
  }
  else{
    digitalWrite(PWM_OutputEnable,HIGH);
  }
}

// initializing the SBUS buffer, obtained through reversed engineering - complicated due to SBUS "secret" design 
void parse_SBus(uint8_t* SBus_buffer, double* SBus_channels_d){
	
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


