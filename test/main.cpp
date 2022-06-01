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
    pthread_t threads[3];
    int id_thread_pir;
    id_thread_pir  = pthread_create(&threads[0], NULL, pirWatcher, (void *)0);
    while(true){
        cout << pir_flag << " pir flag" << endl;
        if(pir_flag){
            cout << "Detecting QR" << endl;
            bool detected = qrDetector(TIMEOUT);
            if(detected) {
                cout<<"QR detected"<<endl;
                beepBuzzer();
            }
            pir_flag = false;

        }
    }

}

