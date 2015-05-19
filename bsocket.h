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

	int send(const char* addr, int port, int vals[], int num_vals);
	int send(const char* addr, int port, double vals[], int num_vals);
	
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

class socket_val{
	public:	
	int type;
	int port;
	int num_vals;
	
	socket_val(int type_, int port_, int num_vals_, std::string description_);
	~socket_val();
	
	void update_vals(double in_vals[]);
	void update_vals(int in_vals[]);
	void print();
	
	double* d_vals;
	int* i_vals;
	
	private:
	std::string description;
};

#endif