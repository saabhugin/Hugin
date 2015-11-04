/*
 * VC01.h
 *
 * Skeleton file for future distance sensor implementation. 
 */

#ifndef VC01_H
#define VC01_H

class VC01{
	public:
	// Init VC01 module with pin number pin
	VC01(int pin);
	
	// returns distance in m
	double get_distance();
	
	private:
	double distance;
};
#endif