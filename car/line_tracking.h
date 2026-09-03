// ========================================
// 🚗 RC카 - 라인 트래킹 헤더파일
// ========================================

#ifndef LINE_TRACKING_H
#define LINE_TRACKING_H

#include "Arduino.h"

class LineTracking {
  public:
    LineTracking();
    
    // 초기화
    void init();
    
    // 라인 감지 및 추적
    void updateSensors();  // 센서값 읽기
    int getLinePosition(); // 라인 위치 반환 (-100 ~ 100)
    
    // PID 제어
    void updatePID();      // PID 계산
    int getPIDOutput();    // PID 출력값 반환
    
    // 라인 추적 수행
    void trackLine(int baseSpeed);  // 기본 속도로 라인 추적
    
  private:
    int sensorValues[5];   // 5개 센서의 아날로그값
    int linePosition;      // 라인 위치 (-100 ~ 100)
    
    // PID 변수
    float pidError;        // 현재 에러
    float pidIntegral;     // 누적 에러
    float pidDerivative;   // 에러 변화율
    float pidOutput;       // PID 계산 결과
    
    int lastError;         // 이전 에러값
};

#endif
