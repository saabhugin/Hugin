#include "GPIO.h"

GPIO::GPIO() {
	GPIO_port = "0";
}

// choose which digital pin you want to activate. NOTE! Use string (e.g "30") not int (30)
GPIO::GPIO(std::string port_) {
	// checking GPIO port availability 
	std::unordered_set<std::string> ValidValues {"60", "48", "49", "117", "115", "112", "20", "66", "67", "68", "69", "45", "44", "26", "47", "46", "27", "65", "61"};
	// if TRUE, port is available
	if(ValidValues.count(port_)) {
		GPIO_port = port_;
		// removing the port from list of available ports
		ValidValues.erase(port_);
	}
	// if FALSE, port is unavailable --> print error message
	else {
		//fprintf(stderr, "GPIO port unavailable: %s\n", std::string port_);
		GPIO_port = "0";
	}
}

// when initializing, choose if pin should be input (0) or output (1), and HIGH (1) or LOW (0)
void GPIO::init(bool dir_val, bool value_) {
	PINPATH = "/sys/class/gpio/gpio";
	PINPATH.append(GPIO_port);
	PINDIR = PINPATH;
	PINDIR.append("/direction");
	PINVAL = PINPATH;
	PINVAL.append("/value");
	set_pin();
	set_direction(dir_val);	
	write(value_);
}	
	
// Set GPIO port number - port already defined in constructor
void GPIO::set_pin() {
	fs.open(SET_PATH, std::fstream::out);
	fs << GPIO_port;
	fs.close();
}

// Set GPIO port direction - in (0) or out (1) 
void GPIO::set_direction(bool dir_val) {
	if(dir_val) {
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

// Set GPIO port to value (int) 
void GPIO::write(bool value_){
	fs.open(PINVAL, std::fstream::out);
    fs << value_;
    fs.close();
}