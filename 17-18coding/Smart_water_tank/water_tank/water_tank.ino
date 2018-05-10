// ip address http://192.168.152.1

#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define DEBUG 1
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3

#define ECHOPIN 11  
#define TRIGGERPIN 12  
#define US_ROUNDTRIP_IN 146      
#define US_ROUNDTRIP_CM 57       
#define PingConvert(echoTime, conversionFactor) ((echoTime + conversionFactor / 2) / conversionFactor)  
  
  
unsigned long pinStart;  
unsigned long pinEnd;  
unsigned int sonar();
void init_sonar();




void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  init_sonar();
  
  lcd.init();                      // initialize the lcd 
 // Print a message to the LCD.
 lcd.backlight();
 
 lcd.setCursor(0,0);
 lcd.print("Tank control");
  
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);
 
//  pinMode(10,OUTPUT);
//  digitalWrite(10,LOW);
//  
//  pinMode(11,OUTPUT);
//  digitalWrite(11,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  
  
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  delay(3000);
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,3333\r\n",1000,DEBUG); // turn on server on port 80
  Serial.println("entering");
}
 
void loop()
{
//  
//  Serial.println(sonar());
  int level = sonar();
  lcd.setCursor(0,1);
  lcd.print("Water Level:");
  lcd.setCursor(12,1);
  lcd.print(level);
  lcd.print("    ");
  
  if(level > 20){
    digitalWrite(8,HIGH);
  }
  
  else if(level < 5){
    digitalWrite(8,LOW);
  }
  

  
  delay(500);
  if(esp8266.available()) // check if the esp is sending a message 
  {
       
   
    if(esp8266.find("+IPD,"))
    {
      digitalWrite(13, HIGH);
      delay(1000);
      delay(1000); // wait for the serial buffer to fill up (read all the serial data)
     digitalWrite(13, LOW);
     // get the connection id so that we can then disconnect
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
      /*---------------------------------------------------------*/
      int pin_number = 0;
      if(esp8266.find("pin=")) // advance cursor to "pin="
      {
        pin_number = esp8266.parseInt();
        Serial.print("pin_number:");
        Serial.print(pin_number);
        if(pin_number == 22){
          
          digitalWrite(9, HIGH);
        }
        else if(pin_number == 2){
          
          digitalWrite(9, LOW);
        }
        if(pin_number == 11){
          
          digitalWrite(8, HIGH);
        }
        if(pin_number == 1){
          
          digitalWrite(8, LOW);
        }
        
       
      }


 
      String webpage;
      String cipSend;
     webpage = "<head><title>foreview</title></head>";
     webpage+= "<h1 align=center><font>Smart Tank Control </font></h1>";
     webpage+="<br/>";
     webpage+="<br/>";
     webpage+="<body align=center>";
     webpage+="<button onclick=\"location.href='/pin=8'\">SWITCH_1</button><br/><br/><button onclick=\"location.href='/pin=9'\">SWITCH_2</button><br/><br/>";
//     webpage+="<button onclick=\"location.href='/pin=10'\">SWITCH_3</button><br/><br/><button onclick=\"location.href='/pin=11'\">SWITCH_4</button><br/>";
     webpage+= "</body>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);


     // make close command
//     String closeCommand = "AT+CIPCLOSE="; 
//     closeCommand+=connectionId; // append connection id
//     closeCommand+="\r\n";
//     
//     sendData(closeCommand,1000,DEBUG); // close connection
    }

  }
}
 
/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{


  
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

void init_sonar(){

   pinMode(TRIGGERPIN, OUTPUT);  
   pinMode(ECHOPIN, INPUT);
}

unsigned int sonar(void){

  digitalWrite(TRIGGERPIN,LOW);  
  delayMicroseconds(2);  
  digitalWrite(TRIGGERPIN,HIGH);  
  delayMicroseconds(10);  
  digitalWrite(TRIGGERPIN,LOW);  
  
  while(digitalRead(ECHOPIN)==LOW){}; //waiting for the pin to trigger  
  pinStart = micros();  
  while(digitalRead(ECHOPIN)==HIGH){};//waiting for the pin to go low  
  pinEnd = micros();  
  
  unsigned int echoTime = pinEnd - pinStart;  

  return (PingConvert(echoTime,US_ROUNDTRIP_IN));  
      
}
