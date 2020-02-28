#ifndef ARDUINO_TM1637_H
#define ARDUINO_TM1637_H

#include <Arduino.h>

class Arduino_TM1637
{
private:
    int CLK;
    int DIO;

public:
    Arduino_TM1637(int CLK, int DIO)
    {
        this->CLK = CLK;
        this->DIO = DIO;
    }

    void writeByte(byte byteToSend);
    void startCondition();
    void stopCondition();
    void setBrightness(byte brightness);

    void setSegments(byte segment1, byte segment2, byte segment3, byte segment4);
    void displayNumber(int number);
};
#endif