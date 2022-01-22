#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

#include <raspicam/raspicam_still_cv.h>
#include <raspicam/raspicamtypes.h>

using namespace cv;
using namespace std;
using namespace raspicam;

VideoCapture webcam;
RaspiCam_Still_Cv picam;
bool usePiCam = false;

void setWebCam(int index) {

  cout << "Opening WebCam: " << index << endl;

  webcam.open(index);

  if (webcam.isOpened() == false) {
    cout << "Cannot open the video camera" << endl;
    exit(0);
  }

  double dWidth = webcam.get(CAP_PROP_FRAME_WIDTH);
  double dHeight = webcam.get(CAP_PROP_FRAME_HEIGHT);

  cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
}

void setPiCamera(int index) {

  cout << "Opening PiCam..." << endl;
  if (!picam.open()) {
    cerr << "Error opening the camera" << endl;
    return;
  }
  double dWidth = webcam.get(CAP_PROP_FRAME_WIDTH);
  double dHeight = webcam.get(CAP_PROP_FRAME_HEIGHT);

  cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
}

bool captureCamera(Mat &image) {
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
