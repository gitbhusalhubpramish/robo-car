/*#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-cba987654321"

BLECharacteristic *characteristic;

class Callback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *c) {
    String value = c->getValue();

    if (value.length()) {
      char cmd = value[0];

      switch (cmd) {
        case 'F':
          Serial.println("Forward");
          break;

        case 'B':
          Serial.println("Backward");
          break;

        case 'L':
          Serial.println("Left");
          break;

        case 'R':
          Serial.println("Right");
          break;

        case 'S':
          Serial.println("Stop");
          break;
      }
    }
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32 Robot");

  BLEServer *server = BLEDevice::createServer();

  BLEService *service =
      server->createService(SERVICE_UUID);

  characteristic =
      service->createCharacteristic(
          CHARACTERISTIC_UUID,
          BLECharacteristic::PROPERTY_WRITE
      );

  characteristic->setCallbacks(new Callback());

  service->start();

  BLEAdvertising *advertising =
      BLEDevice::getAdvertising();

  advertising->addServiceUUID(SERVICE_UUID);
  advertising->start();

  Serial.println("BLE Ready");
}

void loop() {
}
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-cba987654321"

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

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {

    String value = pCharacteristic->getValue();

    if (value.length() == 0) return;

    switch (value[0]) {
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

      case 'S':
        stopMotor();
        break;
    }
  }
};

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotor();

  BLEDevice::init("ESP32 Robot");

  BLEServer *server = BLEDevice::createServer();

  BLEService *service = server->createService(SERVICE_UUID);

  BLECharacteristic *characteristic = service->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE
  );

  characteristic->setCallbacks(new MyCallbacks());

  service->start();

  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->start();

  Serial.println("BLE Ready");
}

void loop() {}
