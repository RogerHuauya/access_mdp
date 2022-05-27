#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <iostream>

using namespace cv;
using namespace std;


int main(){

    const clock_t begin_time = clock();
    int N = 50;
    VideoCapture cap(0);
    Mat image;
    Mat gray;
    for(int i=0;i<N;i++){
        cap >> image;
        cvtColor(image, gray, COLOR_BGR2GRAY);
    }


// do something
    float T = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    cout<<"FPS: "<<N/T<<endl;


    return 0;
}