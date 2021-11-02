#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
 //Open the default video camera
 VideoCapture cap;

 cap.open(2);

 // if not success, exit program
 if (cap.isOpened() == false)  
 {
  cout << "Cannot open the video camera" << endl;
  cin.get(); //wait for any key press
  return -1;
 } 

 double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
 double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

 cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

 string window_name = "CameraStream";
 namedWindow(window_name); //create a window called "My Camera Feed"
 
 int edgeWidth = 5;

 while (true)
 {
  Mat frame;
  bool bSuccess = cap.read(frame); // read a new frame from video 

  //Breaking the while loop if the frames cannot be captured
  if (bSuccess == false) 
  {
   cout << "Video camera is disconnected" << endl;
   cin.get(); //Wait for any key press
   break;
  }

	Mat blurred;
	GaussianBlur(frame, blurred, Size(11, 11), 0);

	Mat bw;
	cvtColor(blurred, bw, COLOR_BGR2GRAY);

	Mat sobelx, sobely, sobelxy;
	Sobel(bw, sobelx, CV_64F, 1, 0, edgeWidth);
	Sobel(bw, sobely, CV_64F, 0, 1, edgeWidth);
	Sobel(bw, sobelxy, CV_64F, 1, 1, edgeWidth);

	Mat edges;
  Canny(bw, edges, 100, 200, 7, false);


	Mat img_color;
  // Apply the colormap:
  applyColorMap(edges, img_color, COLORMAP_JET);

	addWeighted(frame, 0.5, img_color, 0.5, 0.0, blurred);

  //show the frame in the created window
  imshow(window_name, img_color);

  //wait for for 10 ms until any key is pressed.  
  //If the 'Esc' key is pressed, break the while loop.
  //If the any other key is pressed, continue the loop 
  //If any key is not pressed withing 10 ms, continue the loop 
	
	int key = waitKey(10);

  if (key == 27)
  {
   cout << "Esc key is pressed by user. Stoppig the video" << endl;
   break;
  }else if(key == 82){
		edgeWidth += 2;	
	}else if(key == 84){
		if(edgeWidth > 3){
			edgeWidth -= 2;
		}
	}
 }

 return 0;

}
