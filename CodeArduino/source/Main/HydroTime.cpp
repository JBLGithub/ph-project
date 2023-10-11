#include "HydroTime.h"
#include <WiFiNINA.h>
#include <ArduinoJson.h>
#include <time.h>
#include <TimeLib.h>

WiFiClient timeClient;

void setupTime()
{
  Serial.println("***************************");
  Serial.println("Setting up date and time");
  
  //Settings
  int    HTTP_PORT   = 80;
  String HTTP_METHOD = "GET"; // or "POST"
  char   HOST_NAME[] = "worldtimeapi.org"; // hostname of web server
  String PATH_NAME   = "/api/timezone/Etc/UTC";

  //Connect to web server
  if(timeClient.connect(HOST_NAME, HTTP_PORT))
  {
    Serial.println("Connected to time server");
  }
  else 
  {
    Serial.println("Connection to time server failed");
    return;
  }

  //Send http request
  timeClient.println(HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1");
  timeClient.println("Host: " + String(HOST_NAME));
  timeClient.println("Connection: close");
  timeClient.println();

  int tries = 1;
  while(!timeClient.available())
  {
    Serial.print("Waiting for response from time server... Attempt ");
    Serial.println(tries);
    if(tries == 10)
    {
      Serial.println("Server did not respond...");
      return;
    }
    tries++;
    delay(1000);
  }

  while(timeClient.available())
  {
    // read an incoming byte from the server and print them to serial monitor:
    String line1 = timeClient.readStringUntil('\n');
    line1.trim();
    String ok = "HTTP/1.1 200 OK";
    Serial.println(line1);
    if(line1.equals(ok)){
      String data = timeClient.readStringUntil('\n');
      data.trim();
      while(data.length() != 0)
      {
        data = timeClient.readStringUntil('\n');
        data.trim();
      }
      data = timeClient.readStringUntil('\n');
      getTimeFromJson(data);
    }
    else 
    {
      Serial.println("Http request failed...");
      break;
    }
  }

  timeClient.flush();
  Serial.println("Time Server flushed");
}

void getTimeFromJson(String data)
{
  DynamicJsonDocument doc(1024);
  auto error = deserializeJson(doc, data);
  if (error) {
    Serial.print("deserializeJson() failed with code ");
    Serial.println(error.c_str());
    return;
  }

  String dateString = doc["unixtime"];
  const char* date = dateString.c_str();
  Serial.print("Unix Time: ");
  Serial.println(date);

  time_t timenum = (time_t) strtol(date, NULL, 10);
  setTime(timenum);
  Serial.print("Time set successfully: ");
  Serial.println(getTimeString());
}

String getTimeString()
{
  String date = formatTime(hour());
  date += ":";
  date += formatTime(minute());
  date += ":";
  date += formatTime(second());
  return date;
}

String formatTime(int sTime)
{
  if(sTime < 10) 
  {
    return "0"+String(sTime);
  }
  return String(sTime);
}
