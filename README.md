# NCKU RC1 - CK07 Style Dual-Motor RC Car

這是 **2025 新生專題 RC1 組** 的韌體控制專案。
使用 **ESP32** 與 **Xbox 控制器**，實現雙馬達後輪驅動與電子差速轉向。

## 硬體
* **MCU**: NodeMCU-32S (ESP32)
* **Controller**: Xbox Series Controller (via Bluetooth)
* **Driver**: DRV8833 Dual Motor Driver
* **Motors**: JGA25-370 (12V) x2
* **Power**: 2S 18650 Li-ion Battery (7.4V)

(變更摘要)

已完成的項目：
- 搖桿訊號處理
  - 死區過濾：已實作（src/joystick.cpp）
  - 數值映射：已實作，輸出範圍 -255..255（src/joystick.cpp）
  - 油門曲線：已加入指數曲線（可透過 THROTTLE_EXPONENT 在 include/config.h 調整）

- 電子差速
  - 混控算法：已實作（src/diff_drive.cpp），使用 Ackermann-like 比率
  - 原地迴旋：已實作（spin-in-place，當 throttle 很小且 steer 非零時啟動）

其他重要變更：
- PWM 驅動改為 ESP32 LEDC（穩定 PWM）
- setMotor 已改為 signed speed 介面，並且使用四個 LEDC channel
- 如需調校：THROTTLE_EXPONENT, PWM_FREQ, SPIN_THRESHOLD 可在 include/config.h 中調整
