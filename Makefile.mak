all: test
test: pwm_test.o i2cfunc.o PCA9685.o 
	g++ -std=c++0x pwm_test.cpp i2cfunc.c PCA9685.c -o test
pwm_test.o: pwm_test.cpp
	g++ -std=c++0x pwm_test.cpp
i2cfunc.o: i2cfunc.c
	g++ -std=c++0x i2cfunc.c
PCA9685.o: PCA9685.c
	g++ -std=c++0x PCA9685.c 
clean:
	rm -rf *o test 