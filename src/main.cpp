#include <Arduino.h>
#include <ESP32Servo.h>

#include "config.h"
#include "bluetooth.h"
#include "joystick.h"
#include "diff_drive.h"

Servo steeringServo;

// Auxiliary function: Controls motor rotation (forward/reverse logic)
// speed: 0 ~ 255, reverse: true (backward)/false (forward)
void setMotor(int pin1, int pin2, int speed, bool reverse) {
  if (speed == 0) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    return;
  }
  
  if (!reverse) {
    // Forward
    analogWrite(pin1, speed);
    digitalWrite(pin2, LOW);
  } else {
    // Backward
    digitalWrite(pin1, LOW);
    analogWrite(pin2, speed);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("RC1 Car System Starting...");

  pinMode(PIN_MOTOR_L_IN1, OUTPUT);
  pinMode(PIN_MOTOR_L_IN2, OUTPUT);
  pinMode(PIN_MOTOR_R_IN3, OUTPUT);
  pinMode(PIN_MOTOR_R_IN4, OUTPUT);

  // Initialize the servo motor
  ESP32PWM::allocateTimer(0);
  steeringServo.setPeriodHertz(50);
  steeringServo.attach(PIN_SERVO, 500, 2400);
  steeringServo.write(90);
  
  initBluetooth();
}

void loop() {
  // 1. Update Bluetooth data
  updateBluetooth();

 // 2. Safety check: If there is no connection, stop the vehicle
  if (!isControllerConnected()) {
    setMotor(PIN_MOTOR_L_IN1, PIN_MOTOR_L_IN2, 0, false);
    setMotor(PIN_MOTOR_R_IN3, PIN_MOTOR_R_IN4, 0, false);
    return;
  }

  // 3. Reading and Processing Data
  int rawThrottle = getXboxJoyLY(); // Forward is positive, backward is negative
  int rawSteering = getXboxJoyRX(); // // Turn right is positive, turn left is negative
  
  // Processing dead-time logic
  int procThrottle = processJoystickValue(rawThrottle); 
  
  // Steering angle mapping (Servo 60~120 degrees, midpoint 90 degrees)
  // rawSteering (-512~512) -> Servo Angle (120~60)
  int servoAngle = map(rawSteering, -512, 512, 120, 60); 
  // Limiting Angle Protection Mechanism
  servoAngle = constrain(servoAngle, 60, 120);
  
  // 4. Calculate electronic differential
  int absSpeed = abs(procThrottle);
  int steerDeg = map(rawSteering, -512, 512, -35, 35);
  
  calculateDiffDrive(absSpeed, steerDeg);
  
  // 5. Perform hardware control
  // Control Servo
  steeringServo.write(servoAngle);

  // Control the motor (determine whether to move forward or backward)
  bool isReversing = (procThrottle < 0);
  
  setMotor(PIN_MOTOR_L_IN1, PIN_MOTOR_L_IN2, resultLeftPWM, isReversing);
  setMotor(PIN_MOTOR_R_IN3, PIN_MOTOR_R_IN4, resultRightPWM, isReversing);

  // Debug
  Serial.print("Throttle:"); Serial.print(procThrottle);
  Serial.print(" L:"); Serial.print(resultLeftPWM);
  Serial.print(" R:"); Serial.println(resultRightPWM);
  
  delay(10);
}
