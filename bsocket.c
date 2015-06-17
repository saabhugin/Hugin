#include "bsocket.h"

bsocket::bsocket(long buf_size){
	listen_timeout = 100000;	
	buffer = (unsigned char *)malloc(buf_size);
	
	
   sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(sock_raw < 0){
		printf("Socket raw Error\n");
	}
}


void bsocket::set_listen_timeout(int val){
	listen_timeout = val;
}


int bsocket::listen(){
	saddr_size = sizeof saddr;
	return recvfrom(sock_raw, buffer, 65536 ,0 ,&saddr ,&saddr_size);	
}

void bsocket::process_packet(unsigned int size, socket_val socket_vals[], int num_socket_vals){	
	unsigned short iphdrlen;
	struct iphdr *iph = (struct iphdr *)buffer;
	iphdrlen = iph->ihl*4;
	struct udphdr *udph = (struct udphdr*)(buffer + iphdrlen);	
	int udplen = ntohs(udph->len);
	int port = ntohs(udph->dest);
	
	for(int i = 0; i < num_socket_vals; i++){
		if(port == socket_vals[i].port){
			if(socket_vals[i].type == DOUBLE) udp_data2double_val(buffer + iphdrlen, udplen, socket_vals[i].d_vals, socket_vals[i].num_vals);
			if(socket_vals[i].type == INTEGER) udp_data2integer_val(buffer + iphdrlen, udplen, socket_vals[i].i_vals, socket_vals[i].num_vals);			
		}
	}
}


int bsocket::send(const char* addr, int port, int vals[], int num_vals){
	struct sockaddr_in si_other;
	int slen = sizeof(si_other);
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(port);
	if (inet_aton(addr, &si_other.sin_addr) == 0){
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
	
	// Init first 8 bytes to 0
	char message[512];
	for(int i = 0; i < 8; i++){
		message[i] = 0;
	}
	
	for(int i = 0; i < num_vals; i++){
		message[i] = (char)vals[i];
	}
		
	
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sendto(sock, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == -1){
		printf("Asendto() failed\n");
		exit(1);
	}	
	close(sock);
}

int bsocket::send(const char* addr, int port, double vals[], int num_vals){
	struct sockaddr_in si_other;
	int slen = sizeof(si_other);
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(port);
	if (inet_aton(addr , &si_other.sin_addr) == 0){
		fprintf(stderr, "Binet_aton() failed\n");
		return(-1);
	}
	
	char message[8*num_vals + 2];	// Added two bytes of space so I don't have to think about terminating null or something...
	for(int i = 0; i < 8*num_vals + 2; i++){
		message[i] = 0;
	}
	for(int i = 0; i < num_vals; i++){
		std::string hexstr = reverse_hex_string(double2hexstr(vals[i]));
		for(int u = 0; u < 8; u++){
			std::string bytestr = "0x";
			bytestr += hexstr[2*u];
			bytestr += hexstr[2*u + 1];
			
			char word_char = (unsigned char)std::stol(bytestr, 0, 16);
			message[8*i + u] = word_char;
		}
	}
	
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sendto(sock, message, num_vals*8, 0 , (struct sockaddr *) &si_other, slen) == -1){
		printf("sendto() failed\n");
		return(-1);
	}	
	close(sock);
}

// Help functions
void udp_data2double_val(unsigned char* data, int size, double d_vals[], int num_vals){	
	if(size-8 < num_vals * DOUBLE_BYTES * 2){
		printf("Not enough incoming double values. Size of packet: %i, number of values: %i\n", size, num_vals);
		return;
	}
	std::string vals_string;
	char buf[3];
	for(int i = 8; i < size; i++){
		sprintf(buf, "%02x", (unsigned char)data[i]);
		vals_string.append(buf);
	}
	
	for(int i = 0; i < num_vals; i++){
		d_vals[i] = hexstr2double(reverse_hex_string(vals_string.substr(i*16, 16)));
	}
}

void udp_data2integer_val(unsigned char* data, int size, int i_vals[], int num_vals){
	if(size-8 < num_vals * INTEGER_BYTES * 2){
		printf("Not enough incoming integer values. Size of packet: %i, number of values: %i\n", size, num_vals);
		return;
	}
	
	std::string vals_string;
	char buf[3];
	for(int i = 8; i < size; i++){
		sprintf(buf, "%02x", (unsigned char)data[i]);
		vals_string.append(buf);
	}
	
	for(int i = 0; i < num_vals; i++){
		i_vals[i] = std::stoi(((std::string)"0x").append(reverse_hex_string(vals_string.substr(i*2, 2))), 0, 16);
	}
}

std::string reverse_hex_string(std::string in_string){
	// Converts little-big endian
	std::string ret;
	int slen = in_string.length();
	for(int i = 0; i < slen; i+=2){
		ret.append(in_string.substr(slen - i - 2, 2));
	}
	return ret;
}

// If the string hexstr is faulty then there might be an out_of_range error here.
// TODO: Fix this by checking the string against something.
double hexstr2double(const std::string& hexstr){
	union{
		long long i;
		double d;
	} value;
	 	
	if(hexstr.length() == 16){
		try{
			value.i = std::stoull(hexstr, nullptr, 16);
		} catch (const std::out_of_range& e){
			printf(" --ERR\n");
			return 0.0;
		}
	} else {
		value.i = 0;
	}
	return value.d;
}

std::string double2hexstr(double x){
	union{
		long long i;
		double d;
	} value;

   value.d = x;

   char buf[17];

   snprintf (buf, sizeof(buf), "%016llx", value.i);
   buf[17] = 0; //make sure it is null terminated.

   return std::string(buf);
}


socket_val::socket_val(int type_, int port_, int num_vals_, std::string description_){
	if(port_ > 0) port = port_;
	num_vals = num_vals_;
	description = description_;
	switch(type_){
		case DOUBLE:
			d_vals = new double[num_vals];
			type = type_;
		case INTEGER:
			i_vals = new int[num_vals];
			type = type_;
			break;
		default:
			type = -1;
	}
}

socket_val::~socket_val(){
	delete[] d_vals;
	delete[] i_vals;
}


void socket_val::update_vals(double in_vals[]){
	for(int i = 0; i < num_vals; i++){
		d_vals[i] = in_vals[i];
	}
}

void socket_val::update_vals(int in_vals[]){
	for(int i = 0; i < num_vals; i++){
		i_vals[i] = in_vals[i];
	}
}

void socket_val::print(){
	printf("Type: %i, Socket: %i, vals: ", type, port);
	for(int i = 0; i < num_vals; i++){
		if(type == DOUBLE) printf("%f,", d_vals[i]);
		if(type == INTEGER) printf("%i,", i_vals[i]);
	}
	printf("\n");
}