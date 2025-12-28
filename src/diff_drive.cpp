#include "diff_drive.h"

int resultLeftPWM = 0;
int resultRightPWM = 0;

void calculateDiffDrive(int throttle, int steerAngle) {
  // 1. Straight-line driving (dead zone handling)
  if (abs(steerAngle) < 1) {
    resultLeftPWM = throttle;
    resultRightPWM = throttle;
    return;
  }

  // 2. Ackermann geometry calculations
  // Convert to radians
  float thetaRad = radians(abs(steerAngle));
  float R = WHEEL_BASE / tan(thetaRad);

  float innerRatio = 1.0 - (TRACK_WIDTH / (2.0 * R));
  float outerRatio = 1.0 + (TRACK_WIDTH / (2.0 * R));

  // 3. Determine the steering direction and distribute power
  // Assumption: steerAngle > 0 indicates a right turn
  if (steerAngle > 0) {
    // Turn right: Left wheel is the outside (acceleration), right wheel is the inside (deceleration)
    resultLeftPWM = throttle * outerRatio;
    resultRightPWM = throttle * innerRatio;
  } 
  else {
    // Turn left: Left wheel is on the inside (decelerates), right wheel is on the outside (accelerates)
    resultLeftPWM = throttle * innerRatio;
    resultRightPWM = throttle * outerRatio;
  }

  // 4. Security Restrictions
  resultLeftPWM = constrain(resultLeftPWM, 0, 255);
  resultRightPWM = constrain(resultRightPWM, 0, 255);
}
