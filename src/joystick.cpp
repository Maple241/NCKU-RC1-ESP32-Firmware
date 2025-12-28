#include "joystick.h"
#include "config.h"
#include <math.h>

/**
 * processJoystickValue:
 * - rawInput: -512 .. 512
 * - returns: signed PWM -PWM_MAX .. PWM_MAX
 *
 * Behavior:
 * - deadzone filtering
 * - normalize to 0..1 magnitude
 * - apply exponent curve (configurable via THROTTLE_EXPONENT)
 * - map back to PWM range and preserve sign
 */
int processJoystickValue(int rawInput) {
  if (abs(rawInput) < DEADZONE) {
    return 0;
  }

  float sign = (rawInput >= 0) ? 1.0f : -1.0f;
  int magRaw = abs(rawInput);

  // Normalize magnitude to 0..1 taking joystick max into account
  float normalized = (float)(magRaw - DEADZONE) / (float)(JOYSTICK_MAX - DEADZONE);
  if (normalized < 0.0f) normalized = 0.0f;
  if (normalized > 1.0f) normalized = 1.0f;

  // Apply exponential throttle curve for smoother low-end control
  float curved = powf(normalized, THROTTLE_EXPONENT);

  int pwm = (int)(curved * PWM_MAX + 0.5f);
  if (pwm > PWM_MAX) pwm = PWM_MAX;

  return (int)(sign * pwm);
}
