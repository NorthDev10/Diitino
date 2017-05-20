/*
	Diitino_MCP23017.h - Library for MCP23017 I/O Port Expander.
	v0.0.2 Beta
	Created by Dmitry Drehval, May 19,2017.
*/
#ifndef Diitino_MCP23017_h
#define Diitino_MCP23017_h
#include "Arduino.h"
#include <Wire.h>

#define IODIRA      0x00
#define IODIRB      0x01
#define IPOLA       0x02
#define IPOLB       0x03
#define GPINTENA    0x04
#define GPINTENB    0x05
#define DEFVALA     0x06
#define DEFVALB     0x07
#define INTCONA     0x08
#define INTCONB     0x09
#define IOCON       0x0A
#define GPPUA       0x0C
#define GPPUB       0x0D
#define INTFA       0x0E
#define INTFB       0x0F
#define INTCAPA     0x10
#define INTCAPB     0x11
#define GPIOA       0x12
#define GPIOB       0x13
#define OLATA       0x14
#define OLATB       0x15

class Diitino_MCP23017 {
  public:
    void init(byte i2cAdr);
    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t val);
    byte digitalRead(uint8_t pin);
  protected:
    void writeRG(byte adrRG, byte data);
    byte readRG(byte adrRG);
  private:
    byte i2cAdr;
    typedef struct {
      byte mask;
      byte adrDDR;
      byte adrPORT;
      byte adrGPPU;
    } structPort;
    structPort pinMap[16];
};

#endif
