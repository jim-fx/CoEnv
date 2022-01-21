#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <raspicam/raspicam.h>
#include <raspicam/raspicam_cv.h>
#include <raspicam/raspicamtypes.h>

using namespace cv;
using namespace std;
using namespace raspicam;

VideoCapture webcam;
RaspiCam_Cv picam;
bool usePiCam = false;

void setWebCam(int index) {

  webcam = *new VideoCapture();

  cout << "Trying to open the camera:" << index << endl;

  webcam.open(index);

  // if not success, exit program
  if (webcam.isOpened() == false) {
    cout << "Cannot open the video camera" << endl;
    cin.get(); // wait for any key press
    exit(0);
  }

  double dWidth =
      webcam.get(CAP_PROP_FRAME_WIDTH); // get the width of frames of the video
  double dHeight = webcam.get(
      CAP_PROP_FRAME_HEIGHT); // get the height of frames of the video

  webcam.set(CAP_PROP_AUTO_EXPOSURE, 1);

  cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
}

void setPiCamera(int index) {

  picam = *new RaspiCam_Cv();

  picam.set(CAP_PROP_FORMAT, CV_8UC3);
  cout << "Opening Camera..." << endl;
  if (!picam.open()) {
    cerr << "Error opening the camera" << endl;
    return;
  }
}

bool captureCamera(Mat image) {
  if (usePiCam) {
    bool worked = picam.grab();
    if (!worked)
      return false;
    picam.retrieve(image);
    return true;
  } else {
    return webcam.read(image);
  }
}

void createCamera(int index, bool isPi) {
  if (isPi) {
    setPiCamera(index);
  } else {
    setWebCam(index);
  }
};
