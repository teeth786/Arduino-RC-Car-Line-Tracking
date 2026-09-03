// ========================================
// 📌 핀 설정 파일 (모든 핀 번호 정��)
// ========================================

#ifndef PINS_CONFIG_H
#define PINS_CONFIG_H

// ========== RC카 (Arduino Mega) 핀 설정 ==========

// --- 모터 드라이버 1 (좌측 바퀴) ---
#define MOTOR_LEFT_IN1   8      // L298N IN1
#define MOTOR_LEFT_IN2   9      // L298N IN2
#define MOTOR_LEFT_ENA   10     // L298N ENA (PWM)

// --- 모터 드라이버 2 (우측 바퀴) ---
#define MOTOR_RIGHT_IN3  11     // L298N IN3
#define MOTOR_RIGHT_IN4  12     // L298N IN4
#define MOTOR_RIGHT_ENB  13     // L298N ENB (PWM)

// --- nRF24L01 무선 모듈 (SPI) ---
#define RF24_CE   7      // 칩 활성화
#define RF24_CSN  6      // 칩 셀렉트

// --- IR 센서 (라인 트래킹) ---
#define IR_SENSOR_1  A0  // 좌측
#define IR_SENSOR_2  A1  // 중앙 좌
#define IR_SENSOR_3  A2  // 중앙
#define IR_SENSOR_4  A3  // 중앙 우
#define IR_SENSOR_5  A4  // 우측

// --- 초음파 센서 (HC-SR04) ---
#define ULTRASONIC_TRIG  3   // TRIG 핀
#define ULTRASONIC_ECHO  4   // ECHO 핀

// --- 모드 전환 버튼 ---
#define MODE_SWITCH_BUTTON  5  // 모드 전환 버튼

// --- 상태 LED (선택사항) ---
#define STATUS_LED_MANUAL   22  // 수동 모드 LED
#define STATUS_LED_AUTO    23   // 자동 모드 LED

// ========== 조종기 (Arduino Nano) 핀 설정 ==========

// --- 조이스틱 1 (좌우 회전) ---
#define JOYSTICK_1_VRx  A0  // X축 (좌우)
#define JOYSTICK_1_VRy  A1  // Y축 (앞뒤) - 사용 안함
#define JOYSTICK_1_SW   D2  // 버튼

// --- 조이스틱 2 (전후 이동) ---
#define JOYSTICK_2_VRx  A2  // X축 (좌우) - 사용 안함
#define JOYSTICK_2_VRy  A3  // Y축 (앞뒤)
#define JOYSTICK_2_SW   D3  // 버튼

// --- 회전 센서 (MPU6050) - I2C 사용 ---
// SCL: Nano A5 (기본)
// SDA: Nano A4 (기본)

// --- nRF24L01 무선 모듈 (SPI) ---
#define RF24_CE_CTRL   D7      // 칩 활성화
#define RF24_CSN_CTRL  D8      // 칩 셀렉트
// SCK:  D13 (기본 SPI)
// MOSI: D11 (기본 SPI)
// MISO: D12 (기본 SPI)

// --- 모드 전환 버튼 ---
#define MODE_SWITCH_BUTTON_CTRL  D4  // 모드 전환 버튼

// --- 상태 LED ---
#define STATUS_LED_CONNECTED    D5   // 연결 상태 LED
#define STATUS_LED_MODE         D6   // 모드 상태 LED

#endif
