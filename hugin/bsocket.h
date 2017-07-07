/* bsocket.h
 *
 * UDP protocol functions. 
 *
 * Holds class bsocket and socket_val.
 *
 * bsocket handles the main UDP communication and stores the values in a socket_val object. 
 */

#ifndef BSOCKET_H
#define BSOCKET_H

#include <string>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <exception>
//#include <unistd.h> // use with gcc 4.7

#define INTEGER 1
#define DOUBLE 2
#define DOUBLE_BYTES 4
#define INTEGER_BYTES 1
#define LOCAL_HOST "127.0.0.1"

class socket_val;

class bsocket{
	public:
	bsocket(long buf_size);
	
	void set_listen_timeout(int val);
	
	int listen();
	void process_packet(unsigned int size, socket_val socket_vals[], int num_socket_vals);

	int send(const char* addr, int port, int vals[], int num_vals);		// send data of type int
	int send(const char* addr, int port, double vals[], int num_vals);	// send data of type double
	
	private:
	int listen_timeout;
	unsigned char *buffer;
	
	int sock_raw;
	struct sockaddr saddr;
	unsigned int saddr_size;
};

void udp_data2double_val(unsigned char* data, int size, double d_vals[], int num_vals);
void udp_data2integer_val(unsigned char* data, int size, int i_vals[], int num_vals);
std::string reverse_hex_string(std::string in_string);
double hexstr2double(const std::string& hexstr);
std::string double2hexstr(double x);

/*
 * socket_val class for holding UDP-socket data
 * 
 * Public fields:
 * 		type 		- stores
 * 		port 		- stores UDP-port identifier
 * 		num_vals 	- Stores size of buffer needed for the UDP-socket
 * 		d_vals 		- pointer to double values. Holds data when type = DOUBLE
 * 		i_vals		- pointer to integer values. Holds data when type = INTEGER
 */

class socket_val{
	public:	
	int type;
	int port;
	int num_vals;
	
	socket_val(int type_, int port_, int num_vals_, std::string description_);
	~socket_val();		// destructor
	
	void update_vals(double in_vals[]);
	void update_vals(int in_vals[]);
	void print();
	
	double* d_vals;		// pointer to values of type double
	int* i_vals;		// pointer to values of type int
	
	private:
	std::string description;
};

#endif