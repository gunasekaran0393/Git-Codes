#include<SoftwareSerial.h>
SoftwareSerial serial(2,3);
void setup()
{
  Serial.begin(9600);
  serial.begin(9600);
  
  
  serial.println("AT+RST");
  delay(3000);
  serial.println("AT+CWSAP=\"esp_test2#\",\"12345678\",2,2");
  delay(2000);
  pinMode(13,OUTPUT);
  
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  
}

void loop(){
  
  int x = analogRead(0);
  
  if(x < 350){
    
    serial.println("AT+CWSAP=\"esp_test\",\"12345678\",2,2");
    delay(1000);
    serial.println("AT+RST");
     delay(3000);
  }
//  Serial.println(x);
//  
//  delay(100);
 
  
}
