#include "GPIO.h"

GPIO::GPIO() {
	handle = 0;
}

GPIO::GPIO(int handle_) {
	handle = handle_;
}

void GPIO::init(bool dir_val, int value_) {
	pin = std::to_string(handle);
	PINPATH = "/sys/class/gpio/gpio";
	PINPATH.append(pin);
	PIN_DIR = PINPATH;
	PIN_DIR.append("/direction");
	PIN_VAL = PINPATH;
	PIN_VAL.append("/value");
	set_pin();
	set_direction(dir_val);	
}

// Set GPIO port number - port defined in constructor
void GPIO::set_pin() {
	fs.open(SET_PATH, std::fstream::out);
	fs << pin;
	fs.close();
}

// Set GPIO port direction - in/out
void GPIO::set_direction(bool dir_val) {
	if(dir_val) {
		fs.open(PIN_DIR, std::fstream::out);
	}
	else {
		fs.open(PIN_DIR, std::fstream::in);
	}
}

// Set GPIO port to value - 0/1
void GPIO::write(bool value_){
	fs.open(PIN_VAL, std::fstream::out);
    fs << value_;
    fs.close();
}