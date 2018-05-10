#include<SoftwareSerial.h>

SoftwareSerial serial(2,3);

void setup()
{
   Serial.begin(9600);
   serial.begin(9600);
   
   pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);
   
   pinMode(10,OUTPUT);
   pinMode(11,OUTPUT);
   
   pinMode(2,OUTPUT);
   pinMode(3,OUTPUT);
   
   
    
   pinMode(6,INPUT_PULLUP);
   pinMode(7,INPUT_PULLUP);
   

  
  digitalWrite(2,LOW); //buzzer
  digitalWrite(3,LOW);
  
  
  digitalWrite(9,HIGH); //back
  digitalWrite(8,LOW);
 
  while(digitalRead(6)== LOW);
  
  digitalWrite(9,LOW); //stop
  digitalWrite(8,LOW);
  
  digitalWrite(10,LOW); //stop
  digitalWrite(11,LOW);

  
  

}

void loop()
{

 int i =0;
  digitalWrite(3,HIGH);
  delay(1000);
  digitalWrite(3,LOW);
  
  digitalWrite(9,LOW); //front
  digitalWrite(8,HIGH);
  
  while(digitalRead(7)== LOW);  
  
  digitalWrite(9,LOW); //stop
  digitalWrite(8,LOW);
 
  delay(3000);
  
   while(i < 10){
    serial.println('a');
   i++;
 }
  i =0;
  delay(2000);
   
    
//  digitalWrite(3,HIGH);
//  delay(1000);
//  digitalWrite(3,LOW);
  
  
  digitalWrite(9,HIGH); //back
  digitalWrite(8,LOW);
  
  
  while(digitalRead(6)== LOW);  
  
  digitalWrite(9,LOW); //stop
  digitalWrite(8,LOW);
   while(i < 10){
      serial.print('b');
    i++;
   }
     i =0;
  delay(3000);
  
   while(i < 10){
    serial.print('a');
   i++;
 }
   i =0;
  delay(3000);
   while(i < 10){
  serial.print('b');
  i++;
   }
     i =0;
//  
//  digitalWrite(3,HIGH);
//  delay(1000);
//  digitalWrite(3,LOW);
  
  digitalWrite(9,LOW); //front
  digitalWrite(8,HIGH);
  
  while(digitalRead(7)== LOW);  
  
  digitalWrite(9,LOW); //stop
  digitalWrite(8,LOW);
  while(1);
   
}
