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
#define HIGH 1
#define LOW 0
#define OUT 1
#define IN 0

class GPIO{
	
public:
	GPIO();
	GPIO(std::string port);
	void init(bool direction, bool value);
	void set_pin();
	void set_direction(bool direction); 
	void write(bool value);
	bool read();
	
private:
	std::string port_;
	bool direction_;
	std::string PINPATH;
	std::string PINDIR;
	std::string PINVAL;
	std::fstream fs;
};

#endif