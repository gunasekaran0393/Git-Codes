#include<SoftwareSerial.h>

SoftwareSerial serial(2,3);

#define MOTOR1 8
#define MOTOR2 9

#define BUZZER1 6
#define BUZZER2 7

void setup(){
 Serial.begin(9600);
 serial.begin(9600);
 
  pinMode(MOTOR1,OUTPUT);
  pinMode(MOTOR2,OUTPUT);
  
  digitalWrite(MOTOR1,LOW);
  digitalWrite(MOTOR2,LOW);
  
  digitalWrite(BUZZER1,LOW);
  digitalWrite(BUZZER2,LOW);;'hjl
}


void loop(){
  
 int LDR,TEMP,FLAME,GAS;
 
 unsigned char c;
 
 
 TEMP = analogRead(0);
 LDR = analogRead(1);
 FLAME = analogRead(2);
 GAS = analogRead(3);
 
// Serial.print("Temperature:");
// Serial.println(TEMP);
// Serial.print("Light:");
// Serial.println(LDR);
// Serial.print("Flame:");
// Serial.println(FLAME);
// Serial.print("Gas:");
// Serial.println(GAS);
// Serial.println("--------------------------");
// delay(1000);
 
 
 if(TEMP < 100){
  Serial.print('T');
 }
 else if(LDR > 900){
  Serial.print('L');
 }
 else if(GAS > 300){
  Serial.print('F');
 }
 
 else if(FLAME < 500){
    
   digitalWrite(BUZZER1,HIGH);
   delay(100);
   digitalWrite(BUZZER1,LOW);
   delay(100);
   //Serial.print("flame");
 }
 
 else{
   digitalWrite(BUZZER1,LOW);
 }
 
 if(serial.available()>0){
    c = serial.read();
    
    if(c == 'F'){
       digitalWrite(MOTOR1,HIGH);
       digitalWrite(MOTOR2,LOW);
        Serial.print("Front");
    }
    else if(c == 'R'){
       digitalWrite(MOTOR1,LOW);
       digitalWrite(MOTOR2,HIGH);
       Serial.print("Back");
    }
    else if(c == 'S'){
       digitalWrite(MOTOR1,LOW);
       digitalWrite(MOTOR2,LOW);
        Serial.print("stop");
    }
    
 }
 
 
 
}
