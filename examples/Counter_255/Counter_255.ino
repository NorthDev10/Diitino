#include <Diitino.h>

Diitino diitino;

//**************************************************************//
//  Name    : shiftOutCode, Hello World                         //
//  Author  : Carlyn Maw,Tom Igoe                               //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a SN54HC595 Shift Register         //
//          : to count from 0 to 255                            //
//****************************************************************

//Порт підключений до SER SN54HC595
int dataPin = 74;
//Порт підключений до RCLK SN54HC595
int latchPin = 63;
//Порт підключений до SRCLK SN54HC595
int clockPin = 62;

void setup() {
  //ініціалізація
  diitino.init(0x20);
  //встановлюємо режим порту нв вивід
  diitino.pinMode(latchPin, OUTPUT);
  diitino.pinMode(clockPin, OUTPUT);
  diitino.pinMode(dataPin, OUTPUT);
}

void loop() {
  for (int j = 0; j < 256; j++) {
    //встановлюємо LOW на latchPin поки не закінчена передача байта
    diitino.digitalWrite(latchPin, LOW);
    diitino.shiftOut(dataPin, clockPin, LSBFIRST, j);   
    //встановлюємо HIGH на latchPin, щоб проінформувати регістр, що передача закінчена.
    diitino.digitalWrite(latchPin, HIGH);
    delay(1000);
  }
}
