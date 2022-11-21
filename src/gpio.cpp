#include <sys/types.h>
#include <iostream>
#include <string>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


#include "gpio.hpp"

#define BUZZER "13"
#define PIR_SENSOR "26"
#define BLUE_LED "27"
#define WHITE_LED "22"
#define RED_LED "17"
#define DOOR_EN "5"
#define US_TRIGGER "12"
#define US_ECHO "16"

#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1

using namespace std;
bool pir_flag, us_flag;
void delay(int milliseconds){
	usleep(milliseconds*1000);
}

//Copyright (c) 2019, Alex Mous
//Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC-BY-4.0)

//C++ library to control the GPIO pins on the Raspberry Pi.
//Overview of functions:
//	setupPin	--	creates/destroys pin (1 to create and init, 0 to destroy)
//	setDirection	--	set pin direction (input/output)
//	writeValue	--	set the output voltage of the GPIO pin (1 for high, 0 for low)
//	readValue	--	read the current value of the GPIO pin (sets input pointer *output to 1 for high or 0 for low)

#include <iostream>
#include <string>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

GPIO::GPIO(const char *pin) {
//Run class setup
	pin_num = pin;
	_direction = -1; //Direction not set
	_level = -1; //Current pin level not set
}

int GPIO::setupPin(int create) { //Set create to true for creation or false to destroy pin
//Export pin (BCM number pin_num) for use as IO, NOTE: pin_num is char type
	const char *path;

	switch (create) { //Set path
		case 1:
			path = "/sys/class/gpio/export"; //export path
			break;
		case 0:
			path = "/sys/class/gpio/unexport"; //unexport path
			break;
		default:
			std::cout << "ERR (GPIO.h:setupPin): Incorrect value for create variable (must be either 0 or 1)\n";
			break;
	}

	std::ofstream file(path); //Open file
	if (file.is_open()) { //Check that file opened
		file << pin_num; //Write pin number to file
		file.close(); //Close file
	}
	else {
		std::cout << "ERR (GPIO.h:setupPin): Failed to export pin (could not open 'export' file), TRY running code as root and checking /sys/class/gpio/export exists\n";
		return 1;
	}

	char pin_path[30]; //Path for pin
	sprintf(pin_path, "/sys/class/gpio/gpio%s", pin_num);
	int status = access(pin_path, F_OK); //Access directory on system to check exists
	switch (create) {
		case 1:
			if (status < 0) { //Check for errors
				std::cout << "ERR (GPIO.h:setupPin): Failed to export GPIO pin (could not write to 'export' file), TRY running code as root and checking that /sys/class/gpio/export exists\n";
				return 1;
			}
			break;
		case 0:
			if (status >= 0) { //Check for errors (ensure that file does not exist)
				std::cout << "ERR (GPIO.h:setupPin): Failed to unexport GPIO pin (could not write to 'unexport' file), TRY running code as root and checking that /sys/class/gpio/export exists\n";				return 1;
			}
			break;
		default:
			std::cout << "ERR (GPIO.h:setupPin): Incorrect value for create variable (must be either 0 or 1)\n";
			break;
	}

	return 0;
}

int GPIO::setDirection(int direction) {
//Run setup for input/output (variable direction)
	char pin_path[35]; //Path for pin
	sprintf(pin_path, "/sys/class/gpio/gpio%s/direction", pin_num); //Format path
	std::ofstream file(pin_path); //Open file
	if (file.is_open()) { //Check that file opened
		if (direction == 1) { //Check to make sure correct formatting
			file << "out"; //Write
			_direction = 1; //Set _direction variable to prevent write on read pin
		}
		else if (direction == 0) {
			file << 0;
			_direction = 0; //Set _direction variable to prevent write on read pin
		}
		else {
			std::cout << "ERR (GPIO.h:setDirection): Incorrect value for direction variable (must be either 1 for output or 0 of input)\n";
			return 1;
		}
		file.close(); //Close
	}
	else {
		std::cout << "ERR (GPIO.h:setDirection): Failed to set direction of pin (could not open 'direction' file), TRY running code as root and checking that /sys/class/gpio/gpioN/direction exists\n";
		return 1;
	}

	return 0;
}

