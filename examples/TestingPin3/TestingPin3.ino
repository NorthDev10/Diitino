#include <Diitino.h>

Diitino diitino;

int ledPin = 22;

void setup() {
  Serial.begin(9600);
  diitino.init(0x20);
  diitino.pinMode(ledPin, INPUT_PULLUP);
}

void loop() {
  if(Serial.available()) {
    ledPin = Serial.parseInt();
    diitino.pinMode(ledPin, INPUT_PULLUP);
    delay(1000);
    Serial.println(ledPin, DEC);
  }
  Serial.println(diitino.digitalRead(ledPin));
  delay(2000);
}
