#include <Arduino.h>
#include "config.h"
#include "joystick.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  // test
  int rawY = 100;

  int motorPWM = processJoystickValue(rawY);

  Serial.print("PWM: ");
  Serial.println(motorPWM);
  
  delay(100);
}
