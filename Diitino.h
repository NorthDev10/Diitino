/*
	Diitino.h - Library for Diitino.
	v0.0.2 Beta
	Created by Dmitry Drehval, May 19,2017.
*/
#ifndef Diitino_h
#define Diitino_h
#include "Arduino.h"
#include "Diitino_MCP23017.h"
#include <Wire.h>

#define digitalPinToInterrupt(p) ((p) == 2 ? 0 :((p) == 3 ? 1 :((p) == 82 ? 6 : ((p) == 83 ? 7 : ((p) >= 18 && (p) <= 21 ? 23 - (p) : NOT_AN_INTERRUPT)))))

class Diitino {
  public:
    void Diitino::init(byte i2cAdr);
    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t val);
    bool digitalRead(uint8_t pin);
    uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
    void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
  private:
    Diitino_MCP23017 MCP23017;
    byte i2cAdr;
    typedef struct {
      uint8_t mask;
      uint8_t * DDR;
      uint8_t * PORT;
      uint8_t * PIN;
    } structPort;
    structPort pinMap[14];
};

#endif
