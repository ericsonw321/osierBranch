#include "client.h"
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

using namespace std;

int main(int argc , char *argv[])
{
	tcp_client c;
	string host;
	cout << c.status() << endl;
	cout<<"Enter hostname : ";
	cin>>host;
	cout << c.status() << endl;
	c.conn(host, 12345);
	cout << c.status() << endl;
	
	c.send_data("Hello");
	
	c.disConn();
	cout << c.status() << endl;
	
	return 0;
}