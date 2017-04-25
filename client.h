#pragma once
#include<string>
#include<string.h>
#include<sys/socket.h>
#include <netinet/in.h>
using std::string;

#define HOST ""
#define PORT 80

class tcp_client
{
private:
	int sock;
	string address;
	int port;
	struct sockaddr_in server;
	
public:
	tcp_client();
	int conn(string, int);
	bool send_data(string data);
	string receive();
	int status();
	bool disConn();
};