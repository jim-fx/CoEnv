#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <raspicam/raspicam_cv.h>
using namespace cv;
using namespace std;

class Camera {
private:
  bool usePiCam = false;
  VideoCapture webcam;
  raspicam::RaspiCam_Cv picam;

  void setPiCamera(int index) {
    this->picam.set(CAP_PROP_FORMAT, CV_8UC3);
    cout << "Opening Camera..." << endl;
    if (!this->picam.open()) {
      cerr << "Error opening the camera" << endl;
      return;
    }
  }

  void setWebCam(int index) {

    // Open the default video camera
    VideoCapture cap;

    cout << "Trying to open the camera:" << index << endl;

    cap.open(index);

    // if not success, exit program
    if (cap.isOpened() == false) {
      cout << "Cannot open the video camera" << endl;
      cin.get(); // wait for any key press
      exit(0);
    }

    double dWidth =
        cap.get(CAP_PROP_FRAME_WIDTH); // get the width of frames of the video
    double dHeight =
        cap.get(CAP_PROP_FRAME_HEIGHT); // get the height of frames of the video

    cap.set(CAP_PROP_AUTO_EXPOSURE, 1);

    cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
  }

public:
  bool capture(Mat image) {
    if (this->usePiCam) {
      bool worked = this->picam.grab();
      if (!worked)
        return false;
      this->picam.retrieve(image);
      return true;
    } else {
      return this->webcam.read(image);
    }
  }
  void createCamera(int index, bool isPi) {
    if (isPi) {
      this->setPiCamera(index);
    } else {
      this->setWebCam(index);
    }
  }
};
