

#include <SoftwareSerial.h>

SoftwareSerial serial(2,3);

String s = "";
void setup() {
 Serial.begin(9600);
 serial.begin(9600);
 

}

void loop() 
{
 int temp,gas,vib,fuel,flame,volt;
  
 temp = analogRead(1);
 delay(2);
 gas  = analogRead(0);
 delay(2);
 flame  = analogRead(4);
 delay(2);
 fuel   = analogRead(3);
 delay(2);
 vib   = analogRead(2);
 delay(2);
// volt   = analogRead(2);
// delay(2);
 


 s += temp;
 s +='+';
 s += gas;
 s +='+';
 s += flame;
 s +='+';
 s += fuel;
 s +='+';
 s += vib;
// s +='+';
// s += volt;
 s +='\r';

 
 
 Serial.println(s);
 serial.println(s);
 s = "";
 delay(500);
  

}
