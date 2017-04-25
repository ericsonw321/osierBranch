#include "client.h"
#include<iostream>
#include <unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
using std::cout;
using std::endl;

tcp_client::tcp_client()
{
	sock = -1;
	port = 0;
	address = "";
}

int tcp_client::conn(string address , int port)
{
	int status;
	
	if(sock == -1)
	{
		sock = socket(AF_INET , SOCK_STREAM , 0);
		if (sock == -1)
		{
			perror("Could not create socket");
		}
		
		cout<<"Socket created\n";
	}
	
	if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;
         
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            herror("gethostbyname");
            cout<<"Failed to resolve hostname\n";
             
            return false;
        }
         
        addr_list = (struct in_addr **) he->h_addr_list;
 
        for(int i = 0; addr_list[i] != NULL; i++)
        {
            server.sin_addr = *addr_list[i];
             
            cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<endl;
             
            break;
        }
    }
     
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }
	
	server.sin_family = AF_INET;
	server.sin_port = htons( port );
	
	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		status = 1;
		return status;
	}
	
	cout<<"Connected\n";
	status = 0;
	return status;
}

bool tcp_client::send_data(string data)
{
	if(send(sock , data.c_str(), strlen( data.c_str() ), 0) < 0)
	{
		perror("Send failed : ");
		return false;
	}
	cout<<"Data sent\n";
	
	return true;
}

string tcp_client::receive()
{
	int size = 512;
	char buffer[size];
	string reply;
	
	recv(sock, buffer, sizeof(buffer), 0);
	
	reply = buffer;
	return reply;
}

int tcp_client::status()
{
	int status = sock;
	return status;
}

bool tcp_client::disConn()
{
	if(sock > 0)
	{
		close(sock);
		if(sock > 0)
		{
			cout << "Socket failed to close\n";
			return false;
		}
		else
			cout << "Socket closed\n";
		
		return true;
	}
}