// ========================================
// 🚗 RC카 - 장애물 감지 구현파일
// ========================================

#include "obstacle_detection.h"
#include "motor_control.h"
#include "../config/pins_config.h"
#include "../config/config.h"

extern MotorControl motors;  // 외부 모터 제어 객체

ObstacleDetection::ObstacleDetection() {
  lastCheckTime = 0;
  lastDistance = 0;
}

void ObstacleDetection::init() {
  pinMode(ULTRASONIC_TRIG, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);
  
  if (DEBUG_MODE) {
    Serial.println("✓ 초음파 센서 초기화 완료");
  }
}

int ObstacleDetection::measureDistance() {
  // 초음파 송신
  digitalWrite(ULTRASONIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG, LOW);
  
  // 초음파 수신 (마이크로초 단위)
  unsigned long duration = pulseIn(ULTRASONIC_ECHO, HIGH, 30000);  // 타임아웃 30ms
  
  // 거리 계산 (음속 = 340m/s, 왕복 거리)
  // 거리(cm) = (duration(us) * 340 / 1000000) / 2 * 100
  // 간단히: distance = duration / 58
  int distance = duration / 58;
  
  lastDistance = distance;
  return distance;
}

bool ObstacleDetection::isObstacleDetected() {
  // 일정 시간 간격으로만 측정 (불필요한 반복 방지)
  if (millis() - lastCheckTime < OBSTACLE_CHECK_INTERVAL) {
    return false;
  }
  
  lastCheckTime = millis();
  
  int distance = this->measureDistance();
  
  if (DEBUG_MODE) {
    Serial.print("📏 거리: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  return distance < OBSTACLE_DISTANCE;
}

void ObstacleDetection::handleObstacle() {
  if (DEBUG_MODE) {
    Serial.println("⚠️  장애물 감지! 회피 시작...");
  }
  
  // 1. 멈추기
  motors.stop();
  delay(200);
  
  // 2. 후진
  motors.moveBackward(MOTOR_TURN_SPEED);
  delay(300);
  
  // 3. 오른쪽으로 회전
  motors.turnRight(MOTOR_TURN_SPEED);
  delay(OBSTACLE_TURN_TIME);
  
  motors.stop();
  
  if (DEBUG_MODE) {
    Serial.println("✓ 회피 완료!");
  }
}
