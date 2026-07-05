#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Left Motor
#define ENA 14
#define IN1 27
#define IN2 26

// Right Motor
#define ENB 12
#define IN3 25
#define IN4 33

int speedValue = 200;

void setup() {

  Serial.begin(115200);

  SerialBT.begin("ESP32_RC_CAR");

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopCar();

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  Serial.println("Bluetooth Started");
}

void loop() {

  if (SerialBT.available()) {

    char cmd = SerialBT.read();

    Serial.println(cmd);

    switch (cmd) {

      case 'F':
        forward();
        break;

      case 'B':
        backward();
        break;

      case 'L':
        left();
        break;

      case 'R':
        right();
        break;

      case 'G':
        forwardLeft();
        break;

      case 'I':
        forwardRight();
        break;

      case 'H':
        backwardLeft();
        break;

      case 'J':
        backwardRight();
        break;

      case 'S':
        stopCar();
        break;

      // Speed (0-9)
      case '0': setSpeed(0); break;
      case '1': setSpeed(70); break;
      case '2': setSpeed(90); break;
      case '3': setSpeed(110); break;
      case '4': setSpeed(130); break;
      case '5': setSpeed(150); break;
      case '6': setSpeed(170); break;
      case '7': setSpeed(190); break;
      case '8': setSpeed(220); break;
      case '9': setSpeed(255); break;

      case 'q':
        setSpeed(255);
        break;
    }
  }
}

void setSpeed(int s) {
  speedValue = s;
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
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

void forwardLeft() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void forwardRight() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void backwardLeft() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backwardRight() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopCar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
