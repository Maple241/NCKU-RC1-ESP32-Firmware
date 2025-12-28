#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

// Initialize the controller core
extern XboxSeriesXControllerESP32_asukiaaa::Core xboxController;

void initBluetooth();
void updateBluetooth();
bool isControllerConnected();

// Data acquisition function (-512 ~ 512)
int getXboxJoyLX(); // Left stick X
int getXboxJoyLY(); // Left stick Y
int getXboxJoyRX(); // Right stick X
int getXboxJoyRY(); // Right stick Y

// Function to check if the joystick has been pressed
int getBtnA();
int getBtnB();


#endif
