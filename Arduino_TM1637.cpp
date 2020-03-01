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

void Arduino_TM1637::displayNumber(int number, bool showColon)
{

    int units, tens, hundreds, thousands;
    int usedDigits = number / 10.0;

    thousands = number / 1000.0;
    hundreds = (number - thousands * 1000) / 100.0;
    tens = (number - thousands * 1000 - hundreds * 100) / 10.0;
    units = number - thousands * 1000 - hundreds * 100 - tens * 10;

    if (thousands > 0)
        usedDigits = 4;
    else if (hundreds > 0)
        usedDigits = 3;
    else if (tens > 0)
        usedDigits = 2;
    else
        usedDigits = 1;

    startCondition();
    writeByte(0b01000000); //write data to display register command
    stopCondition();

    startCondition();
    writeByte(0b11000000); //write to first segment address
    if (usedDigits == 4)
        writeByte(characterArray[thousands]); //turn on all segments;
    else
        writeByte(0x00);
    if (usedDigits >= 3)
        writeByte(characterArray[hundreds] | (showColon ? 0x80 : 0x00)); //turn on all segments;
    else
        writeByte(0x00 | (showColon ? 0x80 : 0x00));
    if (usedDigits >= 2)
        writeByte(characterArray[tens]); //turn on all segments;
    else
        writeByte(0x00);
    writeByte(characterArray[units]); //turn on all segments;

    stopCondition();

    startCondition();
    writeByte(0b10001111); //set maximum brightness
    stopCondition();
}