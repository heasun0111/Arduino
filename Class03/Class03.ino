#include <Servo.h>
#define trigPin 8
#define echoPin 9 
Servo servoLeft;
Servo servoRight;
int soundSensor=A0;
int threshold=1000 ;

void setup() {
  
  servoLeft.attach(10);
  servoRight.attach(13);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
  //처음 소리 감지 후 출발
  while(1){
    if(analogRead(soundSensor)>=threshold) break;
  }
}
//초음파 거리 cm로 변환
long microsecondsToCentimeters(long microseconds){
  return microseconds*0.034/2;
}

void loop() {   
  while(1){
    //직진
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1300);
    
    //초음파 발생
    long duration,cm;
    digitalWrite(trigPin,LOW);
    digitalWrite(echoPin,LOW);
    delayMicroseconds(1000);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigPin,LOW);
  
    duration=pulseIn(echoPin,HIGH);
    cm=microsecondsToCentimeters(duration);

    //장애물을 감지했을떄
    if(cm<10){
      //잠시 정지
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
      delay(500);
      //U턴
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1700);
      delay(11750);
      //잠시 정지
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
      delay(500);
    }
  }
}
