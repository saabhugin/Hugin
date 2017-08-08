#include "GPIO.h"

GPIO::GPIO() {
	port_ = "0";
}

// choose which digital pin you want to activate. NOTE! Use string (e.g "30") not int (30)
GPIO::GPIO(std::string port) {
	port_ = port;
}

// when initializing, the pin is set to input or output and value high or low
void GPIO::init(bool direction, bool value) {
	PINPATH = "/sys/class/gpio/gpio";
	PINPATH.append(port_);
	PINDIR = PINPATH;
	PINDIR.append("/direction");
	PINVAL = PINPATH;
	PINVAL.append("/value");
	set_pin();
	set_direction(direction);	
	write(value);
}	
	
// Set GPIO port number - port already defined in constructor
void GPIO::set_pin() {
	fs.open(SET_PATH, std::fstream::out);
	fs << port_;
	fs.close();
}

// Set GPIO port direction
void GPIO::set_direction(bool direction) {
	direction_ = direction;
	if(direction_) {
		fs.open(PINDIR, std::fstream::out);
		fs << "out";
		fs.close();
	}
	else {
		fs.open(PINDIR, std::fstream::in);
		fs << "in";
		fs.close();
	}
}

// Write GPIO output value 
void GPIO::write(bool value){
	if(direction_ == OUT) {
		fs.open(PINVAL, std::fstream::out);
		fs << value;
		fs.close();
	}
	else {
		printf("Write to input port not allowed: \n");
	}
}

// Read GPIO input value 
bool GPIO::read() {
	/*if(direction_ == IN) {
		bool value_ = 0;
		fs.open(PINVAL, std::fstream::in);
		fs >> value_;
		fs.close();
		return(value_);
	}	
	else {
		printf("Read output port not allowed: \n");
		return(-1);
	}*/
}