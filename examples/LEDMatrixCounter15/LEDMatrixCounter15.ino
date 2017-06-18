#include <Diitino.h>

Diitino diitino;

// Порт підключений до SER 74HC595
int receivedBytePin = 74;
// Порт підключений до RCLK 74HC595
int latchPin = 63;
// Порт підключений до SRCLK 74HC595
int clockPin = 62;
long received;
byte k = 0;
unsigned long nextCharacter = 0;
unsigned long dynamicIndication = 0;
void drawSymbol();

void setup() {
  diitino.init(0x20);
  //устанавливаем режим порта выхода
  diitino.pinMode(latchPin, OUTPUT);
  diitino.pinMode(clockPin, OUTPUT);
  diitino.pinMode(receivedBytePin, OUTPUT);
}

const byte ledHexMap[16][8] = {{/*0*/0x00,0x38,0x44,0x4C,0x54,0x64,0x44,0x38},
                               {/*1*/0x00,0x10,0x30,0x10,0x10,0x10,0x10,0x38},
                               {/*2*/0x00,0x38,0x44,0x04,0x08,0x10,0x20,0x7C},
                               {/*3*/0x00,0x7C,0x08,0x10,0x08,0x04,0x44,0x38},
                               {/*4*/0x00,0x08,0x18,0x28,0x48,0x7C,0x08,0x08},
                               {/*5*/0x00,0x7C,0x40,0x78,0x04,0x04,0x44,0x38},
                               {/*6*/0x00,0x18,0x20,0x40,0x78,0x44,0x44,0x38},
                               {/*7*/0x00,0x7C,0x04,0x08,0x10,0x20,0x20,0x20},
                               {/*8*/0x00,0x38,0x44,0x44,0x38,0x44,0x44,0x38},
                               {/*9*/0x00,0x38,0x44,0x44,0x3C,0x04,0x08,0x30},
                               {/*A*/0x00,0x38,0x44,0x44,0x44,0x7C,0x44,0x44},
                               {/*B*/0x00,0x78,0x44,0x44,0x78,0x44,0x44,0x78},
                               {/*C*/0x00,0x38,0x44,0x40,0x40,0x40,0x44,0x38},
                               {/*D*/0x00,0x70,0x48,0x44,0x44,0x44,0x48,0x70},
                               {/*E*/0x00,0x7C,0x40,0x40,0x78,0x40,0x40,0x7C},
                               {/*F*/0x00,0x7C,0x40,0x40,0x78,0x40,0x40,0x40}
                              };

void loop() {
  if(micros() - dynamicIndication > 1000) {
    dynamicIndication = micros();
    drawSymbol(k);
  }
  if(millis() - nextCharacter > 2000) {
    nextCharacter = millis();
    if(++k >= 16) k = 0;
  }
}

void drawSymbol(byte indexSymbol) {
  static byte i = 0;
  static word j = 1;
  //встановлюємо LOW на latchPin поки не закінчена передача байта
  diitino.digitalWrite(latchPin, LOW);
  diitino.shiftOut(receivedBytePin, clockPin, LSBFIRST, ledHexMap[indexSymbol][i++]);
  diitino.shiftOut(receivedBytePin, clockPin, MSBFIRST, ~j);
  //встановлюємо HIGH на latchPin, щоб проінформувати регістр, що передача закінчена.
  diitino.digitalWrite(latchPin, HIGH);
  j += j;
  if(j > 128) j = 1;//вибираємо рядок матриці, який буде виводитись
  if(i > 7) i = 0;//вибираємо рядок цифри, який буде виводитись
}
