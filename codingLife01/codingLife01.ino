int green = 12;
int yellow = 10;
int red = 8;

void setup() {
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
}

void loop() {
  for(int i=0; i<10; i++){
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
    delay(1000);
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    delay(1000);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    delay(1000);
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
    delay(1000);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    delay(1000);
    digitalWrite(green, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    delay(1000);

  }
  

}
