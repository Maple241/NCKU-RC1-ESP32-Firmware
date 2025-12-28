#ifndef DIFF_DRIVE_H
#define DIFF_DRIVE_H

#include <Arduino.h>

#define WHEEL_BASE 20.0   // 軸距 (L)
#define TRACK_WIDTH 15.0  // 輪距 (W)

extern int resultLeftPWM;
extern int resultRightPWM;

/**
 * 計算電子差速
 * throttle: 油門輸入 (0 ~ 255)
 * steerAngle: 轉向角度 (例如 -35 ~ 35，正值為右轉)
 */
void calculateDiffDrive(int throttle, int steerAngle);

#endif
