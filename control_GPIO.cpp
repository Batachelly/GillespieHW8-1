/* Program name control_GPIO.cpp
 * Made by Joshua Gillespie 11/10/2021
 * 
 * This program controls GPIO pins
 * first pin is p9.12, this pin is interfaced to an LED
 * The second pin is p8.16, this pin is interfaced to a push button switch
 *
 * this program sets the pin high or low based on the user’s command
 * and reads the pushbutton.
 *
 * It will take three command-line argumants 
 * 1. being GPIO number (this pin is used for output).
 * 2. hi or low
 * 3. GPIO number (this pin is used for input).
 *
 *
 *
 */


#include<iostream>
#include<fstream>
#include<string>
#include<sstream>// to manipulate strings
//#include<cstdlib>
//#include<cstdio>
#define GPIO_PATH "/sys/class/gpio/"

using namespace std;

void writeGPIO(string path, string filename, string value){
	fstream fs;
	fs.open((path + filename).c_str(), fstream::out);
	fs<<value;
	fs.close();
}

string readGPIO(string path, string filename){
	fstream fs;
	fs.open((path + filename).c_str(), fstream::in);
	string value;
	getline(fs, value);
	fs.close();
	return value;
}

int main(int argc, char* argv[]){
	if(argc != 4){
		cout << "Usage is: control_GPIO gpio_number state gpio_number" << endl;
		cout << "gpio number: GPIO number to control" << endl;
		cout << "state: hi or low" << endl;
		cout << "Example: to set GPIO 60 to hi and read GPIO 46:" << endl;
		cout << "control_GPIO 60 hi 46" << endl;
		return 2;
	}

	int gpio_num_out = stoi(argv[1]);
	string state = argv[2];
	int gpio_num_in = stoi(argv[3]);

	ostringstream s;
	s << "gpio" << gpio_num_out;
	string name = string(s.str());
	string path = GPIO_PATH + name + "/";


	// Set direction for GPIO pin to output
	writeGPIO(path, "/direction", "out");
	if(state == "hi"){
		writeGPIO(path, "/value", "1");
	}

	else if (state == "low"){
		writeGPIO(path, "/value", "0");
	}

	else{
		cout << "Command is not valid." << endl;
	}

	s.str("");
	s.clear();
	s << "gpio" << gpio_num_in;
	name = string(s.str());
	path = GPIO_PATH + name + "/";
	// Set direction for GPIO pin to output
	writeGPIO(path, "/direction", "in");
	cout << "Pushbutton is: " << readGPIO(path,"value") << endl;
}//main

