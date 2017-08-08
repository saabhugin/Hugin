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
	
	auto dur = timer::stop_ - timer::start_;
	
	auto i_millis = std::chrono::duration_cast<milliseconds>(dur);
	
	return i_millis.count(); 
	
	//return std::chrono::duration<double,milliseconds>(stop_ - start_).count();
	
}

// get the time interval elapsed in microseconds
double timer::micros() {
	
	auto dur = timer::stop_ - timer::start_;
	
	auto i_micro = std::chrono::duration_cast<microseconds>(dur);
	
	return i_micro.count(); 
	
	//return duration<double, microseconds>(stop_ - start_).count();
}