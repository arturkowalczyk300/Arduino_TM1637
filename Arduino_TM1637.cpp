#include "Arduino_TM1637.h"

void Arduino_TM1637::startCondition()
{
    pinMode(DIO, OUTPUT);
    delayMicroseconds(_delayUs);
}

void Arduino_TM1637::stopCondition()
{
    pinMode(DIO, OUTPUT);
    delayMicroseconds(_delayUs);
    pinMode(CLK, INPUT);
    delayMicroseconds(_delayUs);
    pinMode(DIO, INPUT);
    delayMicroseconds(_delayUs);
}

bool Arduino_TM1637::writeByte(byte byteToSend)
{
    byte _byte = byteToSend;

    for (int i = 0; i < 8; i++)
    {
        pinMode(CLK, OUTPUT);
        delayMicroseconds(_delayUs);
        if (_byte & 0b00000001)
        {
            pinMode(DIO, INPUT);
        }
        else
            pinMode(DIO, OUTPUT);

        delayMicroseconds(_delayUs);
        pinMode(CLK, INPUT);
        delayMicroseconds(_delayUs);
        _byte >>= 1;
    }

    //wait for ACK -> when CLK is lowed
    pinMode(CLK, OUTPUT);
    pinMode(DIO, INPUT);
    delayMicroseconds(_delayUs);
    pinMode(CLK, INPUT);
    delayMicroseconds(_delayUs);
    bool ACK = !digitalRead(DIO); //LOW state -> ACK received
    pinMode(CLK, OUTPUT);
    delayMicroseconds(_delayUs);
}

void Arduino_TM1637::setBrightness(byte brightness)
{
}

void Arduino_TM1637::setSegments(byte segment1, byte segment2, byte segment3, byte segment4)
{
}

void Arduino_TM1637::displayNumber(int number)
{

    int units = 1;
    int tens = 2;
    int hundreds = 0;
    int thousands = 2;

    thousands = number / 1000.0;
    hundreds = (number - thousands * 1000) / 100.0;
    tens = (number - thousands * 1000 - hundreds * 100) / 10.0;
    units = number - thousands * 1000 - hundreds * 100 - tens * 10;

    startCondition();
    writeByte(0b01000000); //write data to display register command
    stopCondition();

    startCondition();
    writeByte(0b11000000);                //write to first segment address
    writeByte(characterArray[thousands]); //turn on all segments;
    writeByte(characterArray[hundreds]);  //turn on all segments;
    writeByte(characterArray[tens]);      //turn on all segments;
    writeByte(characterArray[units]);     //turn on all segments;

    stopCondition();

    startCondition();
    writeByte(0b10001111); //set maximum brightness
    stopCondition();
}