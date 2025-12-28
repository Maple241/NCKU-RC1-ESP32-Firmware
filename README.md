# NCKU RC1 - CK07 Style Dual-Motor RC Car

這裡是 **2025 新生專題 RC1 組** 的韌體控制專案。
目標是使用 **ESP32** 與 **Xbox 控制器**，實現雙馬達後輪驅動與電子差速轉向。

## 硬體
* **MCU**: NodeMCU-32S (ESP32)
* **Controller**: Xbox Series Controller (via Bluetooth)
* **Driver**: DRV8833 Dual Motor Driver
* **Motors**: JGA25-370 (12V) x2
* **Power**: 2S 18650 Li-ion Battery (7.4V)

## 軟體

### 1. 搖桿訊號處理
- [x] **死區過濾**: 消除搖桿回中時的雜訊飄移。
- [x] **數值映射**: 將 Raw Data (-512 ~ 512) 轉換為 PWM (-255 ~ 255)。
- [ ] **油門曲線**: 預計加入指數曲線讓起步更平順。

### 2. 電子差速
- [ ] **混控算法**: 根據轉向角度調整左右輪速差。
- [ ] **原地迴旋**: 支援雙輪反轉的原地轉向模式。
