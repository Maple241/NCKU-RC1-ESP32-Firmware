#ifndef CONFIG_H
#define CONFIG_H

#define JOYSTICK_MAX 512
#define JOYSTICK_MIN -512
#define DEADZONE 30

#define PWM_MAX 255
#define PWM_MIN 0

// LEDC / PWM 設定 (ESP32)
#define PWM_FREQ 2000          // Hz
#define PWM_RESOLUTION 8       // bits (0..255)
#define LEDC_CH_ML_IN1 0
#define LEDC_CH_ML_IN2 1
#define LEDC_CH_MR_IN3 2
#define LEDC_CH_MR_IN4 3

// Pin definition
// 1. DRV8833 (each motor has two pins)
#define PIN_MOTOR_L_IN1  26 
#define PIN_MOTOR_L_IN2  27
#define PIN_MOTOR_R_IN3  14
#define PIN_MOTOR_R_IN4  12

// 2. Servo
#define PIN_SERVO        13

// Throttle curve (exponent). 1.0 = linear, >1.0 = gentler low-end
#define THROTTLE_EXPONENT 1.6f

#endif
