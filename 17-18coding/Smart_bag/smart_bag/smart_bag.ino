
#include<SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serial(2,3);
TinyGPS gps; // create gps object

float lat,lon; // create variable for latitude and longitude object

bool flag = false;
long int timer = 0;

#define TIME_OUT 15000
long int previous =0;
long int time_out =0;  

String location = "";

String book = "";

int cr_book = 0;
int wr_book = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
serial.begin(9600);

pinMode(8,INPUT_PULLUP);

}

void loop() {

   long int current= millis();

   char c;

  while(serial.available()){ // check for gps data
   if(gps.encode(serial.read())){ // encode gps data
    gps.f_get_position(&lat,&lon); // get latitude and longitude
    // display position
//    Serial.print("Position: ");
//    Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
//    Serial.print("lon: ");Serial.println(lon); // print longitude
   }
  }

if(Serial.available()>0){

  c = Serial.read();
  Serial.print("Received:");
  Serial.println(c);
  
 if(c == 'r'){
  
  Serial.println("red");
  cr_book++;
  
 }
 else if(c == 'b'){

  Serial.println("blue");
  wr_book++;
 }
 
}


if(digitalRead(8)== LOW){

    delay(50);
    if(digitalRead(8)== LOW){
  
      Serial.println("Switch pressed");
      flag = true;
      book += cr_book;
      book += " Correct book ";
      book += wr_book;
      book += " Wrong book";
      Send_Message(book);
      book = "=";
      cr_book = 0;
      wr_book = 0;
      time_out =0;
  }
}

if((time_out >= TIME_OUT)&&(flag == true)){
     time_out = 0;
     flag = false;
     location +="Lat:";
     location +=lat;
     location +=" Lon:";
     location +=lon;
     Send_Message(location);
     Serial.println("Timeout");
     location ="";
}

else{

       time_out += current - previous;
       previous = current;
 
}


  
  // put your main code here, to run repeatedly:

}


void Send_Message(String s)
{
 
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+919790377571\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println(s);// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("Sent_message");
}

