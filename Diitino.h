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

class Diitino {
  public:
    void Diitino::init(byte i2cAdr);
    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t val);
    byte digitalRead(uint8_t pin);
  private:
    Diitino_MCP23017 MCP23017;
    byte i2cAdr;
    typedef struct {
      uint8_t mask;
      uint8_t * DDR;
      uint8_t * PORT;
    } structPort;
    structPort pinMap[14];
};

#endif
