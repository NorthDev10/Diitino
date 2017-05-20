#include <Wire.h>

#define I2C_ADR           0
#define I2C_OP            1
#define I2C_NUMBER_BYTES  2
#define I2C_READ          3
#define I2C_DATA_BYTES    4
#define I2C_WRITE         5

byte state = 0;
byte i2cAdr;
byte i2cOp;
byte i2cNumByte = 1;
byte i2cCountReadData = 0;
byte * i2cData;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Enter the address of the i2c device");
}

void loop() {
  if(Serial.available() || (state == I2C_WRITE) || (state == I2C_READ)) {
    switch(state) {
      case I2C_ADR:
        i2cAdr = strtol(Serial.readStringUntil("\n").c_str(),NULL,0);
        Serial.print("i2c Adr. ");
        Serial.println(i2cAdr, HEX);
        Serial.println("Select an operation (0 - read / 1 - write)");
        state = I2C_OP;
      break;
      case I2C_OP:
        i2cOp = strtol(Serial.readStringUntil("\n").c_str(),NULL,0);
        Serial.print("Op. ");
        Serial.println(i2cOp, HEX);
        Serial.println("How many read/write bytes?");
        state = I2C_NUMBER_BYTES;
      break;
      case I2C_NUMBER_BYTES:
        i2cNumByte = strtol(Serial.readStringUntil("\n").c_str(),NULL,0);
        Serial.print("Number of bytes: ");
        Serial.println(i2cNumByte, DEC);
        if(i2cOp) {
          state = I2C_DATA_BYTES;
          i2cData = new byte(i2cNumByte);
          Serial.println("Enter byte");
        } else {
          Wire.requestFrom(i2cAdr, i2cNumByte);
          state = I2C_READ;
          Serial.println("Byte reading...");
        }
      break;
      case I2C_READ:
        while(Wire.available()) {
          Serial.print(Wire.read(), HEX);
          Serial.print(" ");
        }
        Serial.println("\nEnter the address of the i2c device");
        state = I2C_ADR;
      break;
      case I2C_DATA_BYTES:
        if(i2cNumByte > i2cCountReadData) {
          i2cData[i2cCountReadData++] = strtol(Serial.readStringUntil("\n").c_str(),NULL,0);
          Serial.print("You sent a byte: ");
          Serial.println(i2cData[i2cCountReadData-1], HEX);
          if(i2cNumByte > i2cCountReadData) {
            Serial.println("Enter byte");
          } else state = I2C_WRITE;
        }
      break;
      case I2C_WRITE:
        i2cCountReadData = 0;
        Wire.beginTransmission(i2cAdr);
        for(byte i = 0; i < i2cNumByte; i++) {
          Wire.write(i2cData[i]);
        }
        Wire.endTransmission();
        delete[] i2cData;
        state = I2C_ADR;
        Serial.println("Byte successfully recorded");
        Serial.println("Enter the address of the i2c device");
      break;
    }
  }
}
