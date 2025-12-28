# NCKU RC1 - CK07 Style Dual-Motor RC Car

這是 **2025 新生專題 RC1 組** 的韌體控制專案。
使用 **ESP32** 與 **Xbox 控制器**，實現雙馬達後輪驅動與電子差速轉向。

## 硬體
* **MCU**: NodeMCU-32S (ESP32)
* **Controller**: Xbox Series Controller (via Bluetooth)
* **Driver**: DRV8833 Dual Motor Driver
* **Motors**: JGA25-370 (12V) x2
* **Power**: 2S 18650 Li-ion Battery (7.4V)

已完成的項目：
- 搖桿訊號處理
  - 死區過濾：已實作（src/joystick.cpp）
  - 數值映射：已實作，輸出範圍 -255..255（src/joystick.cpp）
  - 油門曲線：已加入指數曲線（可透過 THROTTLE_EXPONENT 在 include/config.h 調整）

- 電子差速
  - 混控算法：已實作（src/diff_drive.cpp），使用 Ackermann-like 比率
  - 原地迴旋：已實作（spin-in-place，當 throttle 很小且 steer 非零時啟動）


### 接線圖

| 裝置 | 腳位名稱 | ESP32 GPIO |
| :--- | :--- | :--- |
| **左輪馬達** | L_IN1 | `GPIO 26` |
| | L_IN2 | `GPIO 27` |
| **右輪馬達** | R_IN3 | `GPIO 14` |
| | R_IN4 | `GPIO 12` |
| **轉向伺服** | Signal | `GPIO 13` |

---

## 安裝指南

A. 設定 ESP32 開發板
1. 進入Arduino IDE 左側選單的 **Boards Manager**。
2. 搜尋關鍵字 `esp32` (by Espressif Systems)。
3. 點選版本下拉選單，選擇 **`2.0.17`**。
4. 點擊 **Install** 或 **Update**。
   *(若已安裝 3.0.x 版，請務必執行此降級動作)*

B. 安裝 Library
1. **XboxSeriesXControllerESP32_asukiaaa** (by asukiaaa)
2. **ESP32Servo** (by Kevin Harrington / Madamaria)

C. 燒錄
1.  前往本專案的 **[Releases 頁面]** ("https://github.com/Maple241/NCKU-RC1-ESP32-Firmware/releases/tag/v1.0.0")。
2.  下載 `RC1.7z`。
3.  解壓縮後，直接開啟 `RC1.ino`。
4.  設定開發板為 `NodeMCU-32S`，選擇 Port 並上傳。

*Developed by Team RC1*
