#include "Arduino_TM1637.h"

Arduino_TM1637 tm1637(6, 7);
unsigned long previousMillis=0;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  tm1637.setBrightness(255);
  delay(1000);
  tm1637.displayNumber(8888, false);
  delay(1000);
}
int currentValue=0;
int endValue=1500;
bool showColon;

void loop() {
  if(millis() - previousMillis >= 100)
  {
    previousMillis = millis();
    showColon=!showColon;
  }
  
  // put your main code here, to run repeatedly:
  tm1637.displayNumber(currentValue++, showColon);
  if(currentValue>endValue) currentValue=0;
  delay(20 );
  
}
