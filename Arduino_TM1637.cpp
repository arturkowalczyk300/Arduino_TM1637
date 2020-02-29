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
    pinMode(CLK, OUTPUT);
    delayMicroseconds(_delayUs);
    for (int i = 0; i < 8; i++)
    {

        if (byteToSend & 0b00000001)
        {
            pinMode(DIO, INPUT);
        }
        else
            pinMode(DIO, OUTPUT);

        delayMicroseconds(_delayUs);
        pinMode(CLK, INPUT);
        delayMicroseconds(_delayUs);
        pinMode(CLK, OUTPUT);
        delayMicroseconds(_delayUs);
    }
    pinMode(DIO, INPUT);
    delayMicroseconds(_delayUs);

    //wait for ACK -> when CLK is lowed
    pinMode(CLK, OUTPUT);
    delayMicroseconds(_delayUs);
    pinMode(CLK, INPUT);
    delayMicroseconds(_delayUs);
    bool ACK = !digitalRead(DIO); //LOW state -> ACK received
    delayMicroseconds(_delayUs);
    pinMode(CLK, INPUT);
    delayMicroseconds(_delayUs);

    return ACK;
}

void Arduino_TM1637::setBrightness(byte brightness)
{
}

void Arduino_TM1637::setSegments(byte segment1, byte segment2, byte segment3, byte segment4)
{
}

void Arduino_TM1637::displayNumber(int number)
{
    startCondition();
    if (writeByte(0b01000000)) //write data to display register command
    {
        Serial.println("otrzymano ACK");
    }
    stopCondition();
}