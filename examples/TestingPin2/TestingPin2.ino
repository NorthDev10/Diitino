#include <Diitino.h>

Diitino diitino;

int ledPin = 22;

void setup() {
  Serial.begin(9600);
  diitino.init(0x20);
  diitino.pinMode(abs(ledPin), OUTPUT);
}

void loop() {
  if(Serial.available()) {
    ledPin = Serial.parseInt();
    diitino.pinMode(abs(ledPin), OUTPUT);
    delay(100);
    if(ledPin > 0) {
      diitino.digitalWrite(abs(ledPin), HIGH);
    } else {
      diitino.digitalWrite(abs(ledPin), LOW);
    }
    Serial.println(ledPin, DEC);
  }
}
