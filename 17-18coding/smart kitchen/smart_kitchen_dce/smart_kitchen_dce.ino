/*----------------------------------------------------------*/
//RX pin 10 --> esp TX
//TX pin 11 --> esp RX

/*-----------------------------------------------------*/

#include <SoftwareSerial.h>
#include <stdlib.h>
#include<Servo.h>

Servo servo;
/*-------------------------------------------------------*/
// LED indicattion for sensor readings uploaded
    int ledpin   =  13;
   
    
#define TIME_OUT 15000
long int previous =0;
long int time_out =0;  
/*------------------------------------------------------------*/

// your channel's thingspeak API key
String apiKey ="KP3DRSB3OLBIG36Z";

/*----------------------------------------------------*/
SoftwareSerial ser(2,3); // RX, TX

// this runs once
void setup()
{    

servo.attach(8);
  servo.write(0);
  delay(2000); 
  // initialize the digital pin as an output.
 
 
 pinMode(ledpin,OUTPUT);
 
 pinMode(6,OUTPUT);
 
 pinMode(8,OUTPUT);
  
  // enable debug serial
  Serial.begin(9600); 
  // enable software serial
  ser.begin(115200);
  
 

  
  // reset ESP8266
  ser.println("AT+RST");
  Serial.println("Reseting");
  delay(3000);
  digitalWrite(6,LOW);
 digitalWrite(8,LOW); 
 servo.write(0);
  delay(1000); 
 
}


// the loop 
void loop() 

{
 
  // blink LED on board
   long int current= millis();
  digitalWrite(ledpin, HIGH);   
  delay(200);               
  digitalWrite(ledpin, LOW);

 
  // Read the value from Sensors
  // Read 10 values for averaging.
  /*--------------------------------------------------------*/
    int gas;
    
    gas = analogRead(0);
    delay(2);
//    ph = analogRead(1);
//    delay(2);        
          
  /*-------------------------------------------------------*/
  
  /*-------------------------------------------------------*/
  // convert to string
    char buf[16];
//    char c;
//    if(Serial.available()>0)
//    {
//     c =Serial.read()
//     while(c != 0A){
//       rec +=c;
//        c = Serial.read();
//        
//       
//      }
//    }
  
    String strgas  = dtostrf(gas, 4, 1, buf);
  /*---------------------------------------------------------------*/
//    String strph   = dtostrf(ph, 4, 1, buf);
  /*-------------------------------------------------------------*/
//   String strtemp   = dtostrf(temp, 4, 1, buf);
 
//  
  Serial.print("gas ");
 Serial.println(strgas);
// // Serial.println(rec);
//  
  /*--------------------------------------------------------*/
// Serial.print("ph  ");
// Serial.println(strph);
 
// Serial.print("temp  ");
// Serial.println(strtemp);
//  /*--------------------------------------------------------*/
 if(time_out >= TIME_OUT){
   
     time_out = 0;
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
 /*-----------------------------------------------*/  
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
 /*----------------------------------------*/ 
  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(strgas);
//  getStr +="&field2=";
//  getStr += String(strph);
//  getStr +="&field3=";
//  getStr += String(strprox);
//  getStr +="&field4=";
//  getStr += String(strvolt);
  getStr += "\r\n\r\n";

 
/*-----------------------------------------------------------*/
  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
  /*-------------------------------------------*/
    if(ser.find(">"))
    {
    ser.print(getStr);
    }
  else{
   
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  /*-------------------------------------------------------------------*/
  }

else{
     time_out += current - previous;
     previous = current;
     
}

if(gas > 600)
{
  digitalWrite(6,HIGH);
  digitalWrite(8,HIGH);
  servo.write(90);
  delay(5000); 
    

 
}
  
  
  // thingspeak needs 15 sec delay between updates
  
  
 
  
}


