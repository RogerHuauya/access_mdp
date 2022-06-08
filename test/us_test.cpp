#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <iostream>
#include <pthread.h>

#include "qr.hpp"
#include "gpio.hpp"

#define TIMEOUT 5.0

using namespace cv;
using namespace std;


int main() {
    gpioSetup();
	cout<<"LOL"<<endl;
	while(true){
		ultras();
	}
	
	return 0;
}