#include<SoftwareSerial.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial serial(2,3);

#define TIME_OUT 15000

char *Name[] = {"JAMES","KARTHICK" };
char *No[]={"310814205024","310814205033"};

String card1 = "2100885AE91A";
String card2 = "210087D9EC93";

String s ="";
bool flag = false;

bool c1_flag = false, c2_flag = false;

int card1_C = 0;
int card2_C = 0;

void setup(){
  
    Wire.begin();
    lcd.backlight();
    lcd.init();
    lcd.setCursor(0,0);
    lcd.print("Exam Hall Finder");
    
   Serial.begin(9600);
   serial.begin(9600);
   
   pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);
   pinMode(13,OUTPUT);
   
   digitalWrite(8,LOW);
   digitalWrite(9,LOW);

}

void loop(){
  
  if(serial.available()>0)
    while (serial.available() > 0) {
      char c = serial.read();
      delay(5);
      s += c;
      flag = true;
    }
    if(flag == true){
      
       flag = false;
   
      if(s == card1){
        c1_flag = true;
        card1_C++;        
        Serial.println("card_1");
       
      }
      else if(s == card2){
        c2_flag = true;   
        card2_C++;     
        Serial.println("card_2");
       
      }
      
       s ="";
    }
    
    if(c1_flag == true){
      
      c1_flag = false;
      
      if(card1_C == 1){
      
        lcd.setCursor(0,0);
        lcd.print("JAMES");
        lcd.print("           ");
        
//        lcd.setCursor(0,2);
//        lcd.print("310814205024");
//        lcd.print("    ");
//        
        lcd.setCursor(0,1);
        lcd.print("Hall:10 Seat:20");
  
      }
//     else if(card1_C == 2){
//        card1_C = 0;
//        lcd.setCursor(0,1);
//        lcd.print("JPR to TBM");
//        lcd.print("      ");
//        
//        lcd.setCursor(0,2);
//        lcd.print("Bus No: 12");
//        lcd.print("      ");
//        lcd.setCursor(0,3);
//        lcd.print("               ");
//        
//      }
    }
    
    if(c2_flag == true){
      
      c2_flag = false;
      
       if(card2_C == 1){
        lcd.setCursor(0,0);
        lcd.print("KARTHICK");
        lcd.print("         ");
         
//        lcd.setCursor(0,2);
//        lcd.print("310814205033");
//        lcd.print("    ");
//        
        lcd.setCursor(0,1);
        lcd.print("Hall:12 Seat:25");
        lcd.print("   ");
      }
//      else if(card2_C == 2){
//        card2_C = 0;
//        lcd.setCursor(0,1);
//        lcd.print("JPR to Guindy");
//        lcd.print("          ");
//        
//        lcd.setCursor(0,2);
//        lcd.print("Bus No: 20");
//        lcd.print("          ");
//        
//        lcd.setCursor(0,3);
//        lcd.print("               ");
//      }
  }
    
  
}

