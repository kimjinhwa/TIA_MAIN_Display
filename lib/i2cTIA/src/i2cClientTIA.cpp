
// #include <Arduino.h>
// #include "Wire.h"

// #define I2C_DEV_ADDR 0x55
// struct _cell_value{
//   float voltage;
//   float impendance;
//   int16_t temperature;
// };
// _cell_value cellvalue[40];

// uint32_t i = 0;
//  uint8_t receiveData[1024];
//   uint16_t uTemp;
// void onRequest(){
//   Wire1.print(i++);
//   Wire1.print(" Packets.");
//   Serial.println("onRequest");
// }

// void onReceive(int len)
// {
//   Serial.printf("onReceive[%d]: ", len);
//   int i = 0;
//   int startAddress = 0;
//   while (Wire1.available())
//   {
//     receiveData[i++] = Wire1.read();
//     // Serial.write(Wire1.read());
//     if (i > 1023)
//       i = 0;
//   };
//   startAddress = receiveData[2] << 8 | receiveData[3];
//   len = receiveData[4] << 8 | receiveData[5];
//   Serial.printf("\nSender %d", receiveData[0]);
//   Serial.printf("\nCommand %c", receiveData[1]);
//   Serial.printf("\nstart address %d", startAddress);
//   Serial.printf("\nData Len %d", len);
//   Serial.println();

//   if (receiveData[1] == 'V')
//   {
//     for (i = 3; startAddress < len / 2; startAddress++, i++)
//     {
//       cellvalue[startAddress].voltage = (float)((receiveData[i * 2] << 8 | receiveData[i * 2 + 1]) / 1000.0f);
//     }
//   }
//   if (receiveData[1] == 'R')
//   {
//     for (i = 3; startAddress < len / 2; startAddress++, i++)
//     {
//       cellvalue[startAddress].impendance= (float)((receiveData[i * 2] << 8 | receiveData[i * 2 + 1]) / 1000.0f);
//     }
//   }
//   if (receiveData[1] == 'T')
//   {
//     for (i = 3; startAddress < len / 2; startAddress++, i++)
//     {
//       cellvalue[startAddress].temperature = (int16_t)((receiveData[i * 2] << 8 | receiveData[i * 2 + 1]) );
//       cellvalue[startAddress].temperature -= 4000;
//     }
//   }
//   for (i = 0; i < len / 2; i++)
//   {
//     Serial.printf("\n%02d %3.3f %3.3F %d", i,cellvalue[i].voltage,cellvalue[i].impendance,cellvalue[i].temperature);
//   }
//   Serial.println();
// }

// void i2cClientsetup() {
//    uint8_t receiveData[1024];
//   memset(receiveData,0x00,1024);
//   uint16_t uTemp;
//   Serial.begin(115200);
//   Serial.setDebugOutput(true);
//   Wire1.onReceive(onReceive);
//   Wire1.onRequest(onRequest);
//   Wire1.begin((uint8_t)I2C_DEV_ADDR,13,19,10000);

// #if CONFIG_IDF_TARGET_ESP32
//   char message[64];
//   snprintf(message, 64, "%u Packets.", i++);
//   Wire1.slaveWrite((uint8_t *)message, strlen(message));
// #endif
// }

// void i2cClientloop() {
//   ;vTaskDelay(1000);
// }

//   //Wire1.i2cInit((uint8_t)I2C_DEV_ADDR,13,15);
//   //Wire1.begin((uint8_t)I2C_DEV_ADDR,4,5,100000);