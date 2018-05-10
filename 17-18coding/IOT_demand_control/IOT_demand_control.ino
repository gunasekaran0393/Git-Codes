/*----------------------------------------------------------*/
//RX pin 10 --> esp TX
//TX pin 11 --> esp RX

/*-----------------------------------------------------*/

#include <SoftwareSerial.h>
#include <stdlib.h>


#define TIME_OUT 15000

long int time_out =0;
/*-----------*/
long int previous =0;
// your channel's thingspeak API key
String apiKey = "NJZSPG46LTO7U24P";

/*----------------------------------------------------*/
SoftwareSerial ser(2,3); // RX, TX

// this runs once
void setup()
{                
 
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  pinMode(13,OUTPUT);
  
  // enable debug serial
  Serial.begin(9600); 
  // enable software serial
  ser.begin(115200);
  
  
  
  // reset ESP8266
  ser.println("AT+RST");
  
     digitalWrite(6,LOW);  // 
     digitalWrite(8,HIGH);//L1    r4
     digitalWrite(9,HIGH);//L2    r5
    
     
  
}


// the loop 
void loop() 
{
  long int current= millis();
  
  // blink LED on board
  
  digitalWrite(13, HIGH);   
  delay(200);               
  digitalWrite(13, LOW);

  // Read the value from Sensors
  // Read 10 values for averaging.
  /*--------------------------------------------------------*/
    int ct1,ct2,ct3,volt;
    ct1 = analogRead(0);//60w 36 - 38 100 w 66 -69 40 w 20 22
    ct1 = ct1*1.33;
//    delay(2);
//    ct2 = analogRead(1);//60w 36 - 38 100 w 69 -70 40w  20 22
//    ct2 = ct2*2;
//    delay(2);
//    ct3 = analogRead(2); //60w 28-30  100w  56 - 57  40w 16 17
//    ct3 = ct3*2;
//    delay(2);
//    volt = analogRead(3);// 500
//    volt = volt/1.9;
//    delay(2);
    
  /*-------------------------------------------------------*/
  
  /*-------------------------------------------------------*/
  // convert to string
    char buf[16];
  
    String strct1  = dtostrf(ct1, 4, 1, buf);
  /*---------------------------------------------------------------*/
//    String strct2  = dtostrf(ct2, 4, 1, buf);
//  /*-------------------------------------------------------------*/
//    String strct3  = dtostrf(ct3, 4, 1, buf);
//  /*-------------------------------------------------------------*/
//    String strvolt  = dtostrf(volt, 4, 1, buf);
//  /*-------------------------------------------------------------*/
    
  
  Serial.print("load1: ");
  Serial.println(strct1);
  Serial.println(time_out);
//  /*--------------------------------------------------------*/
//  Serial.print("Load2: ");
//  Serial.println(strct2);
//  /*--------------------------------------------------------*/
//  Serial.print("Load3: ");
//  Serial.println(strct3);
//  /*--------------------------------------------------------*/
//  Serial.print("Volt: ");
//  Serial.println(strvolt);
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
  getStr += String(strct1);
//  getStr +="&field2=";
//  getStr += String(strct2);
//  getStr +="&field3=";
//  getStr += String(strct3);
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

if(ct1 > 120)
{
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  
  
  digitalWrite(7,HIGH);
  delay(500);
  digitalWrite(7,LOW);
}
//else{
//  
//digitalWrite(8,HIGH);
//digitalWrite(9,HIGH);
//}
  
    
}


