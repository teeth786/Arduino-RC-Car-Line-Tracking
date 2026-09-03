# 무선 조종 RC카 + 라인 트래킹 프로젝트

## 📋 프로젝트 개요

이 프로젝트는 다음 두 가지 기능을 지원하는 아두이노 기반 RC카입니다:

### ✨ 주요 기능

1. **수동 조종 모드** 🎮
   - 손으로 조종기를 조작하여 RC카 제어
   - 오른쪽 회전: 조종기 오른쪽으로 틀기
   - 왼쪽 회전: 조종기 왼쪽으로 틀기
   - 앞으로 이동: 조종기 몸 밖으로 밀기
   - 뒤로 이동: 조종기 몸쪽으로 당기기
   - 회전: 손을 돌리기

2. **자동 라인 트래킹 모드** 🤖
   - 검은 테이프를 따라 자동 주행
   - 장애물 감지 시 회전하여 우회
   - 자동 경로 탐색

3. **모드 전환** 🔄
   - 수동 ↔ 자동 모드 실시간 전환
   - 한 번의 버튼 조작으로 모드 변경

---

## 📦 필요한 부품 목록

### RC카 본체 부품
| 부품 | 수량 | 설명 |
|------|------|------|
| Arduino Mega 2560 | 1개 | 메인 제어보드 (RC카용) |
| DC모터 (3-6V) | 4개 | 바퀴 구동 모터 |
| 모터 드라이버 (L298N) | 2개 | 모터 제어 모듈 |
| nRF24L01 | 1개 | 무선 통신 모듈 |
| IR 센서 (적외선) | 5개 | 검은 라인 감지 |
| 초음파 센서 (HC-SR04) | 1개 | 장애물 감지 |
| 서보모터 (SG90) | 1개 | 초음파 센서 방향 제어 (선택사항) |
| 배터리 팩 (7.4V LiPo) | 1개 | 동력원 |
| 캐스터 휠 | 1개 | 무방향 바퀴 |

### 조종기 부품
| 부품 | 수량 | 설명 |
|------|------|------|
| Arduino Nano | 1개 | 조종기 제어보드 |
| 조이스틱 모듈 | 2개 | 방향 제어 (좌우, 전후) |
| 회전 센서 (자이로) 또는 기울기센서 | 1개 | 손 회전 감지 |
| nRF24L01 | 1개 | 무선 통신 모듈 |
| 푸시 버튼 | 1개 | 모드 전환 버튼 |
| 배터리 팩 (3.7V LiPo) | 1개 | 동력원 |
| 손에 끼우는 반지형 구조 | 1개 | 조종기 홀더 |

### 기타 부품
- 점프 와이어 (50줄)
- PCB 보드 또는 만능 기판
- 납땜 인두 및 납
- USB 케이블
- 열수축 튜브

---

## 🔌 핀 연결 도표

### RC카 (Arduino Mega)

```
모터 드라이버 1 (좌측 바퀴)
─────────────────────────
L298N-IN1 ──→ Mega 핀 8
L298N-IN2 ──→ Mega 핀 9
L298N-ENA ──→ Mega 핀 10 (PWM)

모터 드라이버 2 (우측 바퀴)
─────────────────────────
L298N-IN3 ──→ Mega 핀 11
L298N-IN4 ──→ Mega 핀 12
L298N-ENB ──→ Mega 핀 13 (PWM)

nRF24L01 무선 모듈
─────────────────────────
CE  ──→ Mega 핀 7
CSN ──→ Mega 핀 6
SCK ──→ Mega 핀 52 (SPI)
MOSI ──→ Mega 핀 51 (SPI)
MISO ──→ Mega 핀 50 (SPI)
VCC ──→ 3.3V
GND ──→ GND

IR 센서 (라인 트래킹)
─────────────────────────
센서1 ──→ Mega A0
센서2 ──→ Mega A1
센서3 ──→ Mega A2
센서4 ──→ Mega A3
센서5 ──→ Mega A4
(모두 GND에 연결)

초음파 센서 (HC-SR04)
─────────────────────────
TRIG ──→ Mega 핀 3
ECHO ──→ Mega 핀 4

모드 전환 버튼
─────────────────────────
버튼 핀 ──→ Mega 핀 5
GND ──→ GND
```

### 조종기 (Arduino Nano)

```
조이스틱 1 (좌우 회전)
─────────────────────────
VRx ──→ Nano A0
VRy ──→ Nano A1
SW  ──→ Nano D2

조이스틱 2 (전후 이동)
─────────────────────────
VRx ──→ Nano A2
VRy ──→ Nano A3
SW  ──→ Nano D3

회전 센서 (손 회전 감지) - MPU6050
─────────────────────────
SCL ──→ Nano A5
SDA ──→ Nano A4

nRF24L01 무선 모듈
─────────────────────────
CE  ──→ Nano D7
CSN ──→ Nano D8
SCK ──→ Nano D13 (SPI)
MOSI ──→ Nano D11 (SPI)
MISO ──→ Nano D12 (SPI)
VCC ──→ 3.3V
GND ──→ GND

모드 전환 버튼
─────────────────────────
버튼 핀 ──→ Nano D4
LED (선택) ──→ Nano D5
```

---

## 🔧 필요한 라이브러리

```
- RF24 (nRF24L01 통신)
- Wire (I2C 통신)
- MPU6050 (자이로 센서) - 선택사항
```

Arduino IDE에서 설치:
```
스케치 → 라이브러리 포함하기 → 라이브러리 관리 → 위 라이브러리명 검색 후 설치
```

---

## 📂 파일 구조

```
Arduino-RC-Car-Line-Tracking/
├── README.md (이 파일)
├── docs/
│   ├── CIRCUIT_DIAGRAM.md (회로도 상세설명)
│   ├── ASSEMBLY_GUIDE.md (조립 가이드)
│   └── TROUBLESHOOTING.md (문제해결)
├── car/
│   ├── car_main.ino (RC카 메인 코드)
│   ├── motor_control.cpp
│   ├── motor_control.h
│   ├── line_tracking.cpp
│   ├── line_tracking.h
│   ├── obstacle_detection.cpp
│   ├── obstacle_detection.h
│   ├── wireless_receiver.cpp
│   └── wireless_receiver.h
├── controller/
│   ├── controller_main.ino (조종기 메인 코드)
│   ├── joystick_input.cpp
│   ├── joystick_input.h
│   ├── rotation_sensor.cpp
│   ├── rotation_sensor.h
│   └── wireless_transmitter.cpp
└── config/
    ├── config.h (전체 설정값)
    └── pins_config.h (핀 설정)
```

---

## 📖 사용 방법

1. **조립**: `docs/ASSEMBLY_GUIDE.md` 참조
2. **코드 업로드**:
   - RC카: `car/car_main.ino` → Arduino Mega에 업로드
   - 조종기: `controller/controller_main.ino` → Arduino Nano에 업로드
3. **테스트**: 각 모드를 테스트하고 필요시 튜닝

---

## ⚙️ 작동 원리

### 수동 모드
- 조종기의 조이스틱과 센서 입력 → nRF24L01으로 무선 전송
- RC카가 신호 수신 → 모터 제어로 움직임

### 자동 모드
- IR 센서가 검은 라인 감지
- PID 제어로 라인 추적
- 초음파 센서가 장애물 감지 시 우회 로직 실행

### 모드 전환
- 조종기 버튼 클릭 → 모드 변경 신호 전송
- RC카가 모드 전환 (수동 ↔ 자동)

---

## 🚀 시작하기

```bash
git clone https://github.com/teeth786/Arduino-RC-Car-Line-Tracking.git
cd Arduino-RC-Car-Line-Tracking
```

각 코드 파일을 순서대로 읽고 이해한 후:
1. 부품 연결 (회로도 참조)
2. 라이브러리 설치
3. 각 보드에 코드 업로드
4. 테스트 및 튜닝

---

## 📝 라이선스

MIT License

---

## 🤝 기여

버그 리포트 및 개선 제안은 Issues를 통해 남겨주세요.

---

**마지막 업데이트**: 2026-09-03
**작성자**: teeth786
