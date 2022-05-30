#include <wiringPi.h>
#include "gpio.hpp"
#define BUZZER 24
#define PIR_SENSOR 20
#define GREEN_LED 17
#define YELLOW_LED 27
#define RED_LED 22
#define DOOR_EN 25

using namespace std;
bool pir_flag;
void beepBuzzer(){
	cout<< "Beeping buzzer"<<endl;
	digitalWrite(BUZZER, HIGH);
	delay(5000);
	digitalWrite(BUZZER, LOW);
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
	if(digitalRead(PIR_SENSOR) == 1) pir_flag = true;
	delay(200);
}
