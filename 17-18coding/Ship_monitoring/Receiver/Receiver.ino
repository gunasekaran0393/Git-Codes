
#include<SoftwareSerial.h>
#include<Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

SoftwareSerial serial(2,3);
String inData;

void setup() {
  
  lcd.init();
  lcd.backlight();
  
    serial.begin(9600);
    Serial.begin(9600);
  
   lcd.setCursor(0,0);
   lcd.print("Ship Monitoring");
    pinMode(13,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    digitalWrite(6,LOW);
}


void loop() 
{
   int count;
    while (serial.available() > 0)
     {
       char received = serial.read();
           inData += received; 
        if(received == '\n')
        {
          //Serial.println(inData);
          printtext(inData);
          inData = "";
          
        }
        
//       digitalWrite(13,HIGH);
//       delay(100);
//       digitalWrite(13,LOW);
//       delay(100);
       
     }

}



void printtext(String text) 
 {
  String s="";
  int i=0;
  for(;text[i]!='\n';i++)
  {
    if(text[i]=='+')
    {
      text[i]=' ';
      s+=text[i];
    }
    else 
    {
    s+=text[i];
    }
    
  }
  i++;
  text[i]='\0';
  s+=text[i];

print20x4(s);
 
  
 }

 void print20x4(String st)
 {
  String line1="";
  String line2="";
  String line3="";
  String line4="";
  String line5="";
  String line6="";
  int i=0;
  
  for(;(st[i]!='\0')&&(st[i]!=' ');i++)
  {
    
    line1 +=st[i];
    
    
  }
  
  
i++;

  for(;((st[i]!='\0')&&(st[i]!= ' '));i++)
  {
    line2+=st[i];
  }
  
  
i++;
  for(;((st[i]!='\0')&&(st[i]!= ' '));i++)
 {
   line3+=st[i];
 }
i++;

  for(;((st[i]!='\0')&&(st[i]!='\r')&&(st[i]!= ' '));i++)
 {
    line4+=st[i];
 }
 i++;

  for(;((st[i]!='\0')&&(st[i]!='\r')&&(st[i]!= ' '));i++)
 {
    line5+=st[i];
 }
  i++;

  for(;((st[i]!='\0')&&(st[i]!='\r')&&(st[i]!= ' '));i++)
 {
    line6+=st[i];
 }
  
st[i-2] = '\0';
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Ship Parameter Monitor");
    
     lcd.setCursor(0,1);
     lcd.print("Temp:");
     
     lcd.setCursor(11,1);
     lcd.print("Gas:");
     
     lcd.setCursor(0,2);
     lcd.print("Flame:");
     
     lcd.setCursor(11,2);
     lcd.print("Fuel:");
     
     lcd.setCursor(0,3);
     lcd.print("Vib:");
//     
//     lcd.setCursor(11,3);
//     lcd.print("Volt:");

     lcd.setCursor(6,1);
     lcd.print(line1);
     
     lcd.setCursor(16,1);
     lcd.print(line2);
     
     
     lcd.setCursor(6,2);
     lcd.print(line3);

     lcd.setCursor(16,2);
     lcd.print(line4);
  
     lcd.setCursor(6,3);
     lcd.print(line5);

Serial.print("Temp: ");
Serial.println(line1);
Serial.print("Gas: ");
Serial.println(line2);
Serial.print("Flame: ");
Serial.println(line3);
Serial.print("Fuel: ");
Serial.println(line4);
Serial.print("Vib: ");
Serial.println(line1);
Serial.println("--------------------");
//     lcd.setCursor(16,3);
//     lcd.print(line6);
//   
  
 
     
   control(line1.toInt(),line2.toInt(),line3.toInt(),line4.toInt());
     
    line1="";
    line2="";
    line3="";
    line4="";
    line5="";
    line6="";
 }
 void control(int v,int x ,int y,int z )
{
  int count =0;
  //Serial.print("integer value:");
  //Serial.println(x);
 if(y < 800){
   while(count <=5){
     digitalWrite(7,HIGH);
     delay(100);
     digitalWrite(7,LOW);
     delay(100);
     
     count++;
   }
 }
//  else if( x > 960)
//  {
//    Serial.println("check 2");
//     digitalWrite(12,HIGH);
//   
//    
//  }
// 
//
//  else if(y < 290)
//  {
//    Serial.println("check 3");
//     digitalWrite(12,HIGH);
//    
//  }
//  
//  else if(z > 720)
//  {
//    Serial.println("check 4");
//     digitalWrite(12,HIGH);
//  }
//   
// 
// 
//  else
//  {
//    
//    Serial.println("check 5");
//   digitalWrite(12,LOW);
//}
}



