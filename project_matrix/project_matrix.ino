#include <Servo.h>
#include <string.h>
#define trigPin 7
#define echoPin 8
#define black 700

// 적외선 센서 선언
char infrared_L = A0;
char infrared_M = A1;
char infrared_R = A2;

// 왼쪽/오른쪽 바퀴 선언
Servo servoLeft;
Servo servoRight;

// 적외선 센서 상태 값 선언
int state_L;
int state_M;
int state_R;

// 2차원 배열 선언 및 초기화
int arr[7][7];
int x = 0;
int y = 0;


void setup() {
  memset(arr, 0, sizeof(arr));
  servoLeft.attach(10);
  servoRight.attach(13);
  
  pinMode(infrared_L, INPUT);
  pinMode(infrared_M, INPUT);
  pinMode(infrared_R, INPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// 거리 계산
long microsecondsToCentimeters(long microseconds) {
  return (microseconds / 2) * 0.034;
}

long distance() {
  long duration;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(100);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  long cm = microsecondsToCentimeters(duration);

  return cm;
}

// 오른쪽으로 한 칸 이동 (y가 6일 때 신경)
void move_right(int x, int y) {
   if (y != 6) {
    do {
      int state_L = analogRead(infrared_L);
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
      delay(100);
    } while (state_L < black);
    x += 1;
    arr[x][y] = 1;
   } 
   else {
    do {
      int state_R = analogRead(infrared_R);
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
      delay(100);
    } while (state_R < black);
    x += 1;
    arr[x][y] = 1;    
   }   
}

// 왼쪽으로 이동
void move_left(int x, int y) {
  do {
    int state_L = analogRead(infrared_L);
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1300);
    delay(100);
  } while (state_L < black);
  x -= 1;
  arr[x][y] = 1;  
}

// 위쪽으로 이동 (x가 6일 때 신경)
void move_up(int x, int y) {
  if (x != 6) {
    do {
      int state_R = analogRead(infrared_R);
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
      delay(100);
    } while (state_R < black);
    y += 1;
    arr[x][y] = 1;
  }
  else {
    do {
      int state_L = analogRead(infrared_L);
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
      delay(100);
    } while (state_L < black);
    y += 1;
    arr[x][y] = 1;
  }
}

// 아래쪽으로 이동 (x가 6일 때 신경)
void move_down(int x, int y) {
  if (x != 6) {
    do {
      int state_L = analogRead(infrared_L);
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
      delay(100);
    } while (state_L < black);
    y -= 1;
    arr[x][y] = 1;
  }
  else {
    do {
      int state_R = analogRead(infrared_R);
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
      delay(100);
    } while (state_R < black);
    y -= 1;
    arr[x][y] = 1;
  }
}

// 왼쪽으로 90도 회전
void turn_left(int x, int y) {
  do {
    int state_M = analogRead(infrared_M);
    servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1300);
    delay(100);  
  } while (state_M < black);
}

// 오른쪽으로 90도 회전
void turn_right(int x, int y) {
  do {
    int state_M = analogRead(infrared_M);
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1700);
    delay(100);  
  } while (state_M < black);
}


void loop() {

}
