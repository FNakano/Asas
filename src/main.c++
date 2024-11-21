#include <WiFi.h>
#include <ESP32Servo.h>

Servo myservo;
const int servoPin = 13;
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";
WiFiServer server(80);

// Função para gerar o HTML
String generateHTML(int servoPosition) {
  String html = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
<style>
body { text-align: center; font-family: "Trebuchet MS", Arial; margin-left:auto; margin-right:auto;}
.slider { width: 300px; }
</style>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
</head>
<body>
<h1>ESP32 with Servo</h1>
<p>Position: <span id="servoPos"></span></p>
<input type="range" min="0" max="180" class="slider" id="servoSlider" onchange="servo(this.value)" value=")(HTML" + String(servoPosition) + R"HTML("/>
<script>
var slider = document.getElementById("servoSlider");
var servoP = document.getElementById("servoPos");
servoP.innerHTML = slider.value;
slider.oninput = function() {
  servoP.innerHTML = this.value;
};
$.ajaxSetup({ timeout: 1000 });
function servo(pos) {
  $.get("/?value=" + pos + "&");
}
</script>
</body>
</html>)HTML";
  return html;
}


void setup() {
  Serial.begin(115200);
  myservo.attach(servoPin);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String request;
    while (client.connected() && client.available()) {
      request += char(client.read());
    }

    int servoPos = 0;
    if (request.indexOf("GET /?value=") >= 0) {
      int pos1 = request.indexOf('=');
      int pos2 = request.indexOf('&');
      if (pos1 >= 0 && pos2 > pos1) {
        servoPos = request.substring(pos1 + 1, pos2).toInt();
        myservo.write(servoPos);
        Serial.println(servoPos);
      }
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type: text/html");
    client.println("Connection: close");
    client.println();
    client.print(generateHTML(servoPos));
    client.println();
    client.stop();
    Serial.println("Client disconnected.");
  }
}