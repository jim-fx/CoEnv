#include <wiringPi.h>

#include <iostream>

using namespace std;

int main() {
  wiringPiSetup();

  const int r = 27;
  const int g = 28;
  const int b = 29;

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

  bool isOn = false;

  while (true) {

    isOn = !isOn;

    cout << isOn << endl;

    digitalWrite(r, isOn ? 255 : 0);
    digitalWrite(g, isOn ? 0 : 255);
    digitalWrite(b, isOn ? 255 : 0);

    delay(500);
  }
}
