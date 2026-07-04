#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_HOTSPOT_NAME";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

// Motor pins
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33

bool b = false;
bool l = false;
bool r = false;

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Web routes
void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>Robot Car</title>
<style>
body { width:100vw; height:100vh; }
button { width:100%; height:30%; margin:10px; font-size:20px; }
</style>
</head>
<body>
<h2>ESP32 Robot Control</h2>

<button onclick="fetch('/left')">Left</button><br>
<button onclick="fetch('/backward')">Backward</button><br>
<button onclick="fetch('/right')">Right</button><br>

</body>
</html>
)rawliteral");
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotor();

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/backward", [](){ b = true; server.send(200, "text/plain", "OK"); });
  server.on("/left", [](){ l = true; server.send(200, "text/plain", "OK"); });
  server.on("/right", [](){ r = true; server.send(200, "text/plain", "OK"); });

  server.begin();
}

void loop() {
  b = false;
  r = false;
  l = false;

  if (l && r){
    forward();
  } else if (l){
    left();
  } else if (r){
    right()
  } else {
    backward()
  }
  server.handleClient();
}
