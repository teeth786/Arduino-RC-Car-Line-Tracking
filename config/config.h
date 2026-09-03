// ========================================
// 📌 설정 파일 (모든 설정값 관리)
// ========================================

#ifndef CONFIG_H
#define CONFIG_H

// ========== 모드 설정 ==========
#define MODE_MANUAL    1    // 수동 조종 모드
#define MODE_AUTO      2    // 자동 라인 트래킹 모드
#define CURRENT_MODE   MODE_MANUAL  // 초기 모드

// ========== 무선 통신 설정 (nRF24L01) ==========
#define RF24_CHANNEL   76      // 통신 채널 (0-125)
#define RF24_DATA_RATE RF24_1MBPS  // 1Mbps
#define RF24_PA_LEVEL  RF24_PA_MIN  // 전력 레벨

// ========== 모터 속도 설정 ==========
#define MOTOR_MAX_SPEED    255   // 최대 속도 (0-255)
#define MOTOR_MIN_SPEED    50    // 최소 속도 (정지상태)
#define MOTOR_TURN_SPEED   150   // 회전 시 속도
#define MOTOR_REVERSE_SPEED 200  // 후진 속도

// ========== 라인 트래킹 설정 ==========
#define LINE_THRESHOLD     500   // IR 센서 기준값 (흰색/검은색 판별)
#define PID_KP             0.8   // P 게인
#define PID_KI             0.2   // I 게인
#define PID_KD             0.5   // D 게인
#define LINE_TRACKING_SPEED 180  // 라인 추적 시 기본 속도
#define TURN_CORRECTION    50    // 라인 추적 시 회전 보정값

// ========== 장애물 감지 설정 ==========
#define OBSTACLE_DISTANCE  20    // 장애물 감지 거리 (cm)
#define OBSTACLE_CHECK_INTERVAL 200  // 장애물 체크 간격 (ms)
#define OBSTACLE_TURN_TIME 600   // 장애물 만났을 때 회전 시간 (ms)

// ========== 통신 타임아웃 ==========
#define COMM_TIMEOUT       500   // 통신 타임아웃 (ms)
#define RF24_RETRY_DELAY   500   // 재전송 대기 시간 (ms)

// ========== 디버그 모드 ==========
#define DEBUG_MODE         1     // 1: 활성화, 0: 비활성화
#define SERIAL_BAUD_RATE   9600  // 시리얼 통신 속도

#endif
