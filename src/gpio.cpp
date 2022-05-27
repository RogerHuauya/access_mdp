#include <wiringPi.h>
#include "gpio.hpp"
#define BUZZER 14
#define PIR_SENSOR 15
#define GREEN_LED 16
#define RED_LED 17
#define DOOR_EN 18

using namespace std;
bool pir_flag;
void beepBuzzer(){
	cout<< "Beeping buzzer"<<endl;
}
void gpioSetup(){
	wiringPiSetup();
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
	pir_flag = bool(digitalRead(PIR_SENSOR));
}
