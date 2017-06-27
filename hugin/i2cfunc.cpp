/*******************************
 * i2cfunc.c v3
 * wrapper for I2C functions
 *******************************/

#include <stdio.h> 
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <iomanip>
#include "i2cfunc.h"


int i2c_open(unsigned char bus, unsigned char addr)
{
  int file;
  char filename[16];
  sprintf(filename,"/dev/i2c-%d", bus);
  if ((file = open(filename,O_RDWR)) < 0)
  {
    fprintf(stderr, "i2c_open open error: %s\n", strerror(errno));
    return(file);
  }
  if (ioctl(file,I2C_SLAVE,addr) < 0)
  {
    fprintf(stderr, "i2c_open ioctl error: %s\n", strerror(errno));
    return(-1);
  }
  return(file);
}

int i2c_write(int handle, unsigned char* buf, unsigned int length)
{
  if (write(handle, buf, length) != length)
  {
    fprintf(stderr, "i2c_write error 0x%X: %s\n", handle, strerror(errno));
    return(-1);
  }
  return(length);
}

int i2c_write_byte(int handle, unsigned char val)
{
  if (write(handle, &val, 1) != 1)
  {
    fprintf(stderr, "i2c_write_byte error 0x%X: %s\n", handle, strerror(errno));
    return(-1);
  }
  return(1);
}

int i2c_read(int handle, unsigned char* buf, unsigned int length)
{
  if (read(handle, buf, length) != length)
  {
    fprintf(stderr, "i2c_read error 0x%X: %s\n", handle, strerror(errno));
    return(-1);
  }
  return(length);
}

int i2c_read_byte(int handle, unsigned char* val)
{
  if (read(handle, val, 1) != 1)
  {
    fprintf(stderr, "i2c_read_byte error 0x%X: %s\n", handle, strerror(errno));
    return(-1);
  }
  return(1);
}

int i2c_close(int handle)
{
  if ((close(handle)) != 0)
  {
    fprintf(stderr, "i2c_close error 0x%X: %s\n", handle, strerror(errno));
    return(-1);
  }
  return(0);
}

int i2c_write_read(int handle,
                   unsigned char addr_w, unsigned char *buf_w, unsigned int len_w,
                   unsigned char addr_r, unsigned char *buf_r, unsigned int len_r)
{
	struct i2c_rdwr_ioctl_data msgset;
	struct i2c_msg msgs[2];
	
	msgs[0].addr=addr_w;
	msgs[0].len=len_w;
	msgs[0].flags=0;
	msgs[0].buf=buf_w;
	
	msgs[1].addr=addr_r;
	msgs[1].len=len_r;
	msgs[1].flags=1;
	msgs[1].buf=buf_r;
	
	msgset.nmsgs=2;
	msgset.msgs=msgs;
	
	if (ioctl(handle,I2C_RDWR,(unsigned long)&msgset)<0)
  {
		fprintf(stderr, "i2c_write_read error 0x%X: %s\n", handle, strerror(errno));
    return -1;
  } 
  return(len_r);
}

int i2c_write_ignore_nack(int handle,
                          unsigned char addr_w, unsigned char* buf, unsigned int length)
{
	struct i2c_rdwr_ioctl_data msgset;
	struct i2c_msg msgs[1];
	
	msgs[0].addr=addr_w;
	msgs[0].len=length;
	msgs[0].flags=0 | I2C_M_IGNORE_NAK;
	msgs[0].buf=buf;
	
	msgset.nmsgs=1;
	msgset.msgs=msgs;
	
	if (ioctl(handle,I2C_RDWR,(unsigned long)&msgset)<0)
  {
		fprintf(stderr, "i2c_write_ignore_nack error 0x%X: %s\n", handle, strerror(errno));
    return -1;
  } 
  return(length);
}

int i2c_read_no_ack(int handle, 
                    unsigned char addr_r, unsigned char* buf, unsigned int length)
{
	struct i2c_rdwr_ioctl_data msgset;
	struct i2c_msg msgs[1];
	
	msgs[0].addr=addr_r;
	msgs[0].len=length;
	msgs[0].flags=I2C_M_RD | I2C_M_NO_RD_ACK;
	msgs[0].buf=buf;
	
	msgset.nmsgs=1;
	msgset.msgs=msgs;
	
	if (ioctl(handle,I2C_RDWR,(unsigned long)&msgset)<0)
  {
		fprintf(stderr, "i2c_read_no_ack error 0x%X: %s\n", handle, strerror(errno));
    return -1;
  } 
  return(length);
}

int delay_ms(unsigned int msec)
{
  int ret;
  struct timespec a;
  if (msec>999)
  {
    fprintf(stderr, "delay_ms error: delay value needs to be less than 999\n");
    msec=999;
  }
  a.tv_nsec=((long)(msec))*1E6d;
  a.tv_sec=0;
  if ((ret = nanosleep(&a, NULL)) != 0)
  {
    fprintf(stderr, "delay_ms error: %s\n", strerror(errno));
  }
  return(0);
}


// Added by Magnus Blomberg http://www.magnusblomberg.se 2015-03-04

// Request length bytes at register address reg_addr and reads the bytes to buf
int i2c_read_pos(int handle, unsigned char* buf, unsigned int length, unsigned char reg_addr){
	unsigned char tmp[1];
	tmp[0] = reg_addr;
	return (i2c_write(handle, tmp, 1) && i2c_read(handle, buf, length));	
}

// Writes length number of buf bytes at register address reg_addr
int i2c_write_pos(int handle, unsigned char* buf, unsigned int length, unsigned char reg_addr){
	unsigned char tmp[length + 1];
	tmp[0] = reg_addr;
	tmp[1] = *buf;
	return i2c_write(handle, tmp, length + 1);
}
  
// Set bit to value at bit_pos_val at register address reg_addr
// bit_pos_val is a byte with the desired bit (or bits) to be modified set to 1. The rest is 0. 
// Example: To set bit 2 (=third bit) to 1 in a register reg_addr call 
//		i2c_write_bit(handle, 0b00000100, 1, reg_addr);
int i2c_write_bit(int handle, unsigned char bit_pos_val, int value, unsigned char reg_addr){
	unsigned char tmp[1];
	if(i2c_read_pos(handle, tmp, 1, reg_addr)){
		if(value == 1){
			tmp[0] |= bit_pos_val;
			return i2c_write_pos(handle, tmp, 1, reg_addr);
		} else {
			tmp[0] &= ~bit_pos_val;
			return i2c_write_pos(handle, tmp, 1, reg_addr);
		}
	} else {
		return -1;
	}
}

// Reads bit bit_pos_val at register reg_addr and saves to value
int i2c_read_bit(int handle, unsigned char bit_pos_val, int* value, unsigned char reg_addr){
	unsigned char tmp[1];
	if(i2c_read_pos(handle, tmp, 1, reg_addr)){
		*value = (int)((tmp[0] & bit_pos_val) > 0);
		return 1;
	} else {
		return -1;
	}
}
