/*----------------------------------------------------------*/
//RX pin 10 --> esp TX
//TX pin 11 --> esp RX

/*-----------------------------------------------------*/

#include <SoftwareSerial.h>
#include <stdlib.h>

/*-------------------------------------------------------*/
// LED indicattion for sensor readings uploaded
    int ledpin   =  13;
   
    
#define TIME_OUT 15000
long int previous =0;
long int time_out =0;  
/*------------------------------------------------------------*/

// your channel's thingspeak API key
String apiKey ="3H0977KKBSF85EKY";

/*----------------------------------------------------*/
SoftwareSerial ser(2,3); // RX, TX

// this runs once
void setup()
{    

 
  // initialize the digital pin as an output.
 
 
 pinMode(ledpin,OUTPUT);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);

 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);

  
  // enable debug serial
  Serial.begin(9600); 
  // enable software serial
  ser.begin(57600);
  
 

  
  // reset ESP8266
  ser.println("AT+RST");
  Serial.println("Reseting");
  delay(3000);
  
 digitalWrite(8,HIGH); 
 digitalWrite(9,HIGH); 

 digitalWrite(6,LOW); 
 digitalWrite(7,LOW); 


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
    int ct;
    
    ct = analogRead(0);
    ct = ct*2;
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
  
    String strct  = dtostrf(ct, 4, 1, buf);
  /*---------------------------------------------------------------*/
//    String strph   = dtostrf(ph, 4, 1, buf);
  /*-------------------------------------------------------------*/
//   String strtemp   = dtostrf(temp, 4, 1, buf);
 
//  
  Serial.print("ct ");
 Serial.println(strct);
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
  getStr += String(strct);
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

if(ct > 150){
  
      
    int count = 10;

    while(count>0){
      digitalWrite(7,HIGH);
      delay(100);
      digitalWrite(7,LOW);
      delay(200);

      count--;
    }

    delay(2000);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);

}
  
  // thingspeak needs 15 sec delay between updates
  
  
 
  
}


