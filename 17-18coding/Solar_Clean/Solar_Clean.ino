#include<Wire.h>
#include<LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);

void setup(){
  
  lcd.backlight();
  lcd.init();
  Serial.begin(9600);
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  
  lcd.setCursor(0,0);
  lcd.print("Solar Clean");

}

void loop(){
  
  int temp = analogRead(0);
  Serial.println(temp);
  int count = 2;
  if(temp < 350){
   lcd.setCursor(0,1);
   lcd.print("Cleaning");
   lcd.print("        "); 
    
    while(count > 0){
      Serial.println("Driving");
      forward();
      delay(1000);
      backward();
      delay(1000);
      count--;
    }
    
  }
  else{
    
   lcd.setCursor(0,1);
   lcd.print("Stopped"); 
   lcd.print("        "); 
  }
  
  
}

void forward(){
  
  Serial.println("forword");
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    
    while(digitalRead(8) == HIGH);
    Serial.println("Stop");
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    
    digitalWrite(4,LOW);
    digitalWrite(5,LOW); 
}

void backward(){
  
  Serial.println("backword");
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    
    while(digitalRead(9) == HIGH);
    Serial.println("Stop");
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    
    digitalWrite(4,LOW);
    digitalWrite(5,LOW); 
}


