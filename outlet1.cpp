#include "GPIO.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<cstdio>
#include<fcntl.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<pthread.h>
//using namespace exploringBB;
using namespace std;

#define PATH "/sys/class/gpio/gpio31"

string read(string path, string filename){
   ifstream fs;
   fs.open((path + filename).c_str());
   if (!fs.is_open()){
	   perror("GPIO: read failed to open file ");
    }
   string input;
   getline(fs,input);
   fs.close();
   return input;
}

int write(string path, string filename, string value){
   ofstream fs;
   fs.open((path + filename).c_str());
   if (!fs.is_open()){
	   perror("GPIO: write failed to open file ");
	   return -1;
   }
   fs << value;
   fs.close();
   return 0;
}

string getValue(){
	string input = read(PATH, "value");
	return input;
}

int main(int argc, char* argv[])
{
    string cmd(argv[1]);

    if(cmd=="on")
    {
        cout << "LED ON" << endl;
        write(PATH, "value", "1");
    }
    
    else if(cmd=="off")
    {
        cout << "LED Off" << endl;
        write(PATH, "value", "0");
    }
    
    else if(cmd=="status")
    {
        cout << "Status " << getValue() << endl;
    }
    
    else
    {
        cout << "Invalid" << endl;
    }
    
    return 0;
}