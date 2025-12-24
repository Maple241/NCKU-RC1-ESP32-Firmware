#include "joystick.h"
#include "config.h"

int processJoystickValue(int rawInput) {
  if (abs(rawInput) < DEADZONE) {
    return 0; 
  }

  int outputPWM = 0;
  
  if (rawInput > 0) {
    outputPWM = map(rawInput, DEADZONE, JOYSTICK_MAX, PWM_MIN, PWM_MAX);
  } else {
    outputPWM = map(rawInput, -DEADZONE, JOYSTICK_MIN, -PWM_MIN, -PWM_MAX);
  }

  // Clamping
  if (outputPWM > 255) outputPWM = 255;
  if (outputPWM < -255) outputPWM = -255;

  return outputPWM;
}
