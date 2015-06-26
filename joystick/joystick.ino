#define SBus Serial1
char last_data = 0;
uint8_t sBuffer[25];

uint16_t channels_raw[14];
Joystick_ joy;

void setup(){
  Serial1.begin(100000);
  Serial.begin(115200);
  Serial.println("started");
}

void loop(){
  if(SBus.available() > 24){
    int pos = 0;
    while(SBus.available()){
      uint8_t data = SBus.read();
      sBuffer[pos++] = data;
      if(pos == 24){
        SBusParser();
//        printSBus();
        update_joystick();
        while(SBus.available()){
          char data = SBus.read();
        }
      }
    }
  }
}

// Each channel is 11 bits. First byte is 0x0F. 
void SBusParser(){
  channels_raw[0]  = ((sBuffer[1] | sBuffer[2] << 8) & 0x07FF);
  channels_raw[1]  = ((sBuffer[2] >> 3  | sBuffer[3] << 5) & 0x07FF);
  channels_raw[2]  = ((sBuffer[3] >> 6  | sBuffer[4] << 2 | sBuffer[5] << 10) & 0x07FF);
  channels_raw[3]  = ((sBuffer[5] >> 1  | sBuffer[6] << 7) & 0x07FF);
  channels_raw[4]  = ((sBuffer[6] >> 4  | sBuffer[7] << 4) & 0x07FF);
  channels_raw[5]  = ((sBuffer[7] >> 7  | sBuffer[8] << 1  | sBuffer[9] << 9) & 0x07FF);
  channels_raw[6]  = ((sBuffer[9] >> 2  | sBuffer[10] << 6) & 0x07FF);
  channels_raw[7]  = ((sBuffer[10] >> 5  | sBuffer[11] << 3) & 0x07FF);
  channels_raw[8]  = ((sBuffer[12] | sBuffer[13] << 8) & 0x07FF);
  channels_raw[9]  = ((sBuffer[13] >> 3  | sBuffer[14] << 5) & 0x07FF);
  channels_raw[10] = ((sBuffer[14] >> 6  | sBuffer[15] << 2 | sBuffer[16] << 10) & 0x07FF);
  channels_raw[11] = ((sBuffer[16] >> 1  | sBuffer[17] << 7) & 0x07FF);
  channels_raw[12] = sBuffer[23] & 0b1111; // Contains two digital channels on 0b0001 and 0b0010 as well as lost packet flag 0b0100 and failsafe active flag 0b1000
}

void printSBus(){
  for(int i = 0; i < 13; i++){
    Serial.print(i);
    Serial.print(":");
    Serial.print(channels_raw[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void update_joystick(){
  uint8_t channels_8[13];
  for(int i = 0; i < 12; i++){
    channels_8[i] = channels_raw[i] / 8;
  }
  joy.move((uint8_t)channels_8[0], (uint8_t)channels_8[1], (uint8_t)channels_8[2], (uint8_t)channels_8[3]);  
}