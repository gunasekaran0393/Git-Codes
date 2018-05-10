#include<SoftwareSerial.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
//#incldue<String.h>

LiquidCrystal_I2C lcd(0x27,16,2);
long int prev_e = 0;
SoftwareSerial serial(2,3);

int time_out = 0;
String s="";
bool stat =false;
int count = 1;
void setup()
{
  Wire.begin();
  lcd.backlight();
  lcd.init();
 
  lcd.setCursor(0,0);
  lcd.print("Jayanthi:");
  
  lcd.setCursor(0,1);
  lcd.print("Sumathi :");
   
  pinMode(13,OUTPUT);
  
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
   
 
  
  Serial.begin(9600);
  serial.begin(9600);
  
  serial.println("AT+RST");
  delay(3000);
  
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  digitalWrite(6,LOW);
  
  serial.flush();
  digitalWrite(7,HIGH);
  delay(500);
  digitalWrite(7,LOW);
}

void loop()
{

 serial.println("AT+CWLAP");
//  while(!serial.available());
 if(serial.available()>0)
 {
     while(serial.available()){
      char c = serial.read();
      delay(5);
     s += c;
   }
   
   stat =true;
  
   
 }
 if(stat==true)
 {
  stat =false;
  Serial.println(s);
  parseRssi(s);
  s="";
 }

serial.flush();
delay(4000);
  
}


int parseRssi(String s){
 
  String rssi1 ="";
  String rssi2 ="";
  int firstPos = s.indexOf("1#");
  int secondPos = s.indexOf("2#");
 

//  if((firstPos == -1)&&(secondPos == -1)){
//   return 0; 
//  }
  
//  Serial.println(s);
  rssi1 += s.charAt(firstPos+5);
  rssi1 += s.charAt(firstPos+6);
  
  rssi2 += s.charAt(secondPos+5);
  rssi2 += s.charAt(secondPos+6);

  Serial.println(rssi1.toInt());
  Serial.println(rssi2.toInt());
  
  lcd.setCursor(0,0);
  lcd.print("Jayanthi:");
  lcd.setCursor(10,0);
  lcd.print(rssi1.toInt());
  
  lcd.setCursor(0,1);
  lcd.print("Sumathi:");
  lcd.setCursor(10,1);
  lcd.print(rssi2.toInt());

  if((firstPos == -1)||(secondPos == -1)){
   buzzer(2);
    Serial.println("buzzer2");
  }
  if((rssi1.toInt()>70)||(rssi2.toInt()>70)){
     buzzer(3);
  }
  
  
}
void buzzer(int c){
   int count = 0;
  
 while(count <= c){
        digitalWrite(7,HIGH);
        delay(100);
        digitalWrite(7,LOW);
         delay(100);
        count++;
    }
}

