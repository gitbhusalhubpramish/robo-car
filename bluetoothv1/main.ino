#include <BLEDevice.h>
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
