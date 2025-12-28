#include "bluetooth.h"

XboxSeriesXControllerESP32_asukiaaa::Core xboxController;

void initBluetooth() {
    Serial.println("NODEMCU-32: Booting Bluetooth...");
    xboxController.begin();
}

void updateBluetooth() {
    xboxController.onLoop();
    static unsigned long lastDebugTime = 0;
    if (millis() - lastDebugTime > 200) {
        if (isControllerConnected()) {
          /*
            Serial.print("\"lx\":"); Serial.print(lx); Serial.print(",");
            Serial.print("\"ly\":"); Serial.print(ly * -1); Serial.print(","); // Flip Y for UI
            Serial.print("\"rx\":"); Serial.print(rx); Serial.print(",");
            Serial.print("\"ry\":"); Serial.print(ry * -1); Serial.print(",");
              
            // Triggers (0-1023)
            Serial.print("\"lt\":"); Serial.print(xboxController.xboxNotif.trigLT / 1); Serial.print(",");
            Serial.print("\"rt\":"); Serial.print(xboxController.xboxNotif.trigRT / 1); Serial.print(",");
              
            // Buttons (bool to 0/1)
            Serial.print("\"a\":"); Serial.print(xboxController.xboxNotif.btnA ? 1 : 0); Serial.print(",");
            Serial.print("\"b\":"); Serial.print(xboxController.xboxNotif.btnB ? 1 : 0); Serial.print(",");
            Serial.print("\"x\":"); Serial.print(xboxController.xboxNotif.btnX ? 1 : 0); Serial.print(",");
            Serial.print("\"y\":"); Serial.print(xboxController.xboxNotif.btnY ? 1 : 0); Serial.print(",");
              
            // Bumpers
            Serial.print("\"lb\":"); Serial.print(xboxController.xboxNotif.btnLB ? 1 : 0); Serial.print(",");
            Serial.print("\"rb\":"); Serial.print(xboxController.xboxNotif.btnRB ? 1 : 0); Serial.print(",");
              
            // System (Updated for latest asukiaaa lib)
            Serial.print("\"view\":"); Serial.print(xboxController.xboxNotif.btnSelect ? 1 : 0); Serial.print(",");
            Serial.print("\"menu\":"); Serial.print(xboxController.xboxNotif.btnStart ? 1 : 0); Serial.print(",");
            Serial.print("\"xbox\":"); Serial.print(xboxController.xboxNotif.btnXbox ? 1 : 0); Serial.print(",");
              
            // Stick Clicks
            Serial.print("\"ls\":"); Serial.print(xboxController.xboxNotif.btnLS ? 1 : 0); Serial.print(",");
            Serial.print("\"rs\":"); Serial.print(xboxController.xboxNotif.btnRS ? 1 : 0); Serial.print(",");
              
            // D-Pad
            Serial.print("\"dup\":"); Serial.print(xboxController.xboxNotif.btnDirUp ? 1 : 0); Serial.print(",");
            Serial.print("\"ddown\":"); Serial.print(xboxController.xboxNotif.btnDirDown ? 1 : 0); Serial.print(",");
            Serial.print("\"dleft\":"); Serial.print(xboxController.xboxNotif.btnDirLeft ? 1 : 0); Serial.print(",");
            Serial.print("\"dright\":"); Serial.print(xboxController.xboxNotif.btnDirRight ? 1 : 0); Serial.print(",");
          */
        } else {
             Serial.println("Waiting for Xbox Controller...");
        }
        lastDebugTime = millis();
    }
}

bool isControllerConnected() {
    return xboxController.isConnected();
}

// Joystick mapping (asukiaaa uses uint16_t 0-65535, centered at 32768)
// We map this to approximately -512..512 for our Web UI

int getXboxJoyLX() {
    if (!isControllerConnected()) return 0;
    return ((int32_t)xboxController.xboxNotif.joyLHori - 32768) / 64;
}

int getXboxJoyLY() {
    if (!isControllerConnected()) return 0;
    return (((int32_t)xboxController.xboxNotif.joyLVert - 32768) / 64) * -1;
}

int getXboxJoyRX() {
    if (!isControllerConnected()) return 0;
    return ((int32_t)xboxController.xboxNotif.joyRHori - 32768) / 64;
}

int getXboxJoyRY() {
    if (!isControllerConnected()) return 0;
    return (((int32_t)xboxController.xboxNotif.joyRVert - 32768) / 64) * -1;
}

// Function to check if the joystick has been pressed
int getBtnA() {
    return xboxController.xboxNotif.btnA ? 1 : 0;
}
int getBtnB() {
    return xboxController.xboxNotif.btnB ? 1 : 0;
}
