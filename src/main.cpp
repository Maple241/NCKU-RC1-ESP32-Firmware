#include <Arduino.h>
#include "config.h"
#include "joystick.h"
#include "bluetooth.h"

void setup() {
  Serial.begin(115200);
  initBluetooth();
}

void loop() {
  updateBluetooth();
  if (isControllerConnected()) {
    // Get the raw data from the Bluetooth connection.
    int rawLx = getXboxJoyLX();
    int rawLy = getXboxJoyLY();

    // Dead zone logic judgment
    int motorInputX = processJoystickValue(rawLx);
    int motorInputY = processJoystickValue(rawLy);

    // int leftPWM, rightPWM;
    // calculateDiffDrive(motorInputY, motorInputX, leftPWM, rightPWM);

    // Test: Print out the processed values
    Serial.print("Raw:"); Serial.print(rawLy);
    Serial.print(" -> Processed:"); Serial.println(motorInputY);
  }
  delay(10);
}
