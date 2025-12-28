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

測試建議：
1. 檢查基礎控制
   - 連上 Xbox 控制器，無 throttle/steer 時左右輪應靜止，servo 在 90 度附近
2. 前進/後退
   - 中等油門前進，左右輪應相同（直線）
   - 反向同樣檢查
3. 差速效果
   - 小幅轉向時左右速度差小；大幅轉向時差大
4. 原地旋轉
   - Throttle 接近 0 且搖桿向右/左，觀察左右輪反向以實現 spin-in-place
5. PWM 驗證
   - 用示波器或 LED 驗證 PIN_MOTOR_* 的 PWM 有 2kHz（或 config 中設定的頻率）且占空比合理

如需我立刻建立 PR（會包含所有 changed files、說明與簡易測試步驟），請回覆「開始 PR」。若需我先微調參數（例如 THROTTLE_EXPONENT、PWM_FREQ 或 SPIN_THRESHOLD），請告訴我要用的數值。
