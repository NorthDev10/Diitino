/*
	Diitino_MCP23017.h - Library for MCP23017 I/O Port Expander.
	v0.0.2 Beta
	Created by Dmitry Drehval, May 19,2017.
*/
#include "Diitino_MCP23017.h"

void Diitino_MCP23017::init(byte i2cAdr) {
  this->i2cAdr = i2cAdr;
  /*
    Налаштування регістра конфігурацій IOCON
    BANK   :bit 7 = 0 усі регістри знаходяться в одній банці
    MIRROR :bit 6 = 0 INTA пов'язана з PortA і INTB пов'язано з PortB
    SEQOP  :bit 5 = 1 інкремент адреси регістрів, для режиму послідовних операцій включений
    DISSLW :bit 4 = 1 швидкість зміни сигналу SDA не контролюється
    HAEN   :bit 3 = 0 для мікросхеми MCP23017 недоступний
    ODR    :bit 2 = 0 активний рівень виведення переривання визначається розрядами регістру INTPOL
    INTPOL :bit 1 = 0 активний рівень виводу переривання - низький
           :bit 0 = 0 для мікросхеми MCP23017 недоступний
  */
  this->writeRG(IOCON, 0x30);
  //налаштування регістра напрямку даних IODIR для порта A та B
  Wire.beginTransmission(this->i2cAdr);
  Wire.write(IODIRA); // адреса регістра IODIRA
  Wire.write(0xFF); // всі порти A встановлюємо на введення
  Wire.write(0xFF); // всі порти B встановлюємо на введення
  Wire.endTransmission();
  //ініціалізація карти портів
  //PORTB
  pinMap[84].mask = 0x01;
  pinMap[84].adrDDR = IODIRB;
  pinMap[84].adrPORT = GPIOB;
  pinMap[84].adrGPPU = GPPUB;

  pinMap[85].mask = 0x02;
  pinMap[85].adrDDR = IODIRB;
  pinMap[85].adrPORT = GPIOB;
  pinMap[85].adrGPPU = GPPUB;

  pinMap[86].mask = 0x04;
  pinMap[86].adrDDR = IODIRB;
  pinMap[86].adrPORT = GPIOB;
  pinMap[86].adrGPPU = GPPUB;

  pinMap[87].mask = 0x08;
  pinMap[87].adrDDR = IODIRB;
  pinMap[87].adrPORT = GPIOB;
  pinMap[87].adrGPPU = GPPUB;

  pinMap[88].mask = 0x10;
  pinMap[88].adrDDR = IODIRB;
  pinMap[88].adrPORT = GPIOB;
  pinMap[88].adrGPPU = GPPUB;

  pinMap[89].mask = 0x20;
  pinMap[89].adrDDR = IODIRB;
  pinMap[89].adrPORT = GPIOB;
  pinMap[89].adrGPPU = GPPUB;

  pinMap[90].mask = 0x40;
  pinMap[90].adrDDR = IODIRB;
  pinMap[90].adrPORT = GPIOB;
  pinMap[90].adrGPPU = GPPUB;

  pinMap[91].mask = 0x80;
  pinMap[91].adrDDR = IODIRB;
  pinMap[91].adrPORT = GPIOB;
  pinMap[91].adrGPPU = GPPUB;
  //PORTA
  pinMap[92].mask = 0x01;
  pinMap[92].adrDDR = IODIRA;
  pinMap[92].adrPORT = GPIOA;
  pinMap[92].adrGPPU = GPPUA;

  pinMap[93].mask = 0x02;
  pinMap[93].adrDDR = IODIRA;
  pinMap[93].adrPORT = GPIOA;
  pinMap[93].adrGPPU = GPPUA;

  pinMap[94].mask = 0x04;
  pinMap[94].adrDDR = IODIRA;
  pinMap[94].adrPORT = GPIOA;
  pinMap[94].adrGPPU = GPPUA;

  pinMap[95].mask = 0x08;
  pinMap[95].adrDDR = IODIRA;
  pinMap[95].adrPORT = GPIOA;
  pinMap[95].adrGPPU = GPPUA;

  pinMap[96].mask = 0x10;
  pinMap[96].adrDDR = IODIRA;
  pinMap[96].adrPORT = GPIOA;
  pinMap[96].adrGPPU = GPPUA;
  
  pinMap[97].mask = 0x20;
  pinMap[97].adrDDR = IODIRA;
  pinMap[97].adrPORT = GPIOA;
  pinMap[97].adrGPPU = GPPUA;
  
  pinMap[98].mask = 0x40;
  pinMap[98].adrDDR = IODIRA;
  pinMap[98].adrPORT = GPIOA;
  pinMap[98].adrGPPU = GPPUA;
  
  pinMap[99].mask = 0x80;
  pinMap[99].adrDDR = IODIRA;
  pinMap[99].adrPORT = GPIOA;
  pinMap[99].adrGPPU = GPPUA;
}

