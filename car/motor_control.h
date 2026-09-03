// ========================================
// 🚗 RC카 - 모터 제어 헤더파일
// ========================================

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "Arduino.h"

class MotorControl {
  public:
    MotorControl();
    
    // 초기화
    void init();
    
    // 모터 제어 (PWM 0-255)
    void moveForward(uint8_t speed);    // 전진
    void moveBackward(uint8_t speed);   // 후진
    void turnLeft(uint8_t speed);       // 좌회전
    void turnRight(uint8_t speed);      // 우회전
    void stop();                         // 정지
    
    // 개별 모터 제어
    void setLeftMotor(int speed);   // -255 ~ 255 (음수: 역방향)
    void setRightMotor(int speed);  // -255 ~ 255 (음수: 역방향)
    void setMotors(int leftSpeed, int rightSpeed);  // 동시 제어

  private:
    void pwmWrite(int pin1, int pin2, int ena, int speed);
};

#endif
