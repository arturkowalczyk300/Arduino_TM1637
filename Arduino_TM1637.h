#ifndef ARDUINO_TM1637_H
#define ARDUINO_TM1637_H

#include <Arduino.h>

class Arduino_TM1637
{
private:
    int CLK;
    int DIO;
    const int _delayUs = 100;

    byte characterArray[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

public:
    Arduino_TM1637(int CLK, int DIO)
    {
        this->CLK = CLK;
        this->DIO = DIO;

        pinMode(this->CLK, INPUT); //line stays in HIGH state because of pull-up resistors
        pinMode(this->DIO, INPUT);
    }

    bool writeByte(byte byteToSend); //returns ACK ; true -> valid ACK received
    void startCondition();
    void stopCondition();
    void setBrightness(byte brightness);
    void setSegments(int usedDigits, byte digit1, byte digit2, byte digit3, byte digit4, bool showColon);
    void displayNumber(int number, bool showColon);
    void displayDigits(byte digit1, byte digit2, byte digit3, byte digit4, bool showColon);
};
#endif