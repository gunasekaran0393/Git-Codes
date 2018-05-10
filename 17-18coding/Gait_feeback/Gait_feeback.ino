#include <SoftwareSerial.h>

#include<Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial serial(2,3);


LiquidCrystal_I2C lcd(0x27,20,4);


int count=0,i=0,k=0,rate=0;
unsigned long time2,time1;
unsigned long time;

void setup() 
{
  lcd.init();
  lcd.backlight();
  
Serial.begin(9600);
serial.begin(9600);

 lcd.setCursor(0,0);
 lcd.print("Gait Feedback");

pinMode(8,OUTPUT);
pinMode(9,OUTPUT);

pinMode(10,OUTPUT);
pinMode(11,OUTPUT);


pinMode(7,INPUT);


digitalWrite(9,LOW);

digitalWrite(11,LOW);

}

void loop() 
{
  
int pres1,pres2;
int i = 0;

  k=0;
 rate=0;
      
pres1 = analogRead(0);
delay(2);


pres2 = analogRead(1);
delay(2);


   
    while(k<5)
    {
     if(digitalRead(7))
     {
      if(k==0)
      time1=millis();
      k++;
      while(digitalRead(7));
     }
    }
      time2=millis();
      rate=time2-time1;
      rate=rate/5;
      rate=60000/rate;
//     Serial.println(rate);  
    
 
 
Serial.print("Pressure1: ");
Serial.println(pres1);
Serial.print("Pressure2: ");
Serial.println(pres2);
//Serial.print("Heart: ");
//Serial.println(rate);
//Serial.println("-------------------");
 
 signed int diff = pres1-pres2;

//Serial.println(diff);
//Serial.println("-------------------");

 Serial.println(diff);
  if(diff > 200)
  {
    
    digitalWrite(8,HIGH);
    Serial.println("Pressure 1 HIGH");
     lcd.setCursor(0,1);
     lcd.print("Pressure 1 HIGH");
    serial.println("Pressure 1 HIGH");
  }
 else if(diff < -200)
 {
   
   digitalWrite(10,HIGH);
   Serial.println("Pressure 2 HIGH");
   lcd.setCursor(0,1);
     lcd.print("Pressure 2 HIGH");
   serial.println("Pressure 2 HIGH");
 }
 
 else if(rate > 250)
 {
  
   Serial.println("Heart Rate HIGH");
   lcd.setCursor(0,1);
     lcd.print("Heart Rate HIGH");
   serial.println("Heart Rate HIGH");
 }
 
 
 else 
 {
   Serial.println("Equal pressure");
   serial.println("Equal pressure");
   lcd.setCursor(0,1);
   lcd.print("Normal          ");
   serial.print("Pressure 1 Level:");
   serial.println(pres1);
   serial.print("Pressure 2 Level:");
   serial.println(pres2);
   serial.print("Heart beat Level:");
   serial.println(rate);
   serial.print("");
   digitalWrite(8,LOW);
   digitalWrite(10,LOW);
 }
 

 //delay(1000);
 
 

}
