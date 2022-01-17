# 05 Detect Corner

Today I wanted to implement the detection of the marker ad the bottom of the symbol. 
This took some time, because there was (and still is) a lot of tweaking and optimizing to be done.

This is one of the last stages in the algorithm and I had to learn how to use masks in OpenCV, which
is very good because the last steps need a lot of masking.

Here is the function that took me about 3 hours to write:

```cpp
/**
 * Detect the marker corner inside the hexagon
 */
int detectCorner(std::vector<cv::Point> points, cv::Mat img) {

  // Average value of the content of each mask
  double values[6];

  // This is the center of the image
  cv::Point origin = Point(smallSize / 2.0, smallSize / 2.0);

  float singleAngle = CV_PI / 3.0;
  float maskSize = smallSize / 10.0;

  // We create an initial mask, for the new masks we only need to rotate this
  cv::Point originalMask[] = {
      Point(origin.x, -smallSize / 20),
      Point(origin.x + maskSize, maskSize / 2),
      Point(origin.x, maskSize * 1.1),
      Point(origin.x - maskSize, maskSize / 2),
  };

  // This mat will hold our mask
  Mat maskMat = Mat::zeros(img.cols, img.rows, CV_8U);

  // We will use this one to calculate to average brigtness
  Mat testMat(img.cols, img.rows, CV_8UC3);

  // Loop through all 6 masks
  for (int j = 0; j < 6; j++) {

    float angle = singleAngle * j - singleAngle / 2.0 - 0.03;

    cv::Point mask[4];
    for (int i = 0; i < 4; i++) {
      cv::Point p = rotatePointOrigin(originalMask[i], origin, angle);
      // Scale the mask on the x axis
      p.x = ((p.x - origin.x) * 0.9) + origin.x;
      mask[i] = p;
    };

    // Clear intermediate image
    maskMat = maskMat.zeros(maskMat.rows, maskMat.cols, CV_8U);
    testMat = testMat.zeros(testMat.rows, testMat.cols, CV_8UC3);

    // Create a mask
    fillConvexPoly(maskMat, mask, 4, 255);

    // Copy the mask content to the testMat
    img.copyTo(testMat, maskMat);

    // Set the average brightness
    values[j] = sum(mean(testMat))[0];
  }

  // Find the brightest mask
  double maxValue = 0;
  int maxIndex = 0;
  for (int i = 0; i < 6; i++) {
    double value = values[i];
    if (value > maxValue) {
      maxValue = value;
      maxIndex = i;
    }
  }

  return maxIndex;
}
```

The complicated part was the creation of the mask points.
