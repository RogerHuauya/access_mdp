#include <time.h>
#include <iostream>


#include "gpio.hpp"

#define TIMEOUT 5.0

using namespace std;
int main() {

    gpioSetup();
    beepBuzzer();
    openDoor();

}