int GPIO::writeValue(int level) {
//Set level of pin
	if (_direction == 1) { //Check that the direction of the pin is set as an output
		char pin_path[35]; //Path for pin
		sprintf(pin_path, "/sys/class/gpio/gpio%s/value", pin_num); //Format path
		std::ofstream file(pin_path); //Open file
		if (file.is_open()) { //Check that file opened
			if (level == 1) { //Check to make sure correct formatting
				file << "1"; //Write
			}
			else if (level == 0) {
				file << "0";
			}
			else {
				std::cout << "ERR (GPIO.h:writeValue): Incorrect value for direction variable (must be either 'out' or 'in')\n";
				return 1;
			}
			file.close(); //Close
		}
		else {
			std::cout << "ERR (GPIO.h:writeValue): Failed to set value of pin (could not open 'value' file), TRY running code as root and checking that /sys/class/gpio/gpioN/value exists\n";
			return 1;
		}
	}
	else {
		std::cout << "ERR (GPIO.h:writeValue): Cannot write pin when direction is set as input (direction must be 1 to write level)\n";
	}
	return 0;
}

int GPIO::readValue(std::string *level) {
	if (_direction == 0) { //Check that the direction of the pin is set as an input
		char pin_path[35]; //Path for pin
		sprintf(pin_path, "/sys/class/gpio/gpio%s/value", pin_num); //Format path
		std::ifstream ifile(pin_path); //Open file
		if (ifile.is_open()) { //Check that file opened
			std::getline(ifile, *level);
		}
		else {
			std::cout << "ERR (GPIO.h:readValue): Failed to read pin value (could not open 'value' file), TRY running code as root and checking that /sys/class/gpio/gpioN/value exists\n";
			return 1;
		}
	}
	else {
		std::cout << "ERR (GPIO.h:readValue): Cannot read pin when direction is set as output (direction must be 0 to read level)\n";
	}
	return 0;
}

GPIO pin_buzzer(BUZZER), pin_door(DOOR_EN), pin_pir(PIR_SENSOR), pin_trigger(US_TRIGGER), pin_echo(US_ECHO);
GPIO pin_blue_led(BLUE_LED), pin_red_led(RED_LED), pin_white_led(WHITE_LED);

void beepBuzzer(){
	cout<< "Beeping buzzer"<<endl;
	pin_buzzer.writeValue(1); 
	delay(1000);
	pin_buzzer.writeValue(0); 
}
void gpioSetup(){
	
	pin_buzzer.setupPin(1);
	pin_door.setupPin(1);
	pin_pir.setupPin(1);
	pin_trigger.setupPin(1);
	pin_echo.setupPin(1);
	pin_blue_led.setupPin(1);
	pin_red_led.setupPin(1);
	pin_white_led.setupPin(1);

	pin_buzzer.setDirection(1);
	pin_door.setDirection(1);
	pin_trigger.setDirection(1);
	pin_blue_led.setDirection(1);
	pin_red_led.setDirection(1);
	pin_white_led.setDirection(1);

	pin_echo.setDirection(0);
	pin_pir.setDirection(0);

	pin_buzzer.writeValue(0);
	pin_trigger.writeValue(0);

	pin_blue_led.writeValue(0);
	pin_red_led.writeValue(1);
	pin_white_led.writeValue(1);

	//pinMode(DOOR_EN, OUTPUT);
	//pinMode(PIR_SENSOR, INPUT);
	//pinMode(GREEN_LED, INPUT);
	//pinMode(RED_LED, INPUT);

	//digitalWrite(DOOR_EN, LOW);
	//digitalWrite(BUZZER, LOW);
}

void openDoor(){
	pin_door.writeValue(1);
	pin_white_led.writeValue(0);
	pin_buzzer.writeValue(1);
	delay(500);
	pin_door.writeValue(0);
	pin_white_led.writeValue(1);
	pin_buzzer.writeValue(0);
}

void deniedLight(){
	pin_red_led.writeValue(0);
	delay(1000);
	pin_red_led.writeValue(1);
}
void *pirWatcher(void * thread_id){
	//cout<< "reading pir"<< endl;
	string flag;
	while(true){
		int status = pin_pir.readValue(&flag);
		if(flag == "1") {
			pir_flag = true;
			pin_red_led.writeValue(0);
		}
		else{
			pin_red_led.writeValue(1);
		}
		delay(100);
	}
	
}


void *usWatcher(void * thread_id){
	cout<<"Ultrasound enabled";
	for(;;){
		float d=10000.0;
		string flag;
		pin_trigger.writeValue(1);
		usleep(10);
		pin_trigger.writeValue(0);
		const clock_t begin_time = clock();

		while((float( clock () - begin_time ) /  CLOCKS_PER_SEC)<0.200){
			int status = pin_echo.readValue(&flag);
			if(flag=="1"){
				d = (float( clock () - begin_time ) /  CLOCKS_PER_SEC)*34.30;
				cout << "US presence detected  " <<d<< endl;	
			}
		}
		if(d<=1.2){
			cout << "US presence less than 1.2 m  " <<d<< endl;
			us_flag = true;
		}
	
	}

}

