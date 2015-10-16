#define SBus Serial
#include <Wire.h>
#include <Servo.h> 
  
// PWM reading
const int num_pwm_channels = 4;
volatile unsigned int pin_reading = 0;
volatile unsigned int last_reading = 0;
unsigned long pulse_start[num_pwm_channels];
unsigned int  pulse_iter[num_pwm_channels] = {1,1,1,1};
unsigned long diff;
unsigned int channel_vals[num_pwm_channels];

// SBus variables
const int sBus_bytes = 18; // 11 bits per channel + 1 byte for fail-safe, packet drop and two digital channels
uint8_t sBuffer[25];

// Common variables
const int buffer_size = 2*num_pwm_channels + sBus_bytes + 1; // 2 bytes per PWM channel, 1 extra empty byte
uint8_t buffer[buffer_size];

// PWM output
unsigned long last_received_update = 0; // Updates when pwm updates are received
uint16_t pwm_time_out[num_pwm_channels];
Servo pwm_out0;
Servo pwm_out1;
Servo pwm_out2;
Servo pwm_out3;

// LED - variables
unsigned int counter = 0; // Counter to check when to turn led on/off
unsigned int light = 1; 
unsigned int LED = 13; // PIN number for LED


void setup(){  
  // Set input pins
  DDRD &= ~B00111100; // Arduino pins 2-5
  SBus.begin(100000); 
  
  delay(10);
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
    
  delay(1000);
  
  pwm_out0.attach(6);
  pwm_out1.attach(9);
  pwm_out2.attach(10);
  pwm_out3.attach(11);

  // LED out
  pinMode(LED , OUTPUT);
  digitalWrite(LED, light);
  
}


void loop(){
  check_pins();    // Read PWM signals
  check_SBus();    // Read SBus signal
  check_output();  // Output fail-safe
}

// Write PWM to motors
void receiveEvent(int num_bytes){
  int iter = 0;
  while(Wire.available() && iter < 8){
    unsigned char data = Wire.read();
    if(iter%2 == 0){
      // If even
      pwm_time_out[iter/2] = data << 8;
    } else {
      pwm_time_out[iter/2] |= data;
    }
    iter++;
  }
  last_received_update = millis();
  pwm_out0.writeMicroseconds(pwm_time_out[0]);
  pwm_out1.writeMicroseconds(pwm_time_out[1]);
  pwm_out2.writeMicroseconds(pwm_time_out[2]);
  pwm_out3.writeMicroseconds(pwm_time_out[3]);

}

// On I2C request, put all channel values in a buffer and send buffer
// Send PWM and SBUS to BBB
void requestEvent(){
  // Fix PWM channels
  for(int i = 0; i < num_pwm_channels; i++){
    unsigned int current_val = channel_vals[i];
    // An unsigned int consists of two bytes. 
    buffer[2*i] = current_val >> 8;
    buffer[2*i+1] = current_val & 0xFF;
    pulse_iter[i] = 1; // Reset pulse iterator for mean value calculations.
  }
  
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

void check_pins(){
  // Read pins  
//  pin_reading = (PINB&B00001111);
  pin_reading = (PIND&B00111100) >> 2;
  
  // If there is a difference in the new reading from the last
  if(last_reading^pin_reading){
    unsigned long k = micros(); // XXX:Beware of overflow. Please fix this.
    
    for(int i = 0; i < 4; i++){
      // If there is a difference on this spot
      if((last_reading^pin_reading) & (1<<i)){
        if(pin_reading & (1<<i)){
          // Pin went high, we save the start time of the pulse
          pulse_start[i] = k;
        } else {
          // Pin went low, we calculate the duration of the pulse
          // Possibility exists to filter the signal now
          diff = k - pulse_start[i];
      // Bad code? 
          // channel_vals[i] = diff; 
          if(diff > 900 && diff < 2100){ // Only save if reasonable value
            channel_vals[i] = channel_vals[i]*(pulse_iter[i]-1)/pulse_iter[i] + diff/pulse_iter[i];
            pulse_iter[i]++;
          }
        }
      }
    }
    last_reading = pin_reading;
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

void check_output(){
  // If no pwm updates have been received, set outputs to idle
  if(millis() - last_received_update > 1000){
    pwm_out0.writeMicroseconds(1000);
    pwm_out1.writeMicroseconds(1000);
    pwm_out2.writeMicroseconds(1000);
    pwm_out3.writeMicroseconds(1000);
  }
}
