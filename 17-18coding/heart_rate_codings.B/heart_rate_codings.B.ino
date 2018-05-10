 /*----------------------------------------------------------*/
//RX pin 10 --> esp TX
//TX pin 11 --> esp RX

/*-----------------------------------------------------*/
#include <Wire.h>
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
String apiKey ="HJXKWP5RCRLJ9N7Z";

/*----------------------------------------------------*/
SoftwareSerial ser(2,3);// RX, TX

int count=0,i=0,k=0,heartrate=0;
unsigned long time2,time1;
unsigned long time;

// this runs once
void setup()
{    

 
  // initialize the digital pin as an output.
 
 
 pinMode(ledpin,OUTPUT);
 pinMode(7,INPUT);
  
  // enable debug serial
  Serial.begin(9600); 
  // enable software serial
  ser.begin(115200);
  
 

  
  // reset ESP8266
  ser.println("AT+RST");
  Serial.println("Reseting");
  delay(3000);
  
 //digitalWrite(8,HIGH); 
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
   int k=0,heartrate=0;
   int i = 0;
   
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
      heartrate=time2-time1;
      heartrate=heartrate/5;
      heartrate=60000/heartrate;
      delay(2);
      
      //Serial.print("Heart: ");
      //Serial.println(heartrate);
      //delay(1);//int gas,ph;
    
    //gas = analogRead(0);
    //delay(2);
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
  
    String strheartrate  = dtostrf(heartrate, 4, 1, buf);
  /*---------------------------------------------------------------*/
//    String strph   = dtostrf(ph, 4, 1, buf);
  /*-------------------------------------------------------------*/
//   String strtemp   = dtostrf(temp, 4, 1, buf);
 
//  
  Serial.print("heartrate ");
 Serial.println(strheartrate);
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
  getStr += String(strheartrate);
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

if (heartrate > 250)
{
  Serial.println("Heart Rate HIGH");
}
else {
  Serial.print("Heart beat Level:");
   Serial.println(heartrate);
}
  
  // thingspeak needs 15 sec delay between updates
  
  
 
  
}

  
