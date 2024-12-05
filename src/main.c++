#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

AsyncWebServer server(80);
Servo servo1;
int servo1Pin = 12;

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

  WiFi.softAP("teste", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("ESP")) {
    Serial.println("MDNS responder started");
  }



  server.on("/", [](AsyncWebServerRequest * request)
  { 
  request->send_P(200, "text/html", webpage);
  });
  
  server.on("/servo90/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
   servo1.write(90);
  request->redirect("http://esp.local/");
  });

  server.on("/servo180/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
   servo1.write(180);
  request->redirect("http://esp.local/");
  });

  server.on("/servo/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
   servo1.write(0);
  request->redirect("http://esp.local/");
  });

  server.onNotFound(notFound);

  server.begin();
}


void loop(void)
{
}
