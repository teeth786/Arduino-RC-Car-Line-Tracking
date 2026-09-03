// ========================================
// 🚗 RC카 - 장애물 감지 헤더파일
// ========================================

#ifndef OBSTACLE_DETECTION_H
#define OBSTACLE_DETECTION_H

#include "Arduino.h"

class ObstacleDetection {
  public:
    ObstacleDetection();
    
    // 초기화
    void init();
    
    // 거리 측정
    int measureDistance();  // 거리 반환 (cm)
    
    // 장애물 감지
    bool isObstacleDetected();  // 장애물 있는지 확인
    void handleObstacle();      // 장애물 회피 로직
    
  private:
    unsigned long lastCheckTime;  // 마지막 체크 시간
    int lastDistance;             // 마지막 측정 거리
};

#endif
