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

//���� ���������� �� SER SN54HC595
int dataPin = 74;
//���� ���������� �� RCLK SN54HC595
int latchPin = 63;
//���� ���������� �� SRCLK SN54HC595
int clockPin = 62;

void setup() {
  //�����������
  diitino.init(0x20);
  //������������ ����� ����� �� ����
  diitino.pinMode(latchPin, OUTPUT);
  diitino.pinMode(clockPin, OUTPUT);
  diitino.pinMode(dataPin, OUTPUT);
}

void loop() {
  for (int j = 0; j < 256; j++) {
    //������������ LOW �� latchPin ���� �� �������� �������� �����
    diitino.digitalWrite(latchPin, LOW);
    diitino.shiftOut(dataPin, clockPin, LSBFIRST, j);   
    //������������ HIGH �� latchPin, ��� ������������� ������, �� �������� ��������.
    diitino.digitalWrite(latchPin, HIGH);
    delay(1000);
  }
}
