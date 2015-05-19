#include "VC01.h"

// Init VC01 module with pin number pin
VC01::VC01(int pin){
	distance = 1337;
}

// returns distance in m
double VC01::get_distance(){
	return distance++;
}