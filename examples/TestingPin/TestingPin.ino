#include <Diitino.h>

Diitino diitino;

int ledPin = 22;

void setup() {
  Serial.begin(9600);
  diitino.init(0x20);
  diitino.pinMode(ledPin, OUTPUT);
}

void loop() {
  if(Serial.available()) {
    diitino.pinMode(ledPin, INPUT_PULLUP);
    ledPin = Serial.parseInt();
    diitino.pinMode(ledPin, OUTPUT);
    delay(100);
    Serial.println(ledPin, DEC);
  }
  diitino.digitalWrite(ledPin, HIGH);
  delay(100);
  diitino.digitalWrite(ledPin, LOW);
  delay(100);
}