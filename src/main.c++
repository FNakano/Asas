#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

#define NUM_SERVOS 6

const int liftServoPins[] = {13, 12, 14, 27, 26, 25};
const int spinServoPins[] = {15, 2, 4, 5, 19, 21};

Servo liftServos[NUM_SERVOS];
Servo spinServos[NUM_SERVOS];

AsyncWebServer server(80);

const char* webpage = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>Servo Controls</h1>
<button onclick="window.location = 'http://swan.local/turnon'">Lift Up</button>
<button onclick="window.location = 'http://swan.local/turndown'">Lift Down</button><br><br>
<button onclick="window.location = 'http://swan.local/spinright'">Spin Right</button>
<button onclick="window.location = 'http://swan.local/spinleft'">Spin Left</button>
<button onclick="window.location = 'http://swan.local/off'">Stop</button>
</center>
</body>
</html>
)=====";


void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Page Not Found");
}

void setServoPositions(Servo servos[], int numServos, int position) {
  for (int i = 0; i < numServos; i++) {
    if (servos[i].attached()) { 
      servos[i].write(position);
      delay(500);
    } else {
      Serial.printf("Servo %d não está anexado!\n", i);
    }
  }
}


void setup() {
  Serial.begin(115200);

  for (int i = 0; i < NUM_SERVOS; i++) {
    liftServos[i].attach(liftServoPins[i]);
    spinServos[i].attach(spinServoPins[i]);
  }

  WiFi.softAP("swan dress", "");
  Serial.print("SoftAP IP address: ");
  Serial.println(WiFi.softAPIP());

  if (MDNS.begin("swan")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", webpage);
  });

  server.on("/turnon", HTTP_GET, [](AsyncWebServerRequest *request){
    setServoPositions(liftServos, NUM_SERVOS, 100);
    request->redirect("http://swan.local/");
  });

  server.on("/turndown", HTTP_GET, [](AsyncWebServerRequest *request){
    setServoPositions(liftServos, NUM_SERVOS, 10);
    request->redirect("http://swan.local/");
  });

  server.on("/spinright", HTTP_GET, [](AsyncWebServerRequest *request){
    setServoPositions(spinServos, NUM_SERVOS, 100);
    request->redirect("http://swan.local/");
  });

  server.on("/spinleft", HTTP_GET, [](AsyncWebServerRequest *request){
    setServoPositions(spinServos, NUM_SERVOS, 10);
    request->redirect("http://swan.local/");
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    setServoPositions(liftServos, NUM_SERVOS, 0);
    setServoPositions(spinServos, NUM_SERVOS, 0);
    request->redirect("http://swan.local/");
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {}
