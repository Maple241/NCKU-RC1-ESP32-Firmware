#include <Arduino.h>
#include <ESP32Servo.h>

#include "config.h"
#include "bluetooth.h"
#include "joystick.h"
#include "diff_drive.h"

Servo steeringServo;

// Auxiliary function: Controls motor rotation (forward/reverse logic)
// Now accepts signed speed (-255 .. 255)
// ch1/ch2 are LEDC channel IDs mapped to the motor input pins
void setMotorLEDC(int ch1, int ch2, int speedSigned) {
  int duty = abs(speedSigned);
  if (duty > PWM_MAX) duty = PWM_MAX;

  if (duty == 0) {
    ledcWrite(ch1, 0);
    ledcWrite(ch2, 0);
    return;
  }

  if (speedSigned > 0) {
    // forward: PWM on ch1, ch2 = 0
    ledcWrite(ch1, duty);
    ledcWrite(ch2, 0);
  } else {
    // backward: PWM on ch2, ch1 = 0
    ledcWrite(ch1, 0);
    ledcWrite(ch2, duty);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("RC1 Car System Starting...");

  pinMode(PIN_MOTOR_L_IN1, OUTPUT);
  pinMode(PIN_MOTOR_L_IN2, OUTPUT);
  pinMode(PIN_MOTOR_R_IN3, OUTPUT);
  pinMode(PIN_MOTOR_R_IN4, OUTPUT);

  // Initialize LEDC channels and attach to pins
  ledcSetup(LEDC_CH_ML_IN1, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(LEDC_CH_ML_IN2, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(LEDC_CH_MR_IN3, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(LEDC_CH_MR_IN4, PWM_FREQ, PWM_RESOLUTION);

  ledcAttachPin(PIN_MOTOR_L_IN1, LEDC_CH_ML_IN1);
  ledcAttachPin(PIN_MOTOR_L_IN2, LEDC_CH_ML_IN2);
  ledcAttachPin(PIN_MOTOR_R_IN3, LEDC_CH_MR_IN3);
  ledcAttachPin(PIN_MOTOR_R_IN4, LEDC_CH_MR_IN4);

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
    // ensure motors off
    setMotorLEDC(LEDC_CH_ML_IN1, LEDC_CH_ML_IN2, 0);
    setMotorLEDC(LEDC_CH_MR_IN3, LEDC_CH_MR_IN4, 0);
    delay(100);
    return;
  }

  // 3. Reading and Processing Data
  int rawThrottle = getXboxJoyLY(); // Forward positive, backward negative
  int rawSteering = getXboxJoyRX(); // Right positive, left negative
  
  // Processing dead-time logic and throttle curve
  int procThrottle = processJoystickValue(rawThrottle); // signed -255..255
  
  // Steering: map raw steering to servo angle and to steer degrees for diff calc
  // Optionally apply deadzone on steering if desired
  int servoAngle = map(rawSteering, -512, 512, 120, 60); 
  servoAngle = constrain(servoAngle, 60, 120);
  
  int steerDeg = map(rawSteering, -512, 512, -35, 35);
  
  // 4. Calculate electronic differential (now expects signed throttle)
  calculateDiffDrive(procThrottle, steerDeg);

  // 5. Hardware control
  steeringServo.write(servoAngle);

  setMotorLEDC(LEDC_CH_ML_IN1, LEDC_CH_ML_IN2, resultLeftPWM);
  setMotorLEDC(LEDC_CH_MR_IN3, LEDC_CH_MR_IN4, resultRightPWM);

  // Debug (reduced frequency if needed)
  Serial.print("rawT:"); Serial.print(rawThrottle);
  Serial.print(" procT:"); Serial.print(procThrottle);
  Serial.print(" L:"); Serial.print(resultLeftPWM);
  Serial.print(" R:"); Serial.println(resultRightPWM);
  
  delay(10);
}
