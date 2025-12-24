# 🏎️ NCKU RC1 - CK07 Style Dual-Motor RC Car

這原本是 **2025 新生專題 RC1 組** 的韌體控制專案。
目標是使用 **ESP32** 與 **Xbox 控制器**，實現雙馬達後輪驅動與電子差速轉向。

## 🛠️ 硬體架構
* **MCU**: NodeMCU-32S (ESP32)
* **Controller**: Xbox Series Controller (via Bluetooth)
* **Driver**: DRV8833 Dual Motor Driver
* **Motors**: JGA25-370 (12V) x2
* **Power**: 2S 18650 Li-ion Battery (7.4V)

## ⚡ 軟體功能 (Current Progress)

### 1. 搖桿訊號處理 (Joystick Processing)
- [x] **死區過濾 (Deadzone)**: 消除搖桿回中時的雜訊飄移。
- [x] **數值映射 (Mapping)**: 將 Raw Data (-512~512) 轉換為 PWM (-255~255)。
- [ ] **油門曲線**: 預計加入指數曲線讓起步更平順。

### 2. 電子差速 (Electronic Differential)
- [ ] **混控算法**: 根據轉向角度調整左右輪速差。
- [ ] **原地迴旋**: 支援雙輪反轉的原地轉向模式。

## 📂 安裝與編譯
本專案使用 **PlatformIO** / **Arduino IDE** 開發。
1. Clone 此專案。
2. 安裝 `Bluepad32` 函式庫。
3. 上傳至 ESP32。

---
*Created by Team RC1 (Member F)*
