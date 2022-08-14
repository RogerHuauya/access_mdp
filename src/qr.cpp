#include "qr.hpp"

#include <opencv2/opencv.hpp>
#include <zbar.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>
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

vector<string> hash_arr, dni_arr, name_arr;

void readAuthFile(){
    string line, word;
    hash_arr.clear();
    dni_arr.clear();
    name_arr.clear();
    ifstream file("/home/pi/access_mdp/python/auth_users.csv");
	bool header = true;
    getline(file, line);
    while(getline(file, line)){
		stringstream str(line);
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
}

string currentDate(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    string str = oss.str();
    return str;
}

void saveMark(string dni){
    string now = currentDate();
    ofstream out("/home/pi/access_mdp/python/" + now +".csv");
    out << ",hash,dni" << endl;
    out << "0,"<< dni <<","<< dni << endl;
    out.close();
}
bool qrDetector(float active_time){

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
		for(int j = 0; j < hash_arr.size(); j++){
			//cout<<"Decoded QR: "<<decodedObjects[i].data<<" compared:"<< hash_arr[j]<<endl;
			if(decodedObjects[i].data == hash_arr[j]){
			    cout<< "QR Code and auth User matched"<<endl;
                saveMark(hash_arr[j]);
			    return true;
			}
		}
            }
        }

    }
    return false;
}


