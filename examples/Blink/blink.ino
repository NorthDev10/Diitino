#include <Diitino.h>

Diitino diitino;

int ledPin = 92;

void setup() {
  diitino.init(0x20);
  diitino.pinMode(ledPin, OUTPUT);
}

void loop() {
  diitino.digitalWrite(ledPin, HIGH);
  delay(100);
  diitino.digitalWrite(ledPin, LOW);
  delay(100);
}