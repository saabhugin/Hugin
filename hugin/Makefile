##########################################################
# Makefile for compiling C++ code with additional C code.
#
# Oscar Törnroth, 2017-06-20
#
##########################################################

# TARGET FILE
EXECUTABLE = hugin

# C++
CC = g++
CCFLAGS = -g -std=c++0x
CCSOURCES =  main.cpp bsocket.cpp GPIO.cpp i2cfunc.cpp PCA9685.cpp rcreader.cpp
CCOBJECTS = $(CCSOURCES:.cpp=.o)

# C
C = gcc
CFLAGS = -Wall -g
CLIBS = -lm
CSOURCES = free_imu.c inv_mpu.c inv_mpu_dmp_motion_driver.c 
COBJECTS = $(CSOURCES:.c=.o)

# COMPILER CALLS
all: $(EXECUTABLE)
	@echo TMAQ - hugin successfully built!
	
$(EXECUTABLE): $(CCOBJECTS) $(COBJECTS)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS)

.cpp.o:
	$(CC) $(CCFLAGS) -c $< -o $@
	
.c.o:
	$(C) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *o hugin
