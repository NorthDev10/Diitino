/*
	Diitino.h - Library for Diitino.
	v0.0.2 Beta
	Created by Dmitry Drehval, May 19,2017.
*/
#include "Diitino.h"

void Diitino::init(byte i2cAdr) {
  this->i2cAdr = i2cAdr;
  Wire.begin();
  this->MCP23017.init(this->i2cAdr);
  //ініціалізація карти портів
  //PD5
  pinMap[70].mask = 0x20;
  pinMap[70].DDR = &DDRD;
  pinMap[70].PORT = &PORTD;
  //PD6
  pinMap[71].mask = 0x40;
  pinMap[71].DDR = &DDRD;
  pinMap[71].PORT = &PORTD;
  //PH2
  pinMap[72].mask = 0x04;
  pinMap[72].DDR = &DDRH;
  pinMap[72].PORT = &PORTH;
  //PH7
  pinMap[73].mask = 0x80;
  pinMap[73].DDR = &DDRH;
  pinMap[73].PORT = &PORTH;
  //PD4
  pinMap[74].mask = 0x10;
  pinMap[74].DDR = &DDRD;
  pinMap[74].PORT = &PORTD;
  //PJ6
  pinMap[75].mask = 0x40;
  pinMap[75].DDR = &DDRJ;
  pinMap[75].PORT = &PORTJ;
  //PJ4
  pinMap[76].mask = 0x10;
  pinMap[76].DDR = &DDRJ;
  pinMap[76].PORT = &PORTJ;
  //PJ7
  pinMap[77].mask = 0x80;
  pinMap[77].DDR = &DDRJ;
  pinMap[77].PORT = &PORTJ;
  //PJ2
  pinMap[78].mask = 0x04;
  pinMap[78].DDR = &DDRJ;
  pinMap[78].PORT = &PORTJ;
  //PJ5
  pinMap[79].mask = 0x20;
  pinMap[79].DDR = &DDRJ;
  pinMap[79].PORT = &PORTJ;
  //PJ3
  pinMap[80].mask = 0x08;
  pinMap[80].DDR = &DDRJ;
  pinMap[80].PORT = &PORTJ;
  //PE2
  pinMap[81].mask = 0x04;
  pinMap[81].DDR = &DDRE;
  pinMap[81].PORT = &PORTE;
  //PE6
  pinMap[82].mask = 0x40;
  pinMap[82].DDR = &DDRE;
  pinMap[82].PORT = &PORTE;
  //PE7
  pinMap[83].mask = 0x80;
  pinMap[83].DDR = &DDRE;
  pinMap[83].PORT = &PORTE;
}

void Diitino::pinMode(uint8_t pin, uint8_t mode) {
  if(pin > 69 && pin < 100) {
    if(pin >= 84 && pin <= 99) {// якщо це ніжка від розширювача портів
        MCP23017.pinMode(pin, mode);
    } else {
      //налаштування регістра напрямку даних
      uint8_t oldSREG;
      switch(mode) {
        case OUTPUT:
          oldSREG = SREG; //зберігаємо регістр стану
          cli();//забороняємо переривання
          // встановлюємо pin як вивід
          *pinMap[pin].DDR |= pinMap[pin].mask;
          SREG = oldSREG;//дозволяємо переривання
        break;
        case INPUT_PULLUP:
          oldSREG = SREG;
          cli();
          // встановлюємо pin як ввід
          *pinMap[pin].DDR &= ~pinMap[pin].mask;
          //активується внутрішній підтягаючий резистор
          *pinMap[pin].PORT |= pinMap[pin].mask;
          SREG = oldSREG;
        break;
        default://INPUT
          oldSREG = SREG;
          cli();
          // встановлюємо pin як ввід
          *pinMap[pin].DDR &= ~pinMap[pin].mask;
          //вимикаємо внутрішній підтягаючий резистор
          *pinMap[pin].PORT &= ~pinMap[pin].mask;
          SREG = oldSREG;
        break;
      }
    }
  } else {
    ::pinMode(pin, mode);
  }
}

void Diitino::digitalWrite(uint8_t pin, uint8_t val) {
  if(pin > 69 && pin < 100) {
    if(pin >= 84 && pin <= 99) {
      MCP23017.digitalWrite(pin, val);
    } else {
      uint8_t oldSREG = SREG;
      cli();
      if(val == HIGH) {
        *pinMap[pin].PORT |= pinMap[pin].mask;
      } else {
        *pinMap[pin].PORT &= ~pinMap[pin].mask;
      }
      SREG = oldSREG;
    }
  } else {
    ::digitalWrite(pin, val);
  }
}

byte Diitino::digitalRead(uint8_t pin) {
  if(pin > 69 && pin < 100) {
    if(pin >= 84 && pin <= 99) {
      return MCP23017.digitalRead(pin);
    } else {
      if(*pinMap[pin].PORT & pinMap[pin].mask) return HIGH;
      return LOW;
    }
  } else {
    return ::digitalRead(pin);
  }
}
