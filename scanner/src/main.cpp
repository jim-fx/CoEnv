#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"

#include "MFRC522.h"
#include "helpers.h"
#include "webcam.h"
#include <liquidcrystal/LiquidCrystal_I2C.h>
#include <sio_client.h>

#include <unistd.h>

using namespace cv;
using namespace std;

static int smallSize = 200;

int meanValueInMask(Mat input, Point *inputMask) {

  Mat maskMat = Mat::zeros(input.cols, input.rows, CV_8U);

  fillConvexPoly(maskMat, inputMask, 4, 255);

  // Set the average brightness
  int v = sum(mean(input, maskMat))[0];

  return v;
}

/**
 * Detect the marker corner inside the hexagon
 */
int detectMarker(std::vector<Point> points, Mat img) {

  // Average value of the content of each mask
  int values[6];

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

  // Loop through all 6 masks
  for (int j = 0; j < 6; j++) {

    float angle = singleAngle * j - singleAngle / 2.0 - 0.03;

    Point mask[4];
    for (int i = 0; i < 4; i++) {
      Point p = rotatePointOrigin(originalMask[i], origin, angle);
      // Scale the mask on the x axis
      p.x = ((p.x - origin.x) * 0.9) + origin.x;
      mask[i] = p;
    };

    // Set the average brightness
    values[j] = meanValueInMask(img, mask);
  }

  // Find the brightest mask
  int maxValue = 0;
  int maxIndex = 0;
  for (int i = 0; i < 6; i++) {
    int value = values[i];
    if (value > maxValue) {
      maxValue = value;
      maxIndex = i;
    }
  }

  return maxIndex;
}

void boxFromLine(Point *output, Point *line, float width) {

  // Create a vector from the 2 points
  Point vec = line[0] - line[1];

  // Rotate 90deg
  vec = Point(vec.y, vec.x * -1);

  // Length of vector
  double length = sqrt(pow(vec.x, 2) + pow(vec.y, 2)) / width;

  // Normalize vector length
  vec.x /= length;
  vec.y /= length;

  Point p1 = line[0] + vec;
  Point p2 = line[0] - vec;
  Point p3 = line[1] - vec;
  Point p4 = line[1] + vec;

  output[0] = p1;
  output[1] = p2;
  output[2] = p3;
  output[3] = p4;
}

Point midpoint(const Point &a, const Point &b) {
  Point ret;
  ret.x = (a.x + b.x) / 2;
  ret.y = (a.y + b.y) / 2;
  return ret;
}

void sortLines(bool *lines, int indexOfMarker) {

  bool temp[18];

  int constantOffset = 3;

  // Shift the array so the marker position is corrected
  for (int i = 0; i < 18; i++) {
    int index = (constantOffset + i + indexOfMarker * 3) % 18;
    temp[i] = lines[index];
  }

  for (int i = 0; i < 6; i++) {
    lines[0 + i] = temp[i * 3 + 1];
    lines[6 + ((i + 1) % 6)] = temp[i * 3 + 2];
    lines[12 + ((i + 1) % 6)] = temp[i * 3 + 0];
  }
}

