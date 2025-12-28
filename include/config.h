#ifndef CONFIG_H
#define CONFIG_H

#define JOYSTICK_MAX 512
#define JOYSTICK_MIN -512
#define DEADZONE 30
#define PWM_MAX 255
#define PWM_MIN 0

// Pin defidition
// 1. DRV8833
// Left rear wheel
#define PIN_MOTOR_L_IN1  26 
#define PIN_MOTOR_L_IN2  27
// Right rear wheel
#define PIN_MOTOR_R_IN3  14
#define PIN_MOTOR_R_IN4  12

// 2. Servo
#define PIN_SERVO        13

#endif
