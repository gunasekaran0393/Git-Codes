#include<SoftwareSerial.h>
#include <Servo.h>

#include<Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

Servo servo;

SoftwareSerial serial(2,3);


int msg_cnt;

bool pirflag =true;


void setup()
{
 
  lcd.init();
  lcd.backlight();
     
    
  Serial.begin(9600);//
  serial.begin(9600); //gsm
  
  servo.attach(6);
   
  pinMode(8,OUTPUT);//motor
  pinMode(9,OUTPUT);//motor
  pinMode(10,OUTPUT);//motor
  pinMode(11,OUTPUT);//motor
  
  lcd.setCursor(0,0);
  lcd.print("Home Monitoring");
  
  
  
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  
  servo.write(0);
  


}

void loop(){
  int gas = analogRead(0);
  int pir = analogRead(1);
  int temp = analogRead(2);
  int wl = analogRead(3);
 
//  Serial.print("Gas:");
//  Serial.println(gas);
//  Serial.print("PIR:");
//  Serial.println(pir);
//  Serial.print("temp:");
//  Serial.println(temp);
//  Serial.print("WaterLevel:");
//  Serial.println(wl);
//  delay(1000);
  
  
 if((pir > 500)&&(pirflag == true)){
  
   lcd.setCursor(0,1);
   lcd.print("                ");
   lcd.setCursor(0,1);
   lcd.print("Person Entered");
  
     Serial.println("Pir");
     pirflag = false;
     Send_Message("New person arrived"); 
     delay(1000);
     Receive_Message();
  
 }
 
 if(wl > 700){
  
   Serial.println("Water level");
   digitalWrite(8,HIGH);

  
   lcd.setCursor(0,1);
   lcd.print("Motor ON");
   lcd.print("       ");
 }
 
 else{
    digitalWrite(8,LOW);
 }
 
 if(temp < 350){
  
   Serial.println("temp level");
   digitalWrite(10,HIGH);
   lcd.setCursor(0,1);
   lcd.print("Fan ON");
   lcd.print("         ");
 }
 else{
   digitalWrite(10,LOW);
 }
 
 if(gas > 850){
 
   lcd.setCursor(0,1);
   lcd.print("Gas Alert");
   lcd.print("      ");
   Serial.println("gas level");
   Send_Message("Gas alert");
  
 }
 
 
  
}


void Send_Message(String s)
{
  msg_cnt = 1;
  serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  //serial.println("AT+CMGS=\"+918754213989\"\r"); // Replace x with mobile number
  serial.println("AT+CMGS=\"+918754213989\"\r"); // Replace x with mobile number
  delay(1000);
  serial.print(s);// The SMS text you want to send

  delay(100);
  serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("Sending_message");
}

void Receive_Message(void)
{
  char inchar;
  serial.println("AT+CMGF=1");
  delay(1000);
  serial.println("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  
 while(msg_cnt)
  {
   Serial.println("Entering_to_Measssage loop");
   //If a character comes in from the cellular module...
  if(serial.available() >0)
  {
    Serial.println("Waiting_to_Receive");
    inchar=serial.read(); 
    
    if (inchar=='#')
    {
       Serial.println("received");
      
     msg_cnt = 0; // for single time receiving sms
      delay(10);
 
      inchar=serial.read(); 
      if (inchar=='y')
      {
        Serial.println("In check");
        delay(10);
        inchar=serial.read();
        if (inchar=='e')
        {
           Serial.println("ok Matched");
           servo.write(90);
        } 
        
        
          serial.println("AT+CMGD=1,4"); // delete all SMS
        }
        
      else if (inchar=='n')
      {
        Serial.println("In check2");
        delay(10);
        inchar=serial.read();
        if (inchar=='o')
        {
           Serial.println("ok Matched2");
           
        } 
        
        
          serial.println("AT+CMGD=1,4"); // delete all SMS
        }
      }
    }
 }
 
}

