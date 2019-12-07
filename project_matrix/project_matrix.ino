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


//장애물 인지
void detect_hurdle(int x, int y){
  long duration, length;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  long cm = microsecondsToCentimeters(duration);
  delay(500);
  
  if (cm < 10)   //if문 안에 들어갈 조건은 한 칸의 간격으로 조정한다.
  {
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    if (오른쪽 이동){
      arr[x+1][y] = 2;
    }
    if (왼쪽 이동){
      arr[x-1][y] = 2;
    }
    if (위쪽 이동){
      arr[x][y+1] = 2;
    }
    if (아래쪽 이동){
      arr[x][y-1] = 2;
    }
  }
  
}

//Goal 인지
void detect_Goal(int x, int y){
  if ( state_M < black && state_L >= black && state_R >= black)
  {
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    
    if (오른쪽 이동){
      arr[x+1][y] = 3;
    }
    if (왼쪽 이동){
      arr[x-1][y] = 3;
    }
    //Goal의 경우 문제 조건에 의해서 위,아래로 움직일 때 만날 일이 없다.
  }
  
}

//장애물,Goal을 인지한 후 장애물을 돌아가는 함수
void avoid_obstacle (int x, int y){
  
}

void loop() {

}
