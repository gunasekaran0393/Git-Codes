// ip address http://192.168.152.1

#include <SoftwareSerial.h>
 
#define DEBUG false
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);
 
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
  
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
   
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  delay(3000);
  sendData("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop()
{
  int x = analogRead(0);
  Serial.println(x);
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
//        Serial.print("pin_number:");
//        Serial.print(pin_number);
        
       //digitalWrite(pin_number, !digitalRead(pin_number));
       
       
       if(pin_number == 1){
         digitalWrite(10, HIGH);
       }
       else if(pin_number == 2){
         digitalWrite(10, LOW);
       }
       
       if(pin_number == 3){
         digitalWrite(11, HIGH);
       }
       else if(pin_number == 4){
         digitalWrite(11, LOW);
       }
       
      }


 
      String webpage;
      String cipSend;
     webpage = "<head><title>foreview</title></head>";
     webpage+= "<h1 align=center><font>Home Automation Control </font></h1>";
     webpage+="<br/>";
     webpage+="<br/>";
     webpage+="<body align=center>";
     webpage+="<button onclick=\"location.href='/pin=1'\">S1_ON</button>&nbsp;<button onclick=\"location.href='/pin=2'\">S1_OFF</button><br/><br/></body>";

     
          
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,2000,DEBUG);
     sendData(webpage,2000,DEBUG);
     
    

       webpage ="<body align=center>";
     
       webpage +="<button onclick=\"location.href='/pin=3'\">S2_ON</button>&nbsp;<button onclick=\"location.href='/pin=4'\">S2_OFF</button><br/><br/></body>";

//    if(x < 400){
//       webpage +="<button>Alert</button>";
//     
//     }
//     else{
//        webpage +="<button>Normal</button>";
//     }
     
//     webpage += "<META HTTP-EQUIV=\"refresh\" CONTENT=\"10\">";
//     webpage += "</body>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,2000,DEBUG);
     sendData(webpage,2000,DEBUG);
     
     // make close command
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,1000,DEBUG); // close connection
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




