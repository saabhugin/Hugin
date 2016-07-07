/* 
 * Class for enabling GPIO ports on BBB
 * see documents for available pin numbers
 * 
 */

#ifndef GPIO_H
#define GPIO_H

#include <fstream>
#include <string>

#define SET_PATH "/sys/class/gpio/export" 

class GPIO{
	
public:
	GPIO();
	GPIO(int handle_);
	void init(bool dir_val, int value_);
	void set_pin();
	void set_direction(bool dir_val); 		// 1 = out, 0 = in 
	void write(bool value_);
	
private:
	int handle;
	std::string pin;
	std::string PINPATH;
	std::string PIN_DIR;
	std::string PIN_VAL;
	std::fstream fs;
	
};

#endif