#include "timer.h"

timer::timer() {}

// start the clock
void timer::start(){
	start_ = steady_clock::now();
	}

// stop the clock
void timer::stop(){
	stop_ = steady_clock::now();
}

// get the time interval elapsed in milliseconds
double timer::millis() {
	return duration<double,milliseconds>(stop_ - start_).count();
}

// get the time interval elapsed in microseconds
double timer::micros() {
	return duration<double, microseconds>(stop_ - start_).count();
}