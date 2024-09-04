#include <Arduino.h>
#include "i2cForLcd.h"
//#define TEST_MODE
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <TFT_eSPI.h>
#include <esp_task_wdt.h>
#include "src/ui.h"
#include <EEPROM.h>
#include <BluetoothSerial.h>
#include <myBlueTooth.h>

#include "BleJsonProtocal.h"
#include "WebsocketJsonProtocal.h"
#include "fileSystem.h"
#include "main.h"
#include "src/ui.h"
//#include "i2cForLcd.h"
#include "wifiOTA.h"
#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin
#define TFT_BL 2
#define BRIGHT 155 
#define LED_OFF_TIME 600 
#define WDT_TIMEOUT 20 
uint16_t lcdOntime=0;

//BluetoothSerial SerialBT;
LittleFileSystem lsFile;
TaskHandle_t *h_pxblueToothTask;
extern bool isServerError;
static uint32_t screenWidth;
static uint32_t screenHeight;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;
static unsigned long last_ms;
TaskHandle_t h_modbusService;
TaskHandle_t h_WebService;

initialRomData initRomData;

Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
    9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
    15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3/m, */, 4 /* B4 */
);
// option 1:
// 7寸 50PIN 800*480
Arduino_RPi_DPI_RGBPanel *gfx = new Arduino_RPi_DPI_RGBPanel(
  bus,
//  800 /* width */, 0 /* hsync_polarity */, 8/* hsync_front_porch */, 2 /* hsync_pulse_width */, 43/* hsync_back_porch */,
//  480 /* height */, 0 /* vsync_polarity */, 8 /* vsync_front_porch */, 2/* vsync_pulse_width */, 12 /* vsync_back_porch */,
//  1 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */);

    800 /* width */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 30 /* hsync_pulse_width */, 16 /* hsync_back_porch */,
    480 /* height */, 0 /* vsync_polarity */, 22 /* vsync_front_porch */, 13 /* vsync_pulse_width */, 10 /* vsync_back_porch */,
    1 /* pclk_active_neg */, 12000000 /* prefer_speed */, true /* auto_flush */);
  
#include "touch.h"
#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
   uint32_t w = (area->x2 - area->x1 + 1);
   uint32_t h = (area->y2 - area->y1 + 1);
   gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
   lv_disp_flush_ready(disp);
}


