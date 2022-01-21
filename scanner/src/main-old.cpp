#include <iostream>
#include <fstream>
#include <cstdlib>
#include <raspicam/raspicam_still_cv.h>
using namespace std;

raspicam::RaspiCam_Still_Cv Camera;

int main ( int argc, char *argv[] ) {
    int width = 2592;
    int height =1944;//define height
    cout << "Initializing ..."<<width<<"x"<<height<<endl;
    Camera.set ( cv::CAP_PROP_FRAME_WIDTH, width );
    Camera.set ( cv::CAP_PROP_FRAME_HEIGHT, height );
    Camera.open();
    cv::Mat image;
    cout<<"capturing"<<endl;
    if ( !Camera.grab ( ) ) {
        cerr<<"Error in grab"<<endl;
        return -1;
    }
    Camera.retrieve ( image );
    cout<<"saving picture.jpg"<<endl;

    cv::imwrite ( "picture.jpg",image );
    return 0;
}

