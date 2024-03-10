#include <Arduino.h>
#include "Wire.h"

#define I2C_DEV_ADDR 0x55

uint32_t i = 0;

void i2csetup() {
  Wire1.begin(12,13);
}

void i2cloop() {
  //delay(1000);
  //Write message to the slave
  Wire1.beginTransmission(I2C_DEV_ADDR);
  Wire1.printf("Hello World! %u", i++);
  Wire1.printf("Hello World! %u", i++);
  Wire1.printf("Hello World! %u", i++);
  uint8_t error = Wire1.endTransmission(true);
  Serial.printf("endTransmission: %u\n", error);
  
  //Read 16 bytes from the slave
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 16);
  Serial.printf("requestFrom: %u\n", bytesReceived);
  if((bool)bytesReceived){ //If received more than zero bytes
    uint8_t temp[bytesReceived];
    Wire.readBytes(temp, bytesReceived);
    log_print_buf(temp, bytesReceived);
  }
}
