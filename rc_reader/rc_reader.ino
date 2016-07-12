#define SBus Serial
#include <Wire.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

  
// PWM reading
volatile unsigned int pin_value;
volatile unsigned long time_;
volatile int current_value;
int previous_value;
int changed_pin;
int isChanged;
volatile unsigned long time_interrupt;
unsigned long start_time[4];
unsigned long stop_time[4];
const int num_pwm_channels = 4;
unsigned long prev_time[4] = {0, 0, 0, 0};    // if one is interested in measuring the PWM period un-comment here and in loop
unsigned long freq_time[4];

// SBus variables
const int sBus_bytes = 18; // 11 bits per channel + 1 byte for fail-safe, packet drop and two digital channels
uint8_t sBuffer[25];

// Common variables
const int buffer_size = 2*num_pwm_channels + sBus_bytes + 1; // 2 bytes per PWM channel, 1 extra empty byte
uint8_t buffer[buffer_size];

// LED - variables
unsigned int counter = 0; // Counter to check when to turn led on/off
unsigned int light = 1; 
unsigned int LED = 13; // PIN number for LED


void setup(){  
  cli();    // disables interrupts
  
  // Set input pins
  DDRD &= ~B00111100; // Arduino pins 2-5
  //PCICR |= 0b00000100;    // turn on port d
  PCICR |= 0b00000001;    // turn on port b
  //PCMSK2 |= 0b00111100;   // turn on pins PD2-5
  PCMSK0 |= 0b00001111;   // turn on pins PB0-3
  //PCMSK2 |= 0b00000011;   // turn on pins PD0-1
  SBus.begin(100000); 
  delay(500000);
  Wire.begin(5);
  delay(500000);
  Wire.onRequest(requestEvent);

  yield();

  // LED out
  pinMode(LED , OUTPUT);
  digitalWrite(LED, light);

  sei();    // enables interrupts
}

// ISR to be called for each interrupt
ISR(PCINT0_vect) {
  time_interrupt = micros(); 
  //pin_value = (PIND&B00111100) >> 2;
  pin_value = (PINB&B00001111);
}

void loop(){
  // atomic block makes sure the values are copied without getting interrupted
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    time_ = time_interrupt;
    current_value = pin_value;
  }

 // PWM signal timer
 // if current_value XOR previous_value = TRUE an interrupt occured
  changed_pin = current_value ^ previous_value;
  if(changed_pin) {
    for(int i=0; i<4; i++) {
      isChanged = (changed_pin >> i) & 1;   // shift down 0,1,2,3 bits and pick out the last one to check if changed (1) or not (0)
      // if TRUE, index i changed --> check if HIGH or LOW
      if(isChanged) {
        // if TRUE, pin is HIGH --> start timer
        if((current_value >> i) & 1) {
          start_time[i] = time_;
          /*freq_time[i] = time_ - prev_time[i];    // for PWM period measuring
          prev_time[i] = time_;*/
         }
        // if FALSE, pin is LOW --> stop timer
        else {stop_time[i] = time_ - start_time[i];}
      }
    }
  }
  previous_value = current_value;

  check_SBus();    // Read SBus signal

}


// On I2C request, put all channel values in a buffer and send buffer
// Send PWM and SBUS to BBB
void requestEvent(){
  // Send PWM signal measurements 
  // for loop is inverted because 0001 ~ index 3 (etc) but will be checked first in PWM reading
  for(int i = 3; i > -1; i--){
    // An unsigned int consists of two bytes. 
    buffer[2*i] = stop_time[i] >> 8;
    buffer[2*i+1] = stop_time[i] & 0xFF;
  } 

  // Send PWM period timing (remember to comment eihter this section or PWM signal section above)
  /*for(int i = 3; i>-1; i--) {
      buffer[2*i] = freq_time{i] >> 8;
      buffer[2*i+1] = freq_time[i] & 0xFF;*/   
 
  // Fix SBus data
  for(int i = 2*num_pwm_channels; i < 2*num_pwm_channels + sBus_bytes; i++){
    buffer[i] = sBuffer[i-(2*num_pwm_channels)];
  }
  buffer[buffer_size - 1] = sBuffer[23];
  
  Wire.write(buffer, (uint8_t)(buffer_size));
   
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
        // First byte should be 0x0F
//        if(sBuffer[0] == 0x0F){
//          SBusParser();
//        }
        while(SBus.available()){
          char data = SBus.read();
        }
      }
    }
  }
}


