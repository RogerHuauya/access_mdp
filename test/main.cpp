#include <opencv2/opencv.hpp>
//#include <zbar.h>
#include "sensors.hpp"
using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);

    if (!cap.isOpened()) {
    cout << "cannot open camera";
    }

    Mat save_img; cap >> save_img;
    if(save_img.empty()){
    std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
    }
    // Save the frame into a file
    imwrite("test.jpg", save_img); // A JPG FILE IS BEING SAVED

    return 0;

}

