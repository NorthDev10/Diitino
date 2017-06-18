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
  pinMap[70].PIN = &PIND;
  //PD6
  pinMap[71].mask = 0x40;
  pinMap[71].DDR = &DDRD;
  pinMap[71].PORT = &PORTD;
  pinMap[71].PIN = &PIND;
  //PH2
  pinMap[72].mask = 0x04;
  pinMap[72].DDR = &DDRH;
  pinMap[72].PORT = &PORTH;
  pinMap[72].PIN = &PINH;
  //PH7
  pinMap[73].mask = 0x80;
  pinMap[73].DDR = &DDRH;
  pinMap[73].PORT = &PORTH;
  pinMap[73].PIN = &PINH;
  //PD4
  pinMap[74].mask = 0x10;
  pinMap[74].DDR = &DDRD;
  pinMap[74].PORT = &PORTD;
  pinMap[74].PIN = &PIND;
  //PJ6
  pinMap[75].mask = 0x40;
  pinMap[75].DDR = &DDRJ;
  pinMap[75].PORT = &PORTJ;
  pinMap[75].PIN = &PINJ;
  //PJ4
  pinMap[76].mask = 0x10;
  pinMap[76].DDR = &DDRJ;
  pinMap[76].PORT = &PORTJ;
  pinMap[76].PIN = &PINJ;
  //PJ7
  pinMap[77].mask = 0x80;
  pinMap[77].DDR = &DDRJ;
  pinMap[77].PORT = &PORTJ;
  pinMap[77].PIN = &PINJ;
  //PJ2
  pinMap[78].mask = 0x04;
  pinMap[78].DDR = &DDRJ;
  pinMap[78].PORT = &PORTJ;
  pinMap[78].PIN = &PINJ;
  //PJ5
  pinMap[79].mask = 0x20;
  pinMap[79].DDR = &DDRJ;
  pinMap[79].PORT = &PORTJ;
  pinMap[79].PIN = &PINJ;
  //PJ3
  pinMap[80].mask = 0x08;
  pinMap[80].DDR = &DDRJ;
  pinMap[80].PORT = &PORTJ;
  pinMap[80].PIN = &PINJ;
  //PE2
  pinMap[81].mask = 0x04;
  pinMap[81].DDR = &DDRE;
  pinMap[81].PORT = &PORTE;
  pinMap[81].PIN = &PINE;
  //PE6
  pinMap[82].mask = 0x40;
  pinMap[82].DDR = &DDRE;
  pinMap[82].PORT = &PORTE;
  pinMap[82].PIN = &PINE;
  //PE7
  pinMap[83].mask = 0x80;
  pinMap[83].DDR = &DDRE;
  pinMap[83].PORT = &PORTE;
  pinMap[83].PIN = &PINE;
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

bool Diitino::digitalRead(uint8_t pin) {
  if(pin > 69 && pin < 100) {
    if(pin >= 84 && pin <= 99) {
      return MCP23017.digitalRead(pin);
    } else {
      if(*pinMap[pin].PIN & pinMap[pin].mask) return HIGH;
      return LOW;
    }
  } else {
    return ::digitalRead(pin);
  }
}

/*
Copyright (c) 2005-2006 David A. Mellis
///////////////////////////////////////
*/

uint8_t Diitino::shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
	uint8_t value = 0;
	uint8_t i;
	for(i = 0; i < 8; ++i) {
		this->digitalWrite(clockPin, HIGH);
		if (bitOrder == LSBFIRST) {
			value |= this->digitalRead(dataPin) << i;
		} else {
			value |= this->digitalRead(dataPin) << (7 - i);
    }
		this->digitalWrite(clockPin, LOW);
	}
	return value;
}

void Diitino::shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val) {
	uint8_t i;
	for(i = 0; i < 8; ++i)  {
		if (bitOrder == LSBFIRST) {
			this->digitalWrite(dataPin, !!(val & (1 << i)));
		} else {
			this->digitalWrite(dataPin, !!(val & (1 << (7 - i))));
		}
		this->digitalWrite(clockPin, HIGH);
		this->digitalWrite(clockPin, LOW);
	}
}
/*
///////////////////////////////////////
*/