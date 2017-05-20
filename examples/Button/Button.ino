#include <Diitino.h>

Diitino diitino;

int ledPin = 92;
int ledBtn = 93;

void setup() {
  diitino.init(0x20);
  diitino.pinMode(ledBtn, INPUT_PULLUP);
  diitino.pinMode(ledPin, OUTPUT);
}

void loop() {
  if(diitino.digitalRead(ledBtn) == LOW) {
    diitino.digitalWrite(ledPin, HIGH);
  } else {
    diitino.digitalWrite(ledPin, LOW);
  }
}