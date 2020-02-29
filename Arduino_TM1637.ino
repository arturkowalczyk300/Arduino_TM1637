#include "Arduino_TM1637.h"

Arduino_TM1637 tm1637(7, 8);

void setup() {
  // put your setup code here, to run once:
  tm1637.setBrightness(255);
  delay(1000);
  tm1637.displayNumber(8888);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  tm1637.displayNumber(1234);
  delay(1000);
  tm1637.displayNumber(4321);
  delay(1000);
}
