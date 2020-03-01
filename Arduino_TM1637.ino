#include "Arduino_TM1637.h"

Arduino_TM1637 tm1637(6, 7);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  tm1637.setBrightness(255);
  delay(1000);
  tm1637.displayNumber(8888);
  delay(1000);
}
int currentValue=0;
int endValue=1500;
void loop() {
  // put your main code here, to run repeatedly:
  tm1637.displayNumber(currentValue++);
  if(currentValue>endValue) currentValue=0;
  delay(20 );
  
}
