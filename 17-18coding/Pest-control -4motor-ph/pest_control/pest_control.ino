#include<SoftwareSerial.h>

SoftwareSerial serial(2,3);

void setup()
{
  Serial.begin(9600);
  serial.begin(9600);

  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(13,OUTPUT);
//  pinMode(6,OUTPUT);
//  pinMode(7,OUTPUT);
//  pinMode(8,OUTPUT);
 
 digitalWrite(2,LOW);
 digitalWrite(3,LOW);
 digitalWrite(4,LOW);
 digitalWrite(5,LOW);
 digitalWrite(13,LOW);
// digitalWrite(6,HIGH);
// digitalWrite(7,HIGH);
// digitalWrite(8,HIGH);
 
  
}

void loop()
{
 char c;
 
 int x = analogRead(0);
// Serial.println(x);
 if(x < 300){
   Serial.println("Test0");
   digitalWrite(2,HIGH);
   delay(2000);
   digitalWrite(2,LOW);
   
 }
 if(Serial.available())
 {
  Serial.println("test");
  c=Serial.read();
  Serial.print(c);
  if(c=='a')
  {
   Serial.println("Test1");
   digitalWrite(3,HIGH);
   delay(2000);
   digitalWrite(3,LOW);
  }
  
  else if(c =='b')
  {
     Serial.println("Test2");
     digitalWrite(4,HIGH);
     delay(2000);
     digitalWrite(4,LOW);
  }
  
  else if(c =='c')
  {
   Serial.println("Test3");
   digitalWrite(5,HIGH);
   delay(2000);
   digitalWrite(5,LOW);
    
  }
  
  else if(c =='d')
  {
   Serial.println("Test3");
   digitalWrite(5,HIGH);
   delay(2000);
   digitalWrite(5,LOW);
    
  }

}


}


