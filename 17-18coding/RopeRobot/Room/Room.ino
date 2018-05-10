#include<SoftwareSerial.h>

SoftwareSerial serial(2,3);

void setup(){
  
  Serial.begin(9600);
  serial.begin(9600);
  
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  
  
}

void loop(){
  
  char c;
  
 if(serial.available()>0){
   
   c = serial.read();
   
   if((c == 'T')||(c =='F')){
     digitalWrite(8,HIGH);
   }
   
   else if(c == 'L'){
     digitalWrite(9,HIGH);
   }
 }
  
}
