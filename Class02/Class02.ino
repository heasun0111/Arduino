#define trigPin 7
#define echoPin 8
int led = 13;
 
char infrared = A0;
int state;
 
void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(infrared, INPUT);
  pinMode(led, OUTPUT);
}
 
long microsecondsToCentimeters(long microseconds)
{
  long a = (microseconds / 2) * 0.034;
  return a; 
}
 
void loop() {
  long duration, length;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(100);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
 
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
  long cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.println(" cm");
  delay(500);
  if (cm > 30) {
    int state = analogRead(infrared);
 
    Serial.print("Infrared = ");
    Serial.println(state);
 
    delay(500);
 
    if (state >= 700) {
     digitalWrite(led, HIGH);    
   } else {
     digitalWrite(led, LOW);
   }
  } 
}
