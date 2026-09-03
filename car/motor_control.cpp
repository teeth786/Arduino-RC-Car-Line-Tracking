// ========================================
// 🚗 RC카 - 모터 제어 구현파일
// ========================================

#include "motor_control.h"
#include "../config/pins_config.h"
#include "../config/config.h"

MotorControl::MotorControl() {}

void MotorControl::init() {
  // 모든 모터 핀을 출력으로 설정
  pinMode(MOTOR_LEFT_IN1, OUTPUT);
  pinMode(MOTOR_LEFT_IN2, OUTPUT);
  pinMode(MOTOR_LEFT_ENA, OUTPUT);
  
  pinMode(MOTOR_RIGHT_IN3, OUTPUT);
  pinMode(MOTOR_RIGHT_IN4, OUTPUT);
  pinMode(MOTOR_RIGHT_ENB, OUTPUT);
  
  // 초기 상태: 정지
  this->stop();
  
  if (DEBUG_MODE) {
    Serial.println("✓ 모터 제어 초기화 완료");
  }
}

void MotorControl::pwmWrite(int pin1, int pin2, int ena, int speed) {
  // speed: -255 ~ 255 (음수: 역방향)
  
  if (speed > 0) {
    // 정방향
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(ena, speed);
  } else if (speed < 0) {
    // 역방향
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(ena, -speed);
  } else {
    // 정지
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    analogWrite(ena, 0);
  }
}

void MotorControl::moveForward(uint8_t speed) {
  this->setMotors(speed, speed);
}

void MotorControl::moveBackward(uint8_t speed) {
  this->setMotors(-speed, -speed);
}

void MotorControl::turnLeft(uint8_t speed) {
  // 좌측 모터 느리게, 우측 모터 빠르게
  this->setMotors(speed / 2, speed);
}

void MotorControl::turnRight(uint8_t speed) {
  // 우측 모터 느리게, 좌측 모터 빠르게
  this->setMotors(speed, speed / 2);
}

void MotorControl::stop() {
  this->setMotors(0, 0);
}

void MotorControl::setLeftMotor(int speed) {
  // speed: -255 ~ 255
  this->pwmWrite(MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_LEFT_ENA, speed);
}

void MotorControl::setRightMotor(int speed) {
  // speed: -255 ~ 255
  this->pwmWrite(MOTOR_RIGHT_IN3, MOTOR_RIGHT_IN4, MOTOR_RIGHT_ENB, speed);
}

void MotorControl::setMotors(int leftSpeed, int rightSpeed) {
  // speed: -255 ~ 255
  this->setLeftMotor(leftSpeed);
  this->setRightMotor(rightSpeed);
  
  if (DEBUG_MODE && (leftSpeed != 0 || rightSpeed != 0)) {
    Serial.print("🚗 모터 속도 - 좌: ");
    Serial.print(leftSpeed);
    Serial.print(", 우: ");
    Serial.println(rightSpeed);
  }
}
