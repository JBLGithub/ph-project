#include <Arduino.h>

#ifndef WEBSERVER_H
#define WEBSERVER_H
void setupWebServer();
void enable_WiFi();
void connect_WiFi();
void printWifiStatus();
void checkClient();
void printWEB();
String HTMLResponse();
void updateValues();
#endif
