// ========================================
// 🚗 RC카 - 라인 트래킹 구현파일
// ========================================

#include "line_tracking.h"
#include "motor_control.h"
#include "../config/pins_config.h"
#include "../config/config.h"

extern MotorControl motors;  // 외부 모터 제어 객체

LineTracking::LineTracking() {
  linePosition = 0;
  pidError = 0;
  pidIntegral = 0;
  pidDerivative = 0;
  pidOutput = 0;
  lastError = 0;
}

void LineTracking::init() {
  // IR 센서 핀을 입력으로 설정
  pinMode(IR_SENSOR_1, INPUT);
  pinMode(IR_SENSOR_2, INPUT);
  pinMode(IR_SENSOR_3, INPUT);
  pinMode(IR_SENSOR_4, INPUT);
  pinMode(IR_SENSOR_5, INPUT);
  
  if (DEBUG_MODE) {
    Serial.println("✓ 라인 트래킹 초기화 완료");
  }
}

void LineTracking::updateSensors() {
  // 모든 IR 센서값 읽기
  sensorValues[0] = analogRead(IR_SENSOR_1);
  sensorValues[1] = analogRead(IR_SENSOR_2);
  sensorValues[2] = analogRead(IR_SENSOR_3);
  sensorValues[3] = analogRead(IR_SENSOR_4);
  sensorValues[4] = analogRead(IR_SENSOR_5);
  
  // 라인 위치 계산 (가중치 합산)
  int weightedSum = 0;
  int totalWeight = 0;
  
  for (int i = 0; i < 5; i++) {
    // 검은색(LOW): 라인 감지, 흰색(HIGH): 라인 없음
    if (sensorValues[i] < LINE_THRESHOLD) {
      // 가중치: -2, -1, 0, 1, 2
      int weight = i - 2;
      weightedSum += weight * sensorValues[i];
      totalWeight += sensorValues[i];
    }
  }
  
  // 라인 위치 정규화 (-100 ~ 100)
  if (totalWeight > 0) {
    linePosition = constrain((weightedSum / totalWeight), -100, 100);
  } else {
    linePosition = 0;  // 라인을 찾지 못함
  }
}

int LineTracking::getLinePosition() {
  return linePosition;
}

void LineTracking::updatePID() {
  // 목표: 중앙(0) 유지
  pidError = -linePosition;  // 음수: 오른쪽에서 라인, 양수: 왼쪽에서 라인
  
  // P 항
  float P = pidError * PID_KP;
  
  // I 항 (누적)
  pidIntegral += pidError;
  pidIntegral = constrain(pidIntegral, -100, 100);  // 누적값 제한
  float I = pidIntegral * PID_KI;
  
  // D 항 (변화율)
  pidDerivative = (pidError - lastError);
  float D = pidDerivative * PID_KD;
  
  // 전체 출력
  pidOutput = P + I + D;
  pidOutput = constrain(pidOutput, -100, 100);  // 출력값 제한
  
  lastError = pidError;
}

int LineTracking::getPIDOutput() {
  return (int)pidOutput;
}

void LineTracking::trackLine(int baseSpeed) {
  // 센서 업데이트
  this->updateSensors();
  
  // PID 계산
  this->updatePID();
  
  // 모터 제어
  int pidOutput = this->getPIDOutput();
  
  int leftSpeed = baseSpeed - pidOutput;
  int rightSpeed = baseSpeed + pidOutput;
  
  // 속도 제한
  leftSpeed = constrain(leftSpeed, 0, MOTOR_MAX_SPEED);
  rightSpeed = constrain(rightSpeed, 0, MOTOR_MAX_SPEED);
  
  motors.setMotors(leftSpeed, rightSpeed);
  
  if (DEBUG_MODE) {
    Serial.print("📍 라인위치: ");
    Serial.print(linePosition);
    Serial.print(" | PID: ");
    Serial.print(pidOutput);
    Serial.print(" | 모터: L=");
    Serial.print(leftSpeed);
    Serial.print(" R=");
    Serial.println(rightSpeed);
  }
}