void Diitino_MCP23017::pinMode(uint8_t pin, uint8_t mode) {
  if(pin >= 84 && pin <= 99) {
    byte newIODIRA;
    byte newGPPU;
    switch(mode) {
      case OUTPUT:
        newIODIRA = this->readRG(pinMap[pin].adrDDR);
        newIODIRA &= ~pinMap[pin].mask; // встановлюємо pin як вивід
        this->writeRG(pinMap[pin].adrDDR, newIODIRA);
      break;
      case INPUT_PULLUP://активується внутрішній підтягаючий резистор на 100k
        newGPPU = this->readRG(pinMap[pin].adrGPPU);
        newGPPU |= pinMap[pin].mask; // виконуємо підтяжку на 100k
        this->writeRG(pinMap[pin].adrGPPU, newGPPU);
        newIODIRA = this->readRG(pinMap[pin].adrDDR);
        newIODIRA |= pinMap[pin].mask; // встановлюємо pin як ввід
        this->writeRG(pinMap[pin].adrDDR, newIODIRA);
      break;
      default://INPUT
        newGPPU = this->readRG(pinMap[pin].adrGPPU);
        newGPPU &= ~pinMap[pin].mask; // вимикаємо підтяжку на 100k
        this->writeRG(pinMap[pin].adrGPPU, newGPPU);
        newIODIRA = this->readRG(pinMap[pin].adrDDR);
        newIODIRA |= pinMap[pin].mask; // встановлюємо pin як ввід
        this->writeRG(pinMap[pin].adrDDR, newIODIRA);
      break;
    }
  }
}

void Diitino_MCP23017::digitalWrite(uint8_t pin, uint8_t val) {
  if(pin >= 84 && pin <= 99) {
    byte newPORT = this->readRG(pinMap[pin].adrPORT);
    if(val == HIGH) {
      newPORT |= pinMap[pin].mask;
    } else {
      newPORT &= ~pinMap[pin].mask;
    }
    this->writeRG(pinMap[pin].adrPORT, newPORT);
  }
}

byte Diitino_MCP23017::digitalRead(uint8_t pin) {
  if(pin >= 84 && pin <= 99) {
    if(this->readRG(pinMap[pin].adrPORT) & pinMap[pin].mask) return HIGH;
    return LOW;
  }
}

void Diitino_MCP23017::writeRG(byte adrRG, byte data) {
  Wire.beginTransmission(this->i2cAdr);
  Wire.write(adrRG);
  Wire.write(data);
  Wire.endTransmission();
}

byte Diitino_MCP23017::readRG(byte adrRG) {
  //Перед читанням регістру, необхідно його вибрати
  Wire.beginTransmission(this->i2cAdr);
  Wire.write(adrRG);
  Wire.endTransmission();
  Wire.requestFrom(this->i2cAdr, 1);
  return Wire.read();
}
