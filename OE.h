/* OE.h
 *
 * Handles GPIO port 49 (P9_23) communication on BBB to control the OE port on PCA9685
 */

#ifndef OE_H
#define OE_H


#include <fstream>
#include <string>

#define SET_PATH "/sys/class/gpio/export" 
#define PIN_PATH "/sys/class/gpio/gpio49"

class GPIO{
	
	public:
	GPIO();
	GPIO(int handle_);
	void init(unsigned char pin_, int value_);
	void set(unsigned char pin_);
	void write(int value_);

	
	private:
	int GPIOvalue;
	std::string pinPath;
};


void led_init()
{
	// Setup pin P9_23 as GPIO-port 49
	std::fstream fs;
	fs.open(SET_PATH, std::fstream::out);
	fs << "49";
	fs.close();
   // Set direction to out.
	fs.open(PIN_PATH "/direction", std::fstream::out);
	fs << "out";
	fs.close();
}

// Set OE to value defined in value (0 = output enabled, 1 = output disabled)
void OE_write(bool value){
	std::fstream fs;
	fs.open(PIN_PATH "/value", std::fstream::out);
    fs << value;
    fs.close();
}

#endif