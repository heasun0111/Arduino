
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

// 모든 적외선 센서가 감지 안 될 때까지 전진
void go(Servo sL, Servo sR) {
  while(1) {
    int stateL = digitalRead(sensorL);
    int stateR = digitalRead(sensorR);
    int stateLL = digitalRead(sensorLL);
    int stateRR = digitalRead(sensorRR);
    int stateF = digitalRead(sensorF);
    int stateM = analogRead(sensorM);

    int x=0;
    
    // 기기를 오른쪽 방향으로 가는 지 위쪽 방향으로 가는 지 확인
    if (stateLL) flag = 1; // 오른쪽 방향
    if (stateRR) flag = 2; // 왼쪽 방향
    if (stateM < 100){
      digitalWrite(led_Y, HIGH);
      x=1;
    } else {
      digitalWrite(led_Y, LOW);
      x=0;
    }
    
    if (stateF) motor(sL, sR, 50); // stateF가 감지되면 앞으로 전진
    
    // stateF가 감지가 안 되었을 경우
    else if (stateL) { // stateL이 감지되면 왼쪽으로 회전
      turn(1, sL, sR, 100);  
       
    } else if (stateR) { // stateR이 감지되면 오른쪽 회전
      turn(2, sL, sR, 100);
    }
    
    // 적외선 센서 전체가 감지가 안 되면 빠져나옴
    if (!stateLL && !stateRR && !stateL && !stateF && !stateR){
      if(x==1) countOb++;
      if(countOb==3) {
        while(1) motor(sL,sR,0);
      }
      break;
    }
  }
  motor_d(sL, sR, 50, 400);
}
// 왼쪽으로 회전하기 위해서 전진하는 함수
void goL(Servo sL, Servo sR) {
  while(1) {
    int stateL = digitalRead(sensorL);
    int stateR = digitalRead(sensorR);
    int stateLL = digitalRead(sensorLL);
    int stateRR = digitalRead(sensorRR);
    int stateF = digitalRead(sensorF);
    int stateM = analogRead(sensorM);

    if (stateM < 100) {
      digitalWrite(led_Y, HIGH);
    } else {
      digitalWrite(led_Y, LOW);
      
    }
    
    if (stateF) motor(sL, sR, 50);
    
    // 움직이는 도중 라인 밖으로 나갈 경우
    else if(stateL) {
      turn(1, sL, sR, 30);  
    } else if(stateR) {
      turn(2, sL, sR, 30);
    }
    
    // 1칸 갔을 때 멈춤
    if (stateF && stateL && stateLL) break;
  }
  motor_d(sL, sR, 50, 400);
}



void loop() {
 
}
