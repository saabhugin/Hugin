/* 
 * Class for enabling GPIO ports on BBB
 * if trying to activate a port that is not an allowed GPIO an error will occur
 * 
 * Extra:
 * P8_27-P8_46 is normally used for HDMI but is deactivated for Hugin
 * hence, they can be used as GPIO ports if the ones specified here 
 * is not enough (google guide on how to do this)
 *
 */

#ifndef GPIO_H
#define GPIO_H

#include <fstream>
#include <string>
#include <unordered_set>

#define SET_PATH "/sys/class/gpio/export" 

class GPIO{
	
public:
	GPIO();
	GPIO(std::string port_);
	void init(bool dir_val, bool value_);
	void set_pin();
	void set_direction(bool dir_val); 		// 1 = out, 0 = in 
	void write(bool value_);				// 1 = HIGH, 0 = LOW
	
private:
	std::string GPIO_port;
	std::string PINPATH;
	std::string PINDIR;
	std::string PINVAL;
	std::fstream fs;
	
};

#endif