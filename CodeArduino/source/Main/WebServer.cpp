#include "WebServer.h"
#include <WiFiNINA.h>

#include "HydroTime.h"
#include "phsensor.h"
#include "ecsensor.h"
#include "waterTempSensor.h"

//Web Server
char ssid[] = "MARS1";
char pass[] = "scoobydoobydo";
int keyIndex = 0;
int status = WL_IDLE_STATUS;
WiFiServer webServer(80);
WiFiClient webServerClient = webServer.available();

float wtemp_value = -1;
float ph_value = -1;
float ec_value = -1;
unsigned long seconds = 0;
unsigned long minutes = 0;

void setupWebServer() {

  Serial.println("***************************");
  enable_WiFi();
  connect_WiFi();

  webServer.begin();
  printWifiStatus();
  Serial.println("Connected Successfully");
  Serial.println("***************************");
}

void enable_WiFi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    //Error ?
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
}

void connect_WiFi() {
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void checkClient()
{
  webServerClient = webServer.available();
  if(webServerClient){
    Serial.println("***************************");
    printWEB();
    Serial.println("***************************");
  }
}

void printWEB() {

  if (webServerClient) {
    Serial.print("Client ");
    Serial.print(webServerClient.remoteIP());
    Serial.println(" is connected.");
    String currentLine = "";
    
    while (webServerClient.connected()) {
      
      if (webServerClient.available()) {
        
        char c = webServerClient.read();
        Serial.write(c);
        if (c == '\n') {
          
          if(currentLine.length() == 0) 
          {
            webServerClient.println("HTTP/1.1 200 OK");
            webServerClient.println("Content-type:text/html");
            webServerClient.println();
               
            //Print HTML
            webServerClient.print(HTMLResponse());
    
            // The HTTP response ends with another blank line:
            webServerClient.println();
            break;     
          }
          else 
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }
      }
    }
    
    // close the connection:
    webServerClient.stop();
    Serial.println("200 Response"); 
  }
}

String HTMLResponse()
{

  char wtemp_string[100];
  char ph_string[100];
  char ec_string[100];

  dtostrf(wtemp_value, 6, 3, wtemp_string);
  dtostrf(ph_value, 6, 3, ph_string);
  dtostrf(ec_value, 6, 3, ec_string);
  
  String res = "";
  res += "<!DOCTYPE html>";
  res += "<html>";
  res += "<head>";
    res += "<title>Arduino Hydro</title>";
  res += "</head>";
  res += "<body>";
    res += "<h3>Hydro Values:</h3>";
      res +=  "<p>Water Temperature: ";
      res += wtemp_string;
      res +=  " C</p>";
      res +=  "<p>Water PH: ";
      res += ph_string;
      res +=  "</p>";
      res +=  "<p>Water Nutrients: ";
      res += ec_string;
      res +=  "ppm</p>";
      res += "<p>Last Updated: ";
      res += getTimeString();
      res += " UTC</p>";
  res += "</body>";
  res += "</html>";
  return res;
}

void updateValues()
{
  wtemp_value = currentWaterTemp();
  ph_value = currentPH();
  ec_value = currentECPPM();
  Serial.println("***************************");
  Serial.print("Temp: ");
  Serial.print(wtemp_value);
  Serial.println("ºC");
  Serial.print("PH: ");
  Serial.println(ph_value);
  Serial.print("EC: ");
  Serial.print(ec_value);
  Serial.println("ppm");
  Serial.println("***************************");
}
