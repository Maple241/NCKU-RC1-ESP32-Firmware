#include "diff_drive.h"

int resultLeftPWM = 0;
int resultRightPWM = 0;

void calculateDiffDrive(int throttleSigned, int steerAngle) {
  // throttleSigned: -255 .. 255
  if (throttleSigned == 0 && abs(steerAngle) > 5) {
    // spin in place using steer magnitude
    int spin = map(abs(steerAngle), 0, 35, 0, PWM_MAX);
    if (steerAngle > 0) { // turn right in place -> left forward, right backward
      resultLeftPWM = spin;
      resultRightPWM = -spin;
    } else {
      resultLeftPWM = -spin;
      resultRightPWM = spin;
    }
    return;
  }

  // normal driving: use abs throttle magnitude but keep sign for direction
  float sign = throttleSigned >= 0 ? 1.0f : -1.0f;
  int throttleMag = abs(throttleSigned);

  if (abs(steerAngle) < 1) {
    resultLeftPWM = sign * throttleMag;
    resultRightPWM = sign * throttleMag;
    return;
  }

  float thetaRad = radians(abs(steerAngle));
  float R = WHEEL_BASE / tan(thetaRad);
  float innerRatio = 1.0f - (TRACK_WIDTH / (2.0f * R));
  float outerRatio = 1.0f + (TRACK_WIDTH / (2.0f * R));

  int left, right;
  if (steerAngle > 0) {
    left = (int)(throttleMag * outerRatio + 0.5f);
    right = (int)(throttleMag * innerRatio + 0.5f);
  } else {
    left = (int)(throttleMag * innerRatio + 0.5f);
    right = (int)(throttleMag * outerRatio + 0.5f);
  }
  // apply sign for direction
  resultLeftPWM = (int)constrain(sign * left, -PWM_MAX, PWM_MAX);
  resultRightPWM = (int)constrain(sign * right, -PWM_MAX, PWM_MAX);
}
