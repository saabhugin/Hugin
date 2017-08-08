/*
* 	Class for measuring time intervals
*	Code requires C++11 / g++ 4.7 compilator or newer
*	Not compiled 160810
*	Commented code to run the class already exist in main.cpp
*
*	An object of class timer can only clock one event at a time
*	(every time you start the clock it will reset)
*	If you wish to clock different events at the same time just create 
*	more objects of class timer! 
*	(e.g. if you want to clock a loop and a piece of code inside the loop)
*/

#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class timer {
	// typedef to avoid writing std::chrono every time
	typedef std::chrono::steady_clock steady_clock;
	typedef std::chrono::milliseconds milliseconds;
	typedef std::chrono::microseconds microseconds;
	typedef std::chrono::steady_clock::time_point time_point;
	//typedef std::chrono::duration duration;

	public:
		timer();
		void start();
		void stop();
		double millis();
		double micros();
	
	private:
		time_point start_;
		time_point stop_;
		
};

#endif