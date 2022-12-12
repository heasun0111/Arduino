const int LED4=8;
const int LED3=7;
const int LED1=9;
const int LED2=10;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 int count=0;
 
while(1){
  if(count==0){
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  delay(100);
 }
  
  for(int i=0; i<256; i++)
    {
        analogWrite(LED1, i);
        if(i<128){
          analogWrite(LED2,i);
        }else{
          analogWrite(LED2,256-i);
        }
        delay(10);
    }
  
  for(int i=255; i>=0; i--)
    {
        analogWrite(LED1, i);
        if(i>128){
          analogWrite(LED2,256-i);
        }else{
          analogWrite(LED2,i);
        }
        delay(10);
     }
 count=count+1;
 if(count>3) count=0;
 if(count==1){
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,HIGH);
  delay(100);
 }
 if(count==2){
  digitalWrite(LED3,HIGH);
  digitalWrite(LED4,LOW);
  delay(100);
 }
 if(count==3){
  digitalWrite(LED3,HIGH);
  digitalWrite(LED4,HIGH);
  delay(100);
 }
 }
}
