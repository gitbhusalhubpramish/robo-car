#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_HOTSPOT_NAME";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33

String cmd = "stop";

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

void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>Robot</title>
<style>
button { width:100%; height:25vh; font-size:20px; }
</style>
</head>
<body>

<h2>Robot Control</h2>

<button id="left">LEFT</button>
<button id="right">RIGHT</button>
<button onclick="send('back')">BACK</button>

<script>
let leftPressed = false;
let rightPressed = false;

function update() {
  if (leftPressed && rightPressed) {
    send("forward");
  }
  else if (leftPressed) {
    send("left");
  }
  else if (rightPressed) {
    send("right");
  }
  else {
    send("stop");
  }
}

function send(c) {
  fetch("/cmd?val=" + c);
}

const left = document.getElementById("left");
const right = document.getElementById("right");

// LEFT
left.onmousedown = () => {
  leftPressed = true;
  update();
};

left.onmouseup = left.onmouseleave = () => {
  leftPressed = false;
  update();
};

// RIGHT
right.onmousedown = () => {
  rightPressed = true;
  update();
};

right.onmouseup = right.onmouseleave = () => {
  rightPressed = false;
  update();
};
</script>

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
  while (WiFi.status() != WL_CONNECTED) delay(500);

  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.on("/cmd", []() {
    cmd = server.arg("val");

    if (cmd == "forward") forward();
    else if (cmd == "back") backward();
    else if (cmd == "left") left();
    else if (cmd == "right") right();
    else stopMotor();

    server.send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
