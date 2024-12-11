#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

AsyncWebServer server(80);

Servo liftServo1, liftServo2, liftServo3, liftServo4, liftServo5, liftServo6;
Servo spinServo1, spinServo2, spinServo3, spinServo4, spinServo5, spinServo6;

int liftServo1Pin = 12;
int liftServo2Pin = 13;
int liftServo3Pin = 14;
int liftServo4Pin = 15;
int liftServo5Pin = 16;
int liftServo6Pin = 17;

int spinServo1Pin = 18;
int spinServo2Pin = 19;
int spinServo3Pin = 20;
int spinServo4Pin = 21;
int spinServo5Pin = 22;
int spinServo6Pin = 23;

char webpage[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
<body>

<center>
<h1>Servo Controls</h1>

<h3> Move to 90 </h3>
<button onclick="window.location = 'http://esp.local/servo90/on'">On</button><button onclick="window.location = 'http://esp.local/servo/off'">Off</button>
<h3> Move to 180</h3>
<button onclick="window.location = 'http://esp.local/servo180/on'">On</button><button onclick="window.location = 'http://esp.local/servo/off'">Off</button>

</center>
</body>
</html>

)=====";

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}

void setup(void)
{
  
  Serial.begin(115200);
  
  servo1.attach(servo1Pin);

  liftServo1.attach(liftServo1Pin)
  liftServo2.attach(liftServo2Pin)
  liftServo3.attach(liftServo3Pin)
  liftServo4.attach(liftServo4Pin)
  liftServo5.attach(liftServo5Pin)
  liftServo6.attach(liftServo6Pin)

  spinServo1.attach(spinServo1Pin)
  spinServo2.attach(spinServo2Pin)
  spinServo3.attach(spinServo3Pin)
  spinServo4.attach(spinServo4Pin)
  spinServo5.attach(spinServo5Pin)
  spinServo6.attach(spinServo6Pin)

  WiFi.softAP("swan dress", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("swan")) {
    Serial.println("MDNS responder started");
  }



  server.on("/", [](AsyncWebServerRequest * request)
  { 
  request->send_P(200, "text/html", webpage);
  });
  
  server.on("/turnon", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    liftServo1.write(100)
    liftServo2.write(100)
    liftServo3.write(100)
    liftServo4.write(100)
    liftServo5.write(100)
    liftServo6.write(100)
  request->redirect("http://swan.local/");
  });

  server.on("/turndown", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    liftServo1.write(10)
    liftServo2.write(10)
    liftServo3.write(10)
    liftServo4.write(10)
    liftServo5.write(10)
    liftServo6.write(10)
  request->redirect("http://swan.local/");
  });

  server.on("/spinright", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    spinServo1.write(100)
    spinServo2.write(100)
    spinServo3.write(100)
    spinServo4.write(100)
    spinServo5.write(100)
    spinServo6.write(100)
  request->redirect("http://swan.local/");
  });

  server.on("/spinleft", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    spinServo1.write(10)
    spinServo2.write(10)
    spinServo3.write(10)
    spinServo4.write(10)
    spinServo5.write(10)
    spinServo6.write(10)
  request->redirect("http://swan.local/");
  });

  server.onNotFound(notFound);

  server.begin();
}


void loop(void)
{
}
