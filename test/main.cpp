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

#DEFINE TIMEOUT 5

using namespace cv;
using namespace std;
bool pir_flag;
int main() {

    gpioSetup();
    pthread_t threads[3];
    int id_thread_pir;
    id_thread_pir  = pthread_create(&threads[0], NULL, pirWatcher, (void *)0);

    while(true){

    }

}

