/* led.h
 *
 * Handles GPIO port 30 communication on BBB. I.e. light or blink the LED connected to pin P9_11
 */

#ifndef LED_H
#define LED_H


#include <fstream>
#include <string>

#define SET_PATH "/sys/class/gpio/export" 
#define PIN_PATH "/sys/class/gpio/gpio30"

void led_init()
{
	// Setup pin P9_11 as GPIO-port 30
	std::fstream fs;
	fs.open(SET_PATH, std::fstream::out);
	fs << "30";
	fs.close();
   // Set direction to out.
	fs.open(PIN_PATH "/direction", std::fstream::out);
	fs << "out";
	fs.close();
}

// Set the LED to value defined in value (0 = turn of the led)
void led_write(int value){
	std::fstream fs;
	fs.open(PIN_PATH "/value", std::fstream::out);
    fs << value;
    fs.close();
}

#endif