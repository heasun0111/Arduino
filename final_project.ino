
#include <Servo.h>
#include "pitches.h" // 계이름이 정의된 헤더 파일 삽입

// 초음파 센서 핀 선언
#define trigPin 7
#define echoPin 12

Servo sL;
Servo sR;

const int SPEAKER = 3; // 3번 핀을 사용하는 SPEAKER 상수 정의

int led_Y = 4; 

// 적외선 센서
int sensorM = A0; 
int sensorLL = A1; // 가장 왼쪽(가운데 라인을 기준으로 왼쪽 90도 라인)
int sensorL = A2; 
int sensorF = A3; // 중앙(가운데 라인 확인)
int sensorR = A4;
int sensorRR = A5; // 가장 오른쪽(가운데 라인을 기준으로 오른쪽 90도 라인)

int flag; // 어느 방향으로 회전하는 지를 결정

int countOb = 0; // 장애물을 밀어내는 횟수

void setup() {
  pinMode(sensorLL, INPUT);
  pinMode(sensorL, INPUT);
  pinMode(sensorR, INPUT);
  pinMode(sensorRR, INPUT);
  pinMode(sensorF, INPUT);
  sL.attach(10);
  sR.attach(13);

  pinMode(led_Y, OUTPUT);
}
// 전진
void motor(Servo sL, Servo sR, int rpm) {
  sL.writeMicroseconds(1500 + rpm);
  sR.writeMicroseconds(1500 - rpm);
}

// 전진 시에 딜레이
void motor_d(Servo sL, Servo sR, int rpm, int t) {
  sL.writeMicroseconds(1500 + rpm);
  sR.writeMicroseconds(1500 - rpm);
  delay(t);
}
// 회전(라인을 잘 따라가기 위한)
void turn(int flag, Servo sL, Servo sR, int rpm) {
  
  // flag가 2의 배수이면 오른쪽으로 회전
    if ((flag % 2) == 0) {
    sL.writeMicroseconds(1500 + rpm);
    sR.writeMicroseconds(1500 + rpm);
  } // flag가 2의 배수가 아니면 왼쪽으로 회전
  else {
    sL.writeMicroseconds(1500 - rpm);
    sR.writeMicroseconds(1500 - rpm);
  }
}

// 회전(stateLL이 감지될 때까지)
void turn_(int flag, Servo sL, Servo sR, int rpm){
  
  // flag가 2의 배수이면 좌회전
  if ((flag % 2) == 0) {
    while(1) {
      int stateLL = digitalRead(sensorLL);
      sL.writeMicroseconds(1500 - rpm);
      sR.writeMicroseconds(1500 - rpm);
      // 좌회전하다가 stateLL이 인식되면 멈춤
      if (stateLL) break;
    }
    sL.writeMicroseconds(1500 - rpm);
    sR.writeMicroseconds(1500 - rpm);
    delay(300);
  }
  
  // flag가 2의 배수가 아니면 우회전
  else {
    while(1) {
      int stateRR = digitalRead(sensorRR);
      sL.writeMicroseconds(1500 + rpm);
      sR.writeMicroseconds(1500 + rpm);
      
      // 우회전하다가 stateRR이 인식되면 멈춤
      if (stateRR) break;
    }
    sL.writeMicroseconds(1500 + rpm);
    sR.writeMicroseconds(1500 + rpm);
    delay(300);
  }
}



void loop() {
 
}
