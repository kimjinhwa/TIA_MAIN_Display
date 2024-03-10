#include <Arduino.h>
#include <Wire.h>
#include "i2cMasterTIA.h"

#define I2C_SENDER_ADDR 0x54
#define I2C_DEV_ADDR 0x55
struct _cell_value{
  float voltage;
  float impendance;
  int16_t temperature;
};
_cell_value cellvalue[40];

void i2cMastersetup() {
  for (int i = 0; i < 40; i++)
  {
    cellvalue[i].voltage = 3.123;
    cellvalue[i].impendance = 5.432;
    cellvalue[i].temperature = 23;
  }
  Wire1.begin(13,19,10000);
}

uint32_t i = 0;
void sendCellData(uint8_t command,uint8_t address,uint8_t num){
  vTaskDelay(100);
  uint8_t sendData[1024];
  memset(sendData,0x00,1024);
  uint16_t uTemp;
  int sendLength=0;
  sendData[sendLength++] = I2C_SENDER_ADDR;
  sendData[sendLength++] = command;
  sendData[sendLength++] = address>>8;  // start address
  sendData[sendLength++] = 0x00ff & address;  // start address
  sendData[sendLength++] = 0x00;//num*2 >8;
  sendData[sendLength++] = 0x00ff & (num*2);
  int i;
  for(i=address;i<num;i++){
    if(command == 'V')
      uTemp = (uint16_t)(cellvalue[i].voltage*1000.0f);
    else if(command == 'R')
      uTemp = (uint16_t)(cellvalue[i].impendance*1000.0f);
    else if(command == 'T')
      uTemp = (uint16_t)(cellvalue[i].temperature);
    sendData[sendLength+i*2] = uTemp >> 8;
    sendData[sendLength+i*2+1] = 0x00ff & uTemp ;
  }
  Wire1.beginTransmission(I2C_DEV_ADDR);
  Wire1.write(sendData,sendLength+i*2);
  uint8_t error = Wire1.endTransmission(true);
  Serial.printf("endTransmission: %u\n", error);
}
void i2cloop() {
  //Write message to the slave
  sendCellData('V',0,40);
  sendCellData('R',0,40);
  sendCellData('T',0,40);
  //Wire1.printf("Hello World! %u", i++);
  // for(int i=0 ;i<sendLength;i++)
  //   Wire1.print(sendData[i]);
  
  //Read 16 bytes from the slave
  //vTaskDelay(100);
  uint8_t bytesReceived = Wire1.requestFrom(I2C_DEV_ADDR, 16);
  //vTaskDelay(10);
  Serial.printf("requestFrom: %u\n", bytesReceived);
  if((bool)bytesReceived){ //If received more than zero bytes
    uint8_t temp[bytesReceived];
    Wire1.readBytes(temp, bytesReceived);
    log_print_buf(temp, bytesReceived);
  }
}