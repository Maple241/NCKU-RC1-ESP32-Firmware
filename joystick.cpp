// 搖桿參數設定
const int JOYSTICK_MAX = 512;
const int JOYSTICK_MIN = -512;
const int DEADZONE = 30;

// 馬達 PWM 參數
const int PWM_MAX = 255;       // ESP32 PWM 最大佔空比
const int PWM_MIN = 0;         // 停止

/*
 * 處理搖桿數值：死區過濾 + 數值映射
 * @param rawInput: 搖桿原始讀數 (例如 -512 ~ 512)
 * @return int: 轉換後的 PWM 值 (-255 ~ 255)
*/
 
int processJoystickValue(int rawInput) {
	// 如果絕對值小於死區，視為靜止
	if (abs(rawInput) < DEADZONE) {
		return 0; 
	}
	
	int outputPWM = 0;
	
	// 正向 (前進/右轉)
	if (rawInput > 0) {
		// 注意：fromLow 是 DEADZONE，這樣剛推搖桿時會從 0 開始慢慢加速
		outputPWM = map(rawInput, DEADZONE, JOYSTICK_MAX, PWM_MIN, PWM_MAX);    // map(value, fromLow, fromHigh, toLow, toHigh)
	} 
	else {
		// 負向 (後退/左轉)
		outputPWM = map(rawInput, -DEADZONE, JOYSTICK_MIN, -PWM_MIN, -PWM_MAX);
	}
	
	// 4. 防止計算溢位導致 PWM 超過 255 或低於 -255
	if (outputPWM > 255) outputPWM = 255;
	if (outputPWM < -255) outputPWM = -255;
	
	return outputPWM;

}
