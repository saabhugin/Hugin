#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6

class pwm_out{

public:
	int servoval[4][2];
	void set_servoval();
	void reset(int pwm_handle);
	void set_freq(float freq, int pwm_handle);
	void set(unsigned char num, unsigned int on, unsigned int off, int pwm_handle);
	void set_pin(unsigned char num, unsigned int val, bool invert, int pwm_handle);
	void signal(double ctrl_signal[4], int pwm_handle);

private:
	int pwm_handle = i2c_open(1, 0x40);			// what i2c bus to connect and address to PWM card
	unsigned char servonum[4] = {0, 1, 2, 3};
}