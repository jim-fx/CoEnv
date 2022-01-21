#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"

#include <raspicam/raspicam_still_cv.h>

using namespace cv;
using namespace std;

VideoCapture webcam;
raspicam::RaspiCam_Still_Cv picam;
bool usePiCam = false;

static int FRAME_WIDTH=1280;
static int FRAME_HEIGHT=720;

void setWebCam(int index) {

  webcam = *new VideoCapture();

  cout << "Opening WebCam..." << index << endl;

  webcam.set(CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
  webcam.set(CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
  webcam.set(CAP_PROP_FORMAT, CV_8UC1);

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

  cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
}

void setPiCamera(int index) {

  picam.set(CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
  picam.set(CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
  picam.set(CAP_PROP_FORMAT, CV_8UC1);

  cout << "Opening PiCam..." << endl;
  if (!picam.open()) {
    cerr << "Error opening the camera" << endl;
    return;
  }

  double dWidth =
      picam.get(CAP_PROP_FRAME_WIDTH); // get the width of frames of the video
  double dHeight = picam.get(
      CAP_PROP_FRAME_HEIGHT); // get the height of frames of the video

  cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

}

bool captureCamera(Mat image) {

  if (usePiCam) {
    cout << "Capturing from PiCam" << endl;

    if (!picam.grab()){
      cout << "Error Capturing" << endl;
      return false;
    }

    cout << "Grabbed" << endl;

    picam.retrieve(image);
    bool isEmpty = image.empty();

    cout << "Retrieved" << endl;

    if(isEmpty){
      cout << "Image is Empty" << endl;
      return false;
    }


  } else {
    cout << "Capturing from WebCam" << endl;

    bool worked = webcam.read(image);
    if(!worked){
    	return false;
    }
  }

  if(image.channels() != 3){
	cout << "Image not RGB, converting..." << endl;
      cvtColor(image, image, COLOR_GRAY2BGR);
  }

  return true;

}

void createCamera(int index, bool isPi) {
  usePiCam = isPi;
  if (isPi) {
    setPiCamera(index);
  } else {
    setWebCam(index);
  }
  return;
};
