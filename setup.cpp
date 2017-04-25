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
#include <stdio.h>
#include <stdlib.h>
//using namespace exploringBB;
using namespace std;

#define PATH "/sys/class/gpio/"

#define SLOT_PATH "/sys/devices/platform/bone_capemgr/"

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

int write(string path, string filename, int value){
   ostringstream s;
   s << value;
   write(path,filename,s.str());
   return 0;
}

int exportGPIO(string path, int number){
   write(path, "export", number);
   return 0;
}

int setDirection(string path, int gpio, string dir){
   ostringstream t;
   t << path << "gpio" << gpio << "/";
   int val;
   if(dir == "in"){
       val = 1;
   }
   else if(dir == "out"){
       val = 0;
   }
   else{
       cout << "Invalid";
       return 1;
   }
   switch(val){
   case 1: write(t.str(), "direction", "in");
      break;
   case 0: write(t.str(), "direction", "out");
      break;
   }
   return -1;
}

int setValue(string path, int gpio, int value){
   ostringstream t;
   t << path << "gpio" << gpio << "/";
   switch(value){
   case 1: write(t.str(), "value", "1");
      break;
   case 0: write(t.str(), "value", "0");
      break;
   }
   return -1;
}

int main(int argc, char* argv[])
{
   string cmd(argv[1]);
   
    exportGPIO(PATH, 31);
    exportGPIO(PATH, 50);
    
    setDirection(PATH, 31, "out");
    setDirection(PATH, 50, "out");
    
    if(cmd=="on")
    {
       setValue(PATH, 31, 1);
       setValue(PATH, 50, 1);
    }
    
    if(cmd=="off")
    {
       setValue(PATH, 31, 0);
       setValue(PATH, 50, 0);
    }
    
    write(SLOT_PATH, "slots", "BB-ADC");
    
    return 0;
}