#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "index.h"  //Web page header file

WebServer server(80);

//sensor pin
#define MQ2 34
//led pins
#define manualOut 26
#define automaticOut 27

//Enter your SSID and PASSWORD
//const char* ssid = "DIGI_6bb768";
//const char* password = "3ff09448";
const char* ssid = "HUAWEI";
const char* password = "12345678";


// This routine is executed when you open its IP in browser
void handleRoot() {
  String htmlCode = MAIN_page; //Read HTML contents
  server.send(200, "text/html", htmlCode); //Send web page
}

void handleMQ2() {
  int sensoreRead = analogRead(MQ2);//read in analog mode the sensor value
  String mqValue = String(sensoreRead);//convert int value to string
  server.send(200, "text/plane", mqValue); //Send gas sensor value only to client ajax request
}

//if the routine is called, the manual interrupt led(26 pin) get HIGH/LOW value. If was in LOW will get HIGH value
void manualInterrupt() {
  if (digitalRead(manualOut) == LOW) {
    Serial.println("int");
    digitalWrite(manualOut, HIGH);
  }
  else {
    Serial.println("not");
    digitalWrite(manualOut, LOW);
  }
}

void setup(void) {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  
  //ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connect to your wifi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  //Wait for WiFi to connect
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  //----------------------------------------------------------------
  //init the pins, input/output
  pinMode(MQ2, INPUT);
  pinMode(manualOut, OUTPUT);
  pinMode(automaticOut, OUTPUT);
  server.on("/", handleRoot);      //This is display page
  server.on("/readGas", handleMQ2);//To get update of gas sensor Value only
  server.on("/manualInterrupt", manualInterrupt);//manual interrupt
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

// This routine is executed when you open its IP in browser

void loop(void) {
  server.handleClient();
  //limit, if the value lower than 3000 there is no gas.
  int limit = 3000;
  int sensorValue = analogRead(MQ2);
  //automatic interrupt
  if (sensorValue < limit)
  {
    digitalWrite(automaticOut, LOW);
  }
  else {
    digitalWrite(automaticOut, HIGH);
  }
  delay(1);
}
