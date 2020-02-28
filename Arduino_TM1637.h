#ifndef ARDUINO_TM1637_H
#define ARDUINO_TM1637_H

#include <Arduino.h>

class Arduino_TM1637
{
public:
    void writeByte(byte byteToSend);
    void startCondition();
    void stopCondition();
    void setBrightness(byte brightness);

    void setSegments(byte segment1, byte segment2, byte segment3, byte segment4);
    void displayNumber(int number);
};
#endif