#include "diff_drive.h"
#include "config.h"
#include <math.h>

int resultLeftPWM = 0;   // signed: -255 .. 255
int resultRightPWM = 0;  // signed

void calculateDiffDrive(int throttleSigned, int steerAngle) {
  // throttleSigned: -PWM_MAX .. PWM_MAX
  // steerAngle: -35 .. 35 (positive = right turn)

  // If throttle is very small (we want to rotate in place), enable spin-in-place:
  const int SPIN_THRESHOLD = 5; // throttle magnitude below which spin-in-place may be allowed
  int throttleMag = abs(throttleSigned);

  if (throttleMag <= SPIN_THRESHOLD && abs(steerAngle) > 5) {
    // spin-in-place: left and right have opposite signs
    int spin = map(abs(steerAngle), 0, 35, 0, PWM_MAX);
    if (steerAngle > 0) {
      // turn right in place: left forward, right backward
      resultLeftPWM = spin;
      resultRightPWM = -spin;
    } else {
      // turn left in place
      resultLeftPWM = -spin;
      resultRightPWM = spin;
    }
    return;
  }

  // Normal differential drive (w/ ackermann-like ratio)
  float sign = (throttleSigned >= 0) ? 1.0f : -1.0f;

  if (abs(steerAngle) < 1) {
    // Straight
    resultLeftPWM = (int)(sign * throttleMag);
    resultRightPWM = (int)(sign * throttleMag);
    return;
  }

  // Compute ackermann ratio safely: avoid tan(0)
  float thetaRad = radians((float)abs(steerAngle));
  float R = WHEEL_BASE / tan(thetaRad);

  float innerRatio = 1.0f - (TRACK_WIDTH / (2.0f * R));
  float outerRatio = 1.0f + (TRACK_WIDTH / (2.0f * R));

  // ratio can go below zero for extreme geometry; clamp to small positive
  if (innerRatio < 0.0f) innerRatio = 0.0f;

  int leftMag, rightMag;
  if (steerAngle > 0) {
    // right turn: left is outer, right is inner
    leftMag = (int)(throttleMag * outerRatio + 0.5f);
    rightMag = (int)(throttleMag * innerRatio + 0.5f);
  } else {
    leftMag = (int)(throttleMag * innerRatio + 0.5f);
    rightMag = (int)(throttleMag * outerRatio + 0.5f);
  }

  // clamp magnitudes
  if (leftMag > PWM_MAX) leftMag = PWM_MAX;
  if (rightMag > PWM_MAX) rightMag = PWM_MAX;

  resultLeftPWM = (int)constrain((int)(sign * leftMag), -PWM_MAX, PWM_MAX);
  resultRightPWM = (int)constrain((int)(sign * rightMag), -PWM_MAX, PWM_MAX);
}
