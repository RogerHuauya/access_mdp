#include "qr.hpp"

#include <opencv2/opencv.hpp>
#include <zbar.h>
#include <iostream>
#include <vector>
#include <sstream>
#define QR_TYPE "QR-Code"

using namespace cv;
using namespace std;
using namespace zbar;
string password_key;
typedef struct{
  string type;
  string data;
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
        
        cout << "Type : " << obj.type << " Data : " << obj.data << endl << endl;
        
        output.push_back(obj);
    }
    return output;
}

bool qrDetector(float active_time){
    vector<string> hash_arr, dni_arr, name_arr;
    string line, word;
    ifstream file("/home/pi/access_mdp/python/auth_users.csv")			
	bool header = true;
    getline(file, line);
    while(getline(file, line)){
		row.clear()	
		stringstream str(line)
		getline(str, word, ',');
		getline(str, word, ',');
        hash_arr.push_back(word);
		getline(str, word, ',');
        dni_arr.push_back(word);
		getline(str, word, ',');
        name_arr.push_back(word);
    }
    for(int i = 0; i < hash_arr.size(); i++){
        cout << hash_arr[i] << " " << dni_arr[i] << " " << name_arr[i] << endl; 
    }
    VideoCapture cap(0);
    Mat frame; 
    
    if (!cap.isOpened()) {
        cout << "cannot open camera";
    }

    clock_t begin_time = clock();
    while(float( clock () - begin_time) < active_time*CLOCKS_PER_SEC){
        cap >> frame;
        vector<decodedObject> decodedObjects;  
        decodedObjects = decode(frame);
        for(int i = 0; i < decodedObjects.size(); i++){
            if(decodedObjects[i].type ==QR_TYPE){
                if(decodedObjects[i].data =="http://LearnOpenCV.com"){
                    return true;
                }
            }
        }

    }
    return false;
}
