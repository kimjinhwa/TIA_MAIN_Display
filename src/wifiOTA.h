#include <Arduino.h>
#ifndef _WIFIOTA_H
#define  _WIFIOTA_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

void wifiWebService(void *parameter);
void wifiOtaloop(void) ;
#endif

