#ifndef LED_H
#define LED_H

/* 
 * Functions for lighting the external LED from a GPIO port 30 on the BBB
 */

#include <fstream>
#include <string>

#define SET_PATH "/sys/class/gpio/export" 
#define PIN_PATH "/sys/class/gpio/gpio30"

void led_init()
{
	std::fstream fs;
	fs.open(SET_PATH, std::fstream::out);
	fs << "30";
	fs.close();
  
	fs.open(PIN_PATH "/direction", std::fstream::out);
	fs << "out";
	fs.close();
}

void led_write(int value){
	std::fstream fs;
	fs.open(PIN_PATH "/value", std::fstream::out);
    fs << value;
    fs.close();
}

#endif