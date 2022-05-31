#include <unistd.h>
#include <sys/types.h>
#include "gpio.hpp"

#define BUZZER 24
#define PIR_SENSOR 20
#define GREEN_LED 17
#define YELLOW_LED 27
#define RED_LED 22
#define DOOR_EN 25

#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1

using namespace std;
bool pir_flag;
void delay(int milliseconds){
	usleep(milliseconds*1000);
}
void pinMode(int pin, int mode){
	string pin_string = to_string(pin);
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd, pin_string, pin_string.size()) != pin_string.size()) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    close(fd);

    fd = open("/sys/class/gpio/gpio"+ pin_string +"/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio"+ pin_string +"/direction");
        exit(1);
    }

	if (mode == OUTPUT){
    	if (write(fd, "out", 3) != 3) {
			perror("Error writing to /sys/class/gpio"+ pin_string +"/direction");
			exit(1);
    	}
	}

	else if (mode == INPUT){
    	if (write(fd, "in", 2) != 2) {
			perror("Error writing to /sys/class/gpio"+ pin_string +"/direction");
			exit(1);
    	}
	}

    close(fd);
}

bool digitalRead(int pin){
	string pin_string = to_string(pin);

	int fd = open("/sys/class/gpio/gpio" + pin_string + "/value", O_RONLY);
	string val = read(fd, 1);
	return val=="1"? true: false;
	close(fd)

}


bool digitalWrite(int pin, bool value){

	fd = open("/sys/class/gpio/gpio"+ to_string(pin) +"/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio"+ to_string(pin) +"/value");
        exit(1);
    }
	char svalue = value? '1':'0';
	if (write(fd, svalue, 1) != 1) {
        perror("Error writing to /sys/class/gpio/gpio"+ to_string(pin) +"/value");
        exit(1);
    }
	close(fd);
}
void beepBuzzer(){
	cout<< "Beeping buzzer"<<endl;
	digitalWrite(BUZZER, HIGH);
	delay(5000);
	digitalWrite(BUZZER, LOW);
}
void gpioSetup(){
	pinMode(BUZZER, OUTPUT);
	pinMode(DOOR_EN, OUTPUT);
	pinMode(PIR_SENSOR, INPUT);
	pinMode(GREEN_LED, INPUT);
	pinMode(RED_LED, INPUT);

	digitalWrite(DOOR_EN, LOW);
	digitalWrite(BUZZER, LOW);
}

void openDoor(){
	digitalWrite(DOOR_EN, HIGH);
	delay(500);
	digitalWrite(DOOR_EN, LOW);
}
void *pirWatcher(void * thread_id){
	if(digitalRead(PIR_SENSOR) == 1) pir_flag = true;
	delay(200);
}

