#include "qr.hpp"

#include <opencv2/opencv.hpp>
#include <zbar.h>

using namespace cv;
using namespace std;
using namespace zbar;
string password_key;
typedef struct{
  string type;
  string data;
  vector <Point> location;
} decodedObject;

vector<decodedObject> decode(Mat &im){
    ImageScanner scanner;
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
  
    Mat imGray;
    cvtColor(im, imGray,COLOR_BGR2GRAY);
    Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

    int n = scanner.scan(image);
    vector<decodedObject> output;
    for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol){
        decodedObject obj;
        
        obj.type = symbol->get_type_name();
        obj.data = symbol->get_data();
        
        cout << "Type : " << obj.type << endl;
        cout << "Data : " << obj.data << endl << endl;
        
        for(int i = 0; i< symbol->get_location_size(); i++){
            obj.location.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
        }
        
        output.push_back(obj);
    }
    return output;
}

void display(Mat &im, vector<decodedObject>&decodedObjects){
    for(int i = 0; i < decodedObjects.size(); i++){

        vector<Point> points = decodedObjects[i].location;
        vector<Point> hull;
        
        if(points.size() > 4)
        convexHull(points, hull);
        else
        hull = points;
        
        int n = hull.size();
        
        for(int j = 0; j < n; j++){
            line(im, hull[j], hull[ (j+1) % n], Scalar(255,0,0), 3);
        }
        
    }
    
    imwrite("Results.jpg", im);    
}

void qrDetector(){
  
    VideoCapture cap(0);
    Mat frame; 
    
    if (!cap.isOpened()) {
        cout << "cannot open camera";
    }

    while(true){
        cap >> frame;
        vector<decodedObject> decodedObjects;  
        decodedObjects = decode(frame);
    }
}