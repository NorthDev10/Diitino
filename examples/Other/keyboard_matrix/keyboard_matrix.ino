#include <Wire.h>

// номер ніжки для переривання
const byte interruptPin = 3;
// прапор який сигналізує про переривання
volatile byte pinChange = false;
// дані для сканування стовпців
const byte hexData[4] = {0xFE, 0xFD, 0xFB, 0xF7};
// по цій масці дізнаємося, в якому рядку була натиснута кнопка
const byte maskRowData[4] = {0x10, 0x20, 0x40, 0x80};
const char keymap[4][4] = {
                            "123A",
                            "456B",
                            "789C",
                            "*0#D"
                          };

void setup() { // це функція виконується 1 раз
  // Ініціалізація бібліотеки Wire і підключення до шини I2C
  Wire.begin();
  // Ініціює послідовне з'єднання і задає швидкість передачі даних в bit/s (бод)
  Serial.begin(9600);
  // встановлюємо режим роботи виводу, як "введення", водночас активуючи вбудований підтягаючий резистор
  pinMode(interruptPin, INPUT_PULLUP);
  // задаємо функцію обробки зовнішнього переривання
  // функція digitalPinToInterrupt виконує перетворення номера цифрового порту в номер переривання
  attachInterrupt(digitalPinToInterrupt(interruptPin), readIOExpander, FALLING);
  // Початок передачі по шині I2C з заданою адресою
  Wire.beginTransmission(0x23); // робота з розширювачем портів PCF8574
  // записує дані в чергу
  Wire.write(0xF0);// до рядків підключимо підтягуючі резистори, а стовпці підтягнемо до землі
  // здійснює перечу байт, які були поставлені в чергу методом write()
  Wire.endTransmission();
}

void loop() { // це функція виконується постійно
  if(pinChange) {
    byte pinStatus;
    //Serial.println(pinStatus, BIN);
    for(byte i = 0; i < 4; ++i) {//col
      Wire.beginTransmission(0x23); 
      Wire.write(hexData[i]);
      Wire.endTransmission();
      Wire.requestFrom(0x23, 1);
      if(Wire.available()) {
        // зчитуємо стан виводів розширювача портів PCF8574
        pinStatus = Wire.read();
        for(byte j = 0; j < 4; ++j) {
          if((maskRowData[j] & pinStatus) == 0) {
            Serial.print(keymap[i][j]);
          }
        }
      }
    }
    Serial.println(" ");
    // Початок передачі по шині I2C з заданою адресою
    Wire.beginTransmission(0x23); // робота з розширювачем портів PCF8574
    // записує дані в чергу
    Wire.write(0xF0);// до рядків підключимо підтягуючі резистори, а стовпці підтягнемо до землі
    // здійснює перечу байт, які були поставлені в чергу методом write()
    Wire.endTransmission();
    pinChange = false;
  }
}

void readIOExpander() {
  pinChange = true;
}