string printBoolArray(bool *array, int split = 4) {
  string result = "";
  string t = "1";
  string f = "0";
  for (int i = 0; i < 18; i++) {
    int out = array[i] == true ? 1 : 0;
    if (array[i]) {
      result.append(t);
    } else {
      result.append(f);
    }
    std::cout << out;
    if (i % split == split - 1) {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
  return result;
}

void centerText(Mat output, std::string text, Scalar color, Point p) {
  int font = cv::FONT_HERSHEY_PLAIN;

  Size textSize = cv::getTextSize(text, font, 1, 1, 0);

  p.x -= textSize.width / 2;
  p.y -= textSize.height / 2;

  cv::putText(output, text, p, font, 1.0, Scalar(0, 255, 0), 1, false);
}

void detectLines(bool *lines, Mat inputImg) {

  Point origin(smallSize / 2, smallSize / 2);

  float singleAngle = CV_PI / 3.0;
  float maskSize = smallSize / 10.0;
  float shrinkValue = smallSize / 10.0;

  Point originalMask[3][2]{
      // Center -> MiddleRight
      {Point(origin.x + shrinkValue, origin.y),
       Point(origin.x + smallSize / 4.0 - shrinkValue, origin.y)},
      // MiddleRight -> Left
      {Point(origin.x + smallSize / 4.0 + shrinkValue, origin.y),
       Point(origin.x + smallSize / 2.0 - shrinkValue, origin.y)},
      // MiddleRIght -> Bottom
      {Point(origin.x + smallSize / 4.0 - shrinkValue / 2.0,
             origin.y + shrinkValue),
       Point(origin.x + smallSize / 8.0 + shrinkValue / 2.0,
             origin.y + smallSize / 4.0 - shrinkValue)}};

  Point boxes[18][4];
  std::vector<int> boxValues{};
  boxValues.reserve(19);

  for (int i = 0; i < 9; i++) {

    float angle = singleAngle * i - 0.03;

    Point line1[2]{rotatePointOrigin(originalMask[0][0], origin, angle),
                   rotatePointOrigin(originalMask[0][1], origin, angle)};
    Point line2[2]{rotatePointOrigin(originalMask[1][0], origin, angle),
                   rotatePointOrigin(originalMask[1][1], origin, angle)};
    Point line3[2]{rotatePointOrigin(originalMask[2][0], origin, angle),
                   rotatePointOrigin(originalMask[2][1], origin, angle)};

    boxFromLine(boxes[i * 3 + 0], line1, maskSize);
    boxFromLine(boxes[i * 3 + 1], line2, maskSize);
    boxFromLine(boxes[i * 3 + 2], line3, maskSize);

    int v1 = meanValueInMask(inputImg, boxes[i * 3 + 0]);
    int v2 = meanValueInMask(inputImg, boxes[i * 3 + 1]);
    int v3 = meanValueInMask(inputImg, boxes[i * 3 + 2]);

    // std::cout << v1 << " - " << v2 << " - " << v3 << std::endl;

    boxValues.push_back(v1);
    boxValues.push_back(v2);
    boxValues.push_back(v3);
  }

  int totalSum = 0;
  int maxValue = 0;
  int minValue = 256;
  for (int i = 0; i < 19; i++) {
    int v = boxValues[i];
    totalSum += v;
    maxValue = max(maxValue, v);
    minValue = min(minValue, v);
  }

  int meanAverage = totalSum / 18;
  int centerAverage = (minValue + maxValue) / 2;

  /* std::cout << "mean:" << meanAverage << " center:" << centerAverage
            << std::endl;*/

  Mat debugMat;
  cvtColor(inputImg, debugMat, COLOR_GRAY2RGB);

  for (int j = 0; j < 18; j++) {

    std::vector<Point> vecBox = std::vector<Point>(
        {boxes[j][0], boxes[j][1], boxes[j][2], boxes[j][3]});

    bool isOn = boxValues[j] > centerAverage;

    lines[j] = isOn;

    Scalar color = j == 0 ? Scalar(0, 0, 255)
                   : isOn ? Scalar(255, 0, 0)
                          : Scalar(0, 255, 0);

    Point center = midpoint(vecBox[0], vecBox[2]);

    centerText(debugMat, std::to_string(j), color, center);

    polylines(debugMat, vecBox, true, color, 1);
  }

  /* imshow("Standard Hough Line Transform", debugMat); */
}

string decodeHexagon(std::vector<cv::Point> contour, cv::Mat dst) {
  std::vector<cv::Point> points;

  // Approximate contour with accuracy proportional
  // to the contour perimeter
  cv::approxPolyDP(cv::Mat(contour), points,
                   cv::arcLength(cv::Mat(contour), true) * 0.02, true);

  // Skip small or non-convex objects
  if (std::fabs(cv::contourArea(contour) < 100 ||
                !cv::isContourConvex(points)) ||
      points.size() != 6) {

    cout << "No Result" << endl;
    return string();
  }

  // Get the cosines of all corners
  std::vector<double> cos;
  for (int j = 2; j < 6 + 1; j++)
    cos.push_back(angle(points[j % 6], points[j - 2], points[j - 1]));

  // Sort ascending the cosine values
  std::sort(cos.begin(), cos.end());

  // Draw center
  std::vector<cv::Point> centerRect(4);
  if (_distance(points[0], points[1]) >= _distance(points[1], points[2])) {
    centerRect[0] = points[1];
    centerRect[1] = points[3];
    centerRect[2] = points[4];
    centerRect[3] = points[0];
  } else {
    centerRect[0] = points[0];
    centerRect[1] = points[1];
    centerRect[2] = points[3];
    centerRect[3] = points[4];
  }

  Mat warped_image;
  // Stretch the image to fit the stuff
  fourPointTransform(dst, warped_image, centerRect);

  // FLip the image on the y axis
  flip(warped_image, warped_image, 1);

  // Resize the output to 200 x 200
  resize(warped_image, warped_image, Size(200, 200), 0, 0, INTER_CUBIC);

  // Convert the image to grayscale
  cvtColor(warped_image, warped_image, cv::COLOR_BGR2GRAY);

  // Auto threshold the image to two color
  threshold(warped_image, warped_image, 100, 255, THRESH_OTSU);

  int markerIndex = detectMarker(points, warped_image);
  for (int x = 0; x < 6; x++) {
    Point p = points[x];
    if (markerIndex == x) {
      cv::circle(dst, p, 4 + x, ScalarHSV2BGR(x * 20, 120, 200), 5);
    }
  }

  // Detect the detectLines
  bool lines[20];
  detectLines(lines, warped_image);

  // Arrange the array into the correct way
  sortLines(lines, markerIndex);

  return printBoolArray(lines);
}

string detectShape(cv::Mat src) {

  // Convert to grayscale
  Mat gray;
  cvtColor(src, gray, COLOR_BGR2GRAY);

  // Use Canny instead of threshold to catch squares with gradient shading
  Mat bw;
  Canny(gray, bw, 0, 50, 5);

  // Find hexagons
  vector<vector<Point>> hexagons;
  findContours(bw.clone(), hexagons, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

  sort(hexagons.begin(), hexagons.end(), compareAreas);

  int hexagonAmount = hexagons.size();

  cout << "VISUAL: ";
  if (hexagonAmount > 0) {
    int area = contourArea(hexagons[0]);
    if (area < 100) {
      cout << "small: " << area << endl;
      return string();
    }
    return decodeHexagon(hexagons[0], src);
  } else {
    cout << "No Result" << endl;
    return string();
  }
  return s;
}

LiquidCrystal_I2C *initLCD() {

  // GPIO chip i2c address
  u_int8_t i2c = 0x27;

  // Control line PINs
  u_int8_t en = 2;
  u_int8_t rw = 1;
  u_int8_t rs = 0;

  // Data line PINs
  u_int8_t d4 = 4;
  u_int8_t d5 = 5;
  u_int8_t d6 = 6;
  u_int8_t d7 = 7;

  // Backlight PIN
  u_int8_t bl = 3;

  // LCD display size (1x16, 2x16, 4x20)
  u_int8_t rows = 2;
  u_int8_t cols = 16;

  int adapter_nr = 1;
  char filename[20];

  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);

  printf("Using i2c device: %s, Rows: %u, Cols: %u\n", filename, rows, cols);

  LiquidCrystal_I2C *lcd = new LiquidCrystal_I2C(filename, i2c, en, rw, rs, d4,
                                                 d5, d6, d7, bl, POSITIVE);

  lcd->begin(cols, rows);

  return lcd;
}

// converts character array
// to string and returns it
string convertToString(char *a, int size) {
  int i;
  string s = "";
  for (i = 0; i < size; i++) {
    s = s + a[i];
  }
  return s;
}

LiquidCrystal_I2C *initLCD() {

  // GPIO chip i2c address
  u_int8_t i2c = 0x27;

  // Control line PINs
  u_int8_t en = 2;
  u_int8_t rw = 1;
  u_int8_t rs = 0;

  // Data line PINs
  u_int8_t d4 = 4;
  u_int8_t d5 = 5;
  u_int8_t d6 = 6;
  u_int8_t d7 = 7;

  // Backlight PIN
  u_int8_t bl = 3;

  // LCD display size (1x16, 2x16, 4x20)
  u_int8_t rows = 2;
  u_int8_t cols = 16;

  int adapter_nr = 1;
  char filename[20];

  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);

  printf("Using i2c device: %s, Rows: %u, Cols: %u\n", filename, rows, cols);

  LiquidCrystal_I2C *lcd = new LiquidCrystal_I2C(filename, i2c, en, rw, rs, d4,
                                                 d5, d6, d7, bl, POSITIVE);

  lcd->begin(cols, rows);

  return lcd;
}

// converts character array
// to string and returns it
string convertToString(char *a, int size) {
  int i;
  string s = "";
  for (i = 0; i < size; i++) {
    s = s + a[i];
  }
  return s;
}

void setColor(int r, int g, int b) {
  digitalWrite(27, r);
  digitalWrite(28, g);
  digitalWrite(29, b);
}

int main(int argc, char **argv) {
  /* -- WS CLIENT -- */
  sio::client h;
  h.connect("http://192.168.1.84:8080");
  h.socket()->emit("coenv-station");

  /* -- INIT RFID --  */
  MFRC522 mfrc;
  mfrc.PCD_Init();

  /* -- INIT LCD -- */
  LiquidCrystal_I2C lcd = *initLCD();

  /* -- INIT WEBCAM -- */
  int camIndex = 0;
  char *camIndexArg = argv[1];
  if (sizeof(camIndexArg) != 0) {
    camIndex = std::atoi(camIndexArg);
  }
  createCamera(camIndex, true);

  while (true) {

    // Look for a card
    if (!mfrc.PICC_IsNewCardPresent() || !mfrc.PICC_ReadCardSerial()) {
      continue;
    }

    // Print UID
    char hexstr[mfrc.uid.size * 2 + 1];
    int i;
    for (i = 0; i < mfrc.uid.size; i++) {
      sprintf(hexstr + i * 2, "%02X", mfrc.uid.uidByte[i]);
    }
    hexstr[i * 2] = 0;
    int hexstr_size = sizeof(hexstr) / sizeof(char);
    string id = convertToString(hexstr, hexstr_size);
    h.socket()->emit("rfid", id);
    cout << "RFID: " << id << endl;
    lcd.clear();
    lcd.print(hexstr);

    // Detect shape
    Mat frame;
    if (captureCamera(frame)) {
      string id = detectShape(frame);
    }

    // Sleep for a 500ms
    usleep(500 * 1000);
  }
  return 0;
}