void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;
      ledcWrite(0,BRIGHT);
      lcdOntime=0;
      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
      Serial.print( "Data xx " );
      Serial.println( data->point.x );
      Serial.print( "Data yy " );
      Serial.println( data->point.y );
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
};
void readnWriteEEProm()
{
  if (EEPROM.read(0) != 0x55)
  {
    initRomData.HighVoltage = 1445;
    initRomData.LowVoltage = 1050;
    initRomData.HighImp = 1000;
    initRomData.HighTemp = 60;
    initRomData.alarmSetStatus = 0;
    EEPROM.writeByte(0,0x55);
    EEPROM.writeBytes(1, (const byte *)&initRomData, sizeof(initialRomData));
    EEPROM.commit();
    Serial.println("Memory Initialized first booting....");
  }
  EEPROM.readBytes(1, (byte *)&initRomData, sizeof(initRomData));
  Serial.printf("\ninit data \n%d %d %d %d",initRomData.HighVoltage,initRomData.LowVoltage,initRomData.HighTemp,initRomData.HighImp);

}
void bootingReasonCheck()
{
  esp_reset_reason_t resetReson = esp_reset_reason();

  String strReset[]{
      // ESP_RST_UNKNOWN:
      " Reset reason can not be determined",
      // case ESP_RST_POWERON:
      " Reset due to power-on event",
      // case ESP_RST_EXT:
      " Reset by external pin (not applicable for ESP32)",
      // case ESP_RST_SW:
      " Software reset via esp_restart",
      // case ESP_RST_PANIC:
      " Software reset due to exception/panic",
      // case ESP_RST_INT_WDT:
      " Reset (software or hardware) due to interrupt watchdog",
      // case ESP_RST_TASK_WDT:
      " Reset due to task watchdog",
      // case ESP_RST_WDT:
      " Reset due to other watchdogs",
      // case ESP_RST_DEEPSLEEP:
      " Reset after exiting deep sleep mode",
      // case ESP_RST_BROWNOUT:
      " Brownout reset (software or hardware)",
      // case ESP_RST_SDIO:
      " Reset over SDIO",
  };

  FILE *fp;
  timeval tv;
  struct tm *timeinfo;
  gettimeofday(&tv, NULL);
  timeinfo = localtime(&tv.tv_sec);
  char timeString[30];
  strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);
  String strReason = timeString;
  strReason += strReset[resetReson];
  strReason += "\n";
  Serial.println("\n--------------------------------");
  Serial.println(strReason.c_str());
  Serial.println("--------------------------------");
  fp = fopen("/spiffs/bootLog.txt", "a+");
  if (fp == NULL)
  {
    Serial.printf("\ncellDataLogCreate Error");
    return ;
  }
  fwrite(strReason.c_str(), strReason.length(), 1, fp);
  fclose(fp);
  Serial.printf("\nRead LogFile\n");
  lsFile.cat("/spiffs/bootLog.txt");
  //fp = fopen("/spiffs/bootLog.txt", "a+");
}
void setup()
{
  EEPROM.begin(100);
  readnWriteEEProm();
  Serial.begin(BAUDRATEDEF);
  Serial1.begin(BAUDRATEDEF,SERIAL_8N1,18,17);
  //SerialBT.begin("TIMP_DISPLAY");
  lsFile.littleFsInitFast(0);
  bootingReasonCheck();
  // while (!Serial);
  Serial.println("LVGL Benchmark Demo");

  // Init Display
  // Add
  gfx->begin();
  gfx->fillScreen(BLACK);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  ledcSetup(0, 300, 8);
  ledcAttachPin(TFT_BL, 0);
  ledcWrite(0, 255); /* Screen brightness can be modified by adjusting this parameter. (0-255) */

  gfx->fillScreen(RED);
  delay(500);
  gfx->fillScreen(GREEN);
  delay(500);
  gfx->fillScreen(BLUE);
  delay(500);
  gfx->fillScreen(BLACK);
  delay(500);
  lv_init();

  // Init touch device
  pinMode(TOUCH_GT911_RST, OUTPUT);
  digitalWrite(TOUCH_GT911_RST, LOW);
  delay(10);
  digitalWrite(TOUCH_GT911_RST, HIGH);
  delay(10);
  touch_init();

  screenWidth = gfx->width();
  screenHeight = gfx->height();

  disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 6);

  if (!disp_draw_buf)
  {
    Serial.println("LVGL disp_draw_buf allocate failed!");
  }
  else
  {
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 6);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    /* Initialize the (dummy) input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    ui_init();

    lv_textarea_set_text(ui_HighVoltageTxt, String(initRomData.HighVoltage / 100.0, 2).c_str()); // voltage
    lv_textarea_set_text(ui_LowVoltageTxt, String(initRomData.LowVoltage / 100.0, 2).c_str());   // voltage
    lv_textarea_set_text(ui_HighTempTxt, String(initRomData.HighTemp).c_str());                  // voltage
    lv_textarea_set_text(ui_HighImpTxt, String(initRomData.HighImp / 100.0, 2).c_str());         // voltage
    Serial.println("Setup done");
  }
  struct tm tm;
  tm.tm_year = 2023 - 1900;
  tm.tm_mon = 11;
  tm.tm_mday = 13;
  tm.tm_hour = 15;
  tm.tm_min = 13;
  tm.tm_sec = 00;
  struct timeval tv;
  tv.tv_sec = mktime(&tm);
  tv.tv_usec = 0;
  settimeofday(&tv, NULL);
// 3884 heap byte
  xTaskCreate(blueToothTask,"blueToothTask",6000,NULL,1,h_pxblueToothTask);
// 4060 heap byte
  xTaskCreate(modbusService, "modbusService", 6000, NULL, 1, &h_modbusService);
#ifdef USEWIFI
// 3552 heap byte
  xTaskCreate(wifiWebService, "wifiWebService", 6000, NULL, 1, &h_WebService);
#endif
  //i2csetup();
  esp_task_wdt_init(WDT_TIMEOUT, true);
  esp_task_wdt_add(NULL);
};
static int interval = 1000;
static unsigned long previousmills = 0;
static int everySecondInterval = 1000;
static int every100ms= 100;
static unsigned long now;
unsigned long incTime=1;
void loop()
{
  now = millis();
  void *parameters;
  esp_task_wdt_reset();
  //modbusService(parameters);
  if ((now - previousmills > every100ms))
  {
    previousmills = now;
    incTime++;
  }
  if ((incTime % 10) == 0) // 100*10 = 1S
  {
    lcdOntime++;
    incTime++;
    if (lcdOntime >= LED_OFF_TIME) // lv_led_off(led);
      ledcWrite(0, 0);
  }
  lv_timer_handler(); /* let the GUI do its work */
  vTaskDelay(50);
}