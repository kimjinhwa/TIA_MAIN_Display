#include <Arduino.h>
#include "WebsocketJsonProtocal.h"
#include "ModbusClientRTU.h"
#include "modbusServerRTU.h"
#include "BLEDevice.h"
#include "ArduinoJson.h"
#include "src/ui.h"
#include "src/ui_events.h"
#include "main.h"
#include <esp_task_wdt.h>

#define USE_SERIAL Serial
#define DEVICE_LCD

// #define TESTMODE
// #define DEVICE_BMS
struct _install_info
{
  uint8_t bmsid = 1;
  float nominalVol = 386.0;
  float maxAmp = 15.0;
  uint16_t installed = 40;
};
_install_info bmsInfo; //
struct _system_value
{
  uint8_t bmsid = 1;
  float vol = 386.0;
  float amp = 15.0;
  uint16_t installed = 40;
};
_system_value system_value;
struct _cell_value
{
  float voltage;
  float impendance;
  int16_t temperature;
};
_cell_value cellvalue[40];
static uint16_t requestAddress;
static uint16_t requestLength;
// WebSocketsClient webSocket;

#ifdef TESTMODE
const char *ssid = "iftech";
const char *password = "iftech0273";
const char *serverIP = "192.168.1.2"; // 서버의 IP 주소로 설정
const char *myIP = "192.168.1.4";     // client ip
const int serverPort = 81;
#else
const char *ssid = "BMS12V40C";
const char *password = "87654321";
const char *serverIP = "192.168.10.2"; // 서버의 IP 주소로 설정
const char *myIP = "192.168.10.11";    // client ip
const int serverPort = 81;
#endif

bool isHighVoltage = false;
bool isLowVoltage = false;
bool isHighImpedance = false;
String strServerMessage;
// ModbusClientRTU MB;

static const char *TAG = "WebsocketJsonProtocal";
// StaticJsonDocument<3072> doc;

String makeImdedanceString(uint16_t pos, float average);
String makeVoltageString(uint16_t pos, float average);
void setCelldataToDisplay();
#define MODULE_1 1
#define MODULE_2 2
uint8_t nowWindows = MODULE_1;

