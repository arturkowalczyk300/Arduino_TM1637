#include "Arduino_DS1307.h"
#include "Arduino_TM1637.h"

Arduino_DS1307 ds1307;
Arduino_TM1637 tm1637(6, 7);
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("elo");
  Wire.begin();

 // TIME_DATE_STRUCT timeDateToWrite(20,49,50,1,3,20);

  //ds1307.writeTimeDate(timeDateToWrite, WRITE_ALL);
  tm1637.displayDigits(1, 3, 5, 7, false);
  delay(1000);
}
TIME_DATE_STRUCT timeStruct(0, 0, 0, 0, 0, 0);
void loop()
{
  // put your main code here, to run repeatedly:
  timeStruct = ds1307.readTimeDate();
  Serial.print(timeStruct.hours);
  Serial.print(':');
  Serial.print(timeStruct.minutes);
  Serial.print('.');
  Serial.print(timeStruct.seconds);
  Serial.print("  ");
  Serial.print(timeStruct.day);
  Serial.print('.');
  Serial.print(timeStruct.month);
  Serial.print('.');
  Serial.print(timeStruct.year);
Serial.print("       ");
  delay(500);
    tm1637.displayDigits(timeStruct.hours / 10.0, timeStruct.hours - (timeStruct.hours/10)*10, timeStruct.minutes/ 10, timeStruct.minutes- (timeStruct.minutes/10)*10, true);
}
