
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

void loop() {
 
}