extern initialRomData initRomData;
bool isServerError = false;
#include <EEPROM.h>
void saveButtenEvent(lv_event_t *e)
{
  initRomData.HighVoltage = String(lv_textarea_get_text(ui_HighVoltageTxt)).toFloat() * 100; // 소수점.
  initRomData.LowVoltage = String(lv_textarea_get_text(ui_LowVoltageTxt)).toFloat() * 100;
  initRomData.HighTemp = String(lv_textarea_get_text(ui_HighTempTxt)).toInt();
  initRomData.HighImp = String(lv_textarea_get_text(ui_HighImpTxt)).toFloat() * 100;
  EEPROM.writeBytes(1, (const byte *)&initRomData, sizeof(initialRomData));
  EEPROM.commit();

  initRomData.HighVoltage = 0;
  initRomData.LowVoltage = 0;
  initRomData.HighImp = 0;
  initRomData.HighTemp = 0;

  EEPROM.readBytes(1, (byte *)&initRomData, sizeof(initRomData));
  ESP_LOGI("EEPROM", "\nInitial Memory modified");
  ESP_LOGI("EEPROM", "\ninit data \n%d %d %d %d", initRomData.HighVoltage, initRomData.LowVoltage, initRomData.HighTemp, initRomData.HighImp);
}
void ChangeModuleEvent(lv_event_t *e)
{
  // Your code here
  String cmpText(lv_label_get_text(ui_Label9));
  if (cmpText.compareTo("SET_2") == 0)
  {
    lv_label_set_text(ui_Label9, "SET_1"); // 이것은 바꿔야 할 화면 이므로 현재화면이 아니라 넘길 화면이다
    nowWindows = MODULE_2;
    lv_label_set_text(ui_HeaderTitle, "BMS BAT #2");
  }
  else
  {
    lv_label_set_text(ui_Label9, "SET_2");
    lv_label_set_text(ui_HeaderTitle, "BMS BAT #1");
    nowWindows = MODULE_1;
  };
  setCelldataToDisplay();
}
void hexdump(const void *mem, uint32_t len, uint8_t cols = 16)
{
  const uint8_t *src = (const uint8_t *)mem;
  USE_SERIAL.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
  for (uint32_t i = 0; i < len; i++)
  {
    if (i % cols == 0)
    {
      USE_SERIAL.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
    }
    USE_SERIAL.printf("%02X ", *src);
    src++;
  }
  USE_SERIAL.printf("\n");
}
void timeDisplay()
{
  // struct tm tm_ptr;
  struct tm *tm_ptr;
  struct timeval tv;
  char timeString[30];
  gettimeofday(&tv, NULL);
  tm_ptr = localtime(&tv.tv_sec);
  strftime(timeString, sizeof(timeString), "%Y-%m-%d", tm_ptr);
  sprintf(timeString, "%d-%d-%d", tm_ptr->tm_year + 1900, tm_ptr->tm_mon, tm_ptr->tm_mday);
  //ESP_LOGI("DISPLAY","%s",timeString);
  if(ui_DateLabel!= NULL)
  lv_label_set_text(ui_DateLabel, timeString);
  if(ui_DateLabel1!= NULL)
  lv_label_set_text(ui_DateLabel1, timeString);
  strftime(timeString, sizeof(timeString), "%p %I:%M:%S", tm_ptr);
  sprintf(timeString, "%d:%d:%d", tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
  //ESP_LOGI("DISPLAY","%s",timeString);
  if(ui_TimeLabel!= NULL)
  lv_label_set_text(ui_TimeLabel, timeString);
  if(ui_TimeLabel1!= NULL)
  lv_label_set_text(ui_TimeLabel1, timeString);
}
void setCelldataToDisplay()
{
  lv_obj_t *ui_vol_imp_Array_1[20][2] =
      {
          {ui_voltage1, ui_impedance1},
          {ui_voltage2, ui_impedance2},
          {ui_voltage3, ui_impedance3},
          {ui_voltage4, ui_impedance4},
          {ui_voltage5, ui_impedance5},
          {ui_voltage6, ui_impedance6},
          {ui_voltage7, ui_impedance7},
          {ui_voltage8, ui_impedance8},
          {ui_voltage9, ui_impedance9},
          {ui_voltage10, ui_impedance10},
          {ui_voltage11, ui_impedance11},
          {ui_voltage12, ui_impedance12},
          {ui_voltage13, ui_impedance13},
          {ui_voltage14, ui_impedance14},
          {ui_voltage15, ui_impedance15},
          {ui_voltage16, ui_impedance16},
          {ui_voltage17, ui_impedance17},
          {ui_voltage18, ui_impedance18},
          {ui_voltage19, ui_impedance19},
          {ui_voltage20, ui_impedance20}};

  float TotalVoltage = 0.0;
  float voltageAverage = 0.0;
  int16_t maxTemperature = 0;
  float maxVoltage = 0.0;
  float minVoltage = 100.0;
  float maxImpedance = 0.0;
  float minImpedance = 100.0;
  float impadanceAverage = 0.0;
  int i;
  int start_i = 0, end_i = 0;


  lv_label_set_text(ui_lblMessage, strServerMessage.c_str());
  if (isServerError)
    lv_obj_clear_flag(ui_lblMessage, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_lblMessage, LV_OBJ_FLAG_HIDDEN); /// Flags

  start_i = (nowWindows- 1) * 20;
  end_i = nowWindows * 20;
  for (i = start_i; i < end_i; i++)
  {
    if (maxVoltage <= cellvalue[i].voltage)
      maxVoltage = cellvalue[i].voltage;
    if (minVoltage >= cellvalue[i].voltage)
      minVoltage = cellvalue[i].voltage;

    if (maxImpedance <= cellvalue[i].voltage)
      maxImpedance = cellvalue[i].impendance;
    if (minImpedance >= cellvalue[i].voltage)
      minImpedance = cellvalue[i].impendance;

    if (maxTemperature <= cellvalue[i].voltage)
      maxTemperature = cellvalue[i].temperature;

    impadanceAverage += cellvalue[i].impendance;
    TotalVoltage += cellvalue[i].voltage;
  };
  impadanceAverage /= 20;
  voltageAverage = TotalVoltage / 20;
  // ESP_LOGI("AVG","voltageAverage %f",voltageAverage );
  // ESP_LOGI("AVG","impadanceAverage %f",impadanceAverage );
  timeDisplay();
  if(ui_TotalVoltage != NULL)
  lv_label_set_recolor(ui_TotalVoltage, true);
  if(ui_TotalVoltage!= NULL)
  lv_label_set_text(ui_TotalVoltage, String(String("Total:") + String(TotalVoltage, 0) + String("V")).c_str());
  if(ui_TotalAmpere!= NULL)
  lv_label_set_text(ui_TotalAmpere, String(String("AMP  :") + String(0, 0) + String("A")).c_str());
  if(ui_TotalTemperature!= NULL)
  lv_label_set_text(ui_TotalTemperature, String(String("TEMP :") + String(maxTemperature) + String("C")).c_str());
  // HVOL : 12.4V
  if(ui_HighVoltage!= NULL)
  lv_label_set_text(ui_HighVoltage, String(String("HVOL:") + String(maxVoltage, 2) + String("V")).c_str());
  if(ui_LowVoltage!= NULL)
  lv_label_set_text(ui_LowVoltage, String(String("LVOL:") + String(minVoltage, 2) + String("V")).c_str());
  if(ui_AverageVoltage!= NULL)
  lv_label_set_text(ui_AverageVoltage, String(String("LVOL:") + String(voltageAverage, 2) + String("V")).c_str());
  if(ui_HighImpedance!= NULL)
  lv_label_set_text(ui_HighImpedance, String(String("HIMP:") + String(maxImpedance, 2) + String("m")).c_str());
  if(ui_LowImpedance!= NULL)
  lv_label_set_text(ui_LowImpedance, String(String("LIMP:") + String(minImpedance, 2) + String("m")).c_str());
  if(ui_AverageImpendance!= NULL)
  lv_label_set_text(ui_AverageImpendance, String(String("AIMP:") + String(impadanceAverage, 2) + String("m")).c_str());

  int j;
  for (i = 0, j = start_i; i < 20; i++, j++)
  {
    if (ui_vol_imp_Array_1[i][0] != NULL && ui_vol_imp_Array_1[i][1] != NULL)
    {
      lv_label_set_recolor((lv_obj_t *)ui_vol_imp_Array_1[i][0], true);
      lv_label_set_recolor((lv_obj_t *)ui_vol_imp_Array_1[i][1], true);

      String strTemp = makeVoltageString(j, voltageAverage);
      lv_label_set_text((lv_obj_t *)ui_vol_imp_Array_1[i][0],strTemp.c_str());
      strTemp = makeImdedanceString(j, impadanceAverage);
      lv_label_set_text((lv_obj_t *)ui_vol_imp_Array_1[i][1], strTemp.c_str());
    }
    else
    {
      ESP_LOGE("D ISPLAY", "ui_vol_imp_Array_1[%d][0] is nullptr %u", i, ui_vol_imp_Array_1[i][0]);
    }
  }
}

String makeVoltageString(uint16_t pos, float average)
{
  String strVoltage="";
  char tempbuf[80];
  isHighVoltage = false;
  isLowVoltage = false;
  isHighImpedance = false;
  // ESP_LOGI("VOLTAGE ","[%d]= %d",pos,cellvalue[pos].voltage );
  if (cellvalue[pos].voltage >= initRomData.HighVoltage / 100.0)
  {
    strVoltage = "#ff0000 "; // red
    strVoltage += cellvalue[pos].voltage;
    strVoltage += "# ";
    isHighVoltage = true;
  }
  else if (cellvalue[pos].voltage < initRomData.LowVoltage / 100.0)
  {
    strVoltage = "#0000ff "; // blue
    strVoltage += cellvalue[pos].voltage;
    strVoltage += "# ";
    isLowVoltage = true;
  }
  else
    strVoltage = cellvalue[pos].voltage;
  strVoltage += "V";
  strVoltage += "(";
  sprintf(tempbuf, "%3.1f", cellvalue[pos].temperature / 100.0);
  strVoltage += String(tempbuf);
  strVoltage += ")";
  return strVoltage;
}
String makeImdedanceString(uint16_t pos, float average)
{
  String strImpdance="";
  strImpdance = String(cellvalue[pos].impendance);

  // if (cellvalue[pos].impendance > (cellvalue[pos].impendance/average))
  //  if ( 0.8 > (cellvalue[pos].impendance/average ||
  //     (cellvalue[pos].impendance/average) > 1.2) ||
  //     cellvalue[pos].impendance > initRomData.HighImp )
  if (cellvalue[pos].impendance > initRomData.HighImp)
  {
    strImpdance = "#ff0000 "; // red
    strImpdance += cellvalue[pos].impendance;
    strImpdance += "# ";
    isHighImpedance = true;
  }
  else
    strImpdance = cellvalue[pos].impendance;
  strImpdance += "m";
  return strImpdance;
}
template <typename T>
T generateRandomNumber(T min, T max)
{
  float scale = rand() / (float)RAND_MAX; // 0에서 1 사이의 값으로 스케일 조정
  T result = min + scale * (max - min);
  return (T)round(result * 1000) / 1000.0; // 소수점 세 자리까지 반올림
};
// void modbusSetup()
// {
//   MB.onDataHandler(&handleData);
//   MB.onErrorHandler(&handleError);
//   MB.setTimeout(1000);
//   MB.begin(Serial1);

// } // End of setup.

static unsigned long previousMillis_1 = 0;
const long interval_1s = 1000;

static unsigned long previousMillis_3 = 0;
const long interval_3s = 3000;

static unsigned long previousMillis_5 = 0;
const long interval_5s = 5000;

static unsigned long previousMillis_60 = 0;
const long interval_60s = 60000;

char requestContent[4] = {'E', 'V', 'T', 'I'};
uint16_t requestContentLoop = 0;
ModbusServerRTU MBserver(500);
// FC03: worker do serve Modbus function code 0x03 (READ_HOLD_REGISTER)
ModbusMessage FC03(ModbusMessage request)
{
  uint16_t address;       // requested register address
  uint16_t words;         // requested number of registers
  ModbusMessage response; // response message to be sent back

  // get request values
  request.get(2, address);
  request.get(4, words);

  // Address and words valid? We assume 10 registers here for demo
  if (address && words && (address + words) <= 10)
  {
    // Looks okay. Set up message with serverID, FC and length of data
    response.add(request.getServerID(), request.getFunctionCode(), (uint8_t)(words * 2));
    // Fill response with requested data
    for (uint16_t i = address; i < address + words; ++i)
    {
      response.add(i);
    }
  }
  else
  {
    // No, either address or words are outside the limits. Set up error response.
    response.setError(request.getServerID(), request.getFunctionCode(), ILLEGAL_DATA_ADDRESS);
  }
  return response;
}

ModbusMessage FC10(ModbusMessage request)
{
  uint16_t address;       // requested register address
  ModbusMessage response; // response message to be sent back
  uint16_t quantity;
  int len = (request.size() - 7) / 2;
  // get request values
  request.get(2, address);
  request.get(4, quantity);
  const uint8_t *data = request.data();
  uint16_t *iData = (uint16_t *)(data + 7);

  ESP_LOGI("MODBUS", "id:%d Func:%0d address:%d size : %d", 
    request.getServerID(), request.getFunctionCode(),address, request.size());

  u_int16_t temp;
  u_int16_t src;
  for (int i = 0; i < len; i++)
  {
    src = *(iData + i);
    temp = src >> 8;
    src = src << 8;
    src &= 0xFF00;
    src = src + temp;
    *(iData + i) = src;
  }
  if (address == 0 && len >= 40) // voltage
  {
    for (int i = 0; i < len; i++)
    {
      cellvalue[i].voltage = *(iData + i) / 100.0f;
    }
  }
  else if (address == 40 && len >= 40)
  { // temperature
    for (int i = 0; i < len; i++)
    {
      cellvalue[i].temperature = *(iData + i);
    }
  }
  else if (address == 80 && len >= 40)
  { // temperature
    for (int i = 0; i < len; i++)
    {
      cellvalue[i].impendance= *(iData + i)/100.0f;
    }
  }
  if (address == 120 && len >= 40)
  {
    isServerError = *(iData + 20);
    char *temp = (char *)(iData + 21);
    char *strTemp = temp;
    strServerMessage = strTemp;

    struct tm tmVal;
    struct tm *tm_ptr;
    tmVal.tm_year = (int16_t) * (iData + 0) - 1900;
    tmVal.tm_mon = (int16_t) * (iData + 1);  // month
    tmVal.tm_mday = (int16_t) * (iData + 2); // Day
    tmVal.tm_hour = (int16_t) * (iData + 3); // Hour
    tmVal.tm_min = (int16_t) * (iData + 4);  // Min
    tmVal.tm_sec = (int16_t) * (iData + 5);  // Sec
    struct timeval tv;
    tv.tv_sec = mktime(&tmVal);
    tv.tv_usec = 0;
    settimeofday(&tv, NULL);
    gettimeofday(&tv, NULL);
    tm_ptr = localtime(&tv.tv_sec);
    ESP_LOGI("TIME", "%d-%d-%d %d:%d:%d",
             tm_ptr->tm_year + 1900,
             tm_ptr->tm_mon,
             tm_ptr->tm_mday,
             tm_ptr->tm_hour,
             tm_ptr->tm_min,
             tm_ptr->tm_sec);
  }
  //setCelldataToDisplay(nowWindows);
  response.add(request.getServerID(), request.getFunctionCode(),
               address, quantity);
  return response;
};
void modbusSetup()
{
  RTUutils::prepareHardwareSerial(Serial1);
  Serial1.begin(9600, SERIAL_8N1, GPIO_NUM_18, GPIO_NUM_17);

  // Register served function code worker for server 1, FC 0x03
  MBserver.registerWorker(0x01, READ_HOLD_REGISTER, &FC03);
  MBserver.registerWorker(0x01, WRITE_MULT_REGISTERS, &FC10);

  // Start ModbusRTU background task
  MBserver.begin(Serial1);
}
void modbusService(void *parameters)
{
  modbusSetup();
  for (;;)
  {
    vTaskDelay(100);
  }
}
// void modbusService(void *parameters)
// {
//   unsigned long now;
//   //modbusSetup();
//   Error err;
//   ModbusMessage response;
//   String strStatus;
//   modbusSetup();
//   for (;;)
//   {
//     if (requestContentLoop == 4) requestContentLoop = 0;
//     now = millis();
//     if (now - previousMillis_3 >= interval_3s)
//     {
//       ESP_LOGI(TAG,"\nData request %d %c",requestContentLoop,requestContent[requestContentLoop] );
//       strStatus = "Data request.."  ;
//       strStatus += requestContentLoop;
//       strStatus += " ";
//       strStatus += requestContent[requestContentLoop] ;
//       lv_label_set_text(ui_CompanyLabel1, strStatus.c_str() );
//       // 전압을 읽어온다.
//       if (requestContent[requestContentLoop] == 'V')
//       {
//         requestAddress = 0;
//         requestLength = 40;
//       }
//       else if (requestContent[requestContentLoop] == 'T')
//       {
//         requestAddress = 40;
//         requestLength = 40;
//       }
//       else if (requestContent[requestContentLoop] == 'I')
//       {
//         requestAddress = 80;
//         requestLength = 40;
//       }
//       else if (requestContent[requestContentLoop] == 'E')
//       {
//         requestAddress = 120;
//         requestLength = 40;
//       }
//       time_t startTime = millis();
//       time_t endTime;
//       int loopCount=0;
//       MB.setTimeout(200);
//       do
//       {
//         response = MB.syncRequest(requestContent[requestContentLoop], 1, READ_INPUT_REGISTER, requestAddress, requestLength);
//         if (response.getError() == SUCCESS)
//         {
//           handleData(response, requestContent[requestContentLoop]);
//           strStatus += " OK";
//           lv_label_set_text(ui_CompanyLabel1, strStatus.c_str() );
//           break;
//         }
//         else
//         {
//           strStatus = "Retry ";
//           strStatus += loopCount;
//           lv_label_set_text(ui_CompanyLabel1, strStatus.c_str() );
//         }
//         if(loopCount++ >30)break;// 3초
//         esp_task_wdt_reset();
//       } while (response.getError() != SUCCESS);
//       MB.setTimeout(1000);
//       endTime = millis();
//       ESP_LOGI("MODBUS", "syncRequest time %d Error %d(%d)",
//         endTime - startTime,response.getError(),loopCount);
//       //서버에러가 발생하면 같은 통신을 반복한다
//       if(!isServerError)
//         requestContentLoop = requestContentLoop+1;
//       else
//         delay(1000);
//       previousMillis_3 = millis();
//     }
//     if (now - previousMillis_1 >= interval_1s)
//     {
//       timeDisplay();
//       previousMillis_1 = now;
//     }
//     esp_task_wdt_reset();
//     vTaskDelay(20);
//   };
// }
