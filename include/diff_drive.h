#ifndef DIFF_DRIVE_H
#define DIFF_DRIVE_H

#include <Arduino.h>

#define WHEEL_BASE 20.0   // 軸距 (L)
#define TRACK_WIDTH 15.0  // 輪距 (W)

extern int resultLeftPWM;
extern int resultRightPWM;

/**
* Calculate electronic differential
* Throttle: Throttle input (0 ~ 255)
* SteerAngle: Steering angle (e.g., -35 ~ 35, positive value for right turn)
*/
void calculateDiffDrive(int throttle, int steerAngle);

#endif
