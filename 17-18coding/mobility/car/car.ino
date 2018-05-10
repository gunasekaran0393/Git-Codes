include<SoftwareSerial.h>

SoftwareSerial serial(2,3);

char c;
int count =0;
void setup() {
  
  serial.begin(9600);
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  
  pinMode(8,OUTPUT);//Lf
  pinMode(9,OUTPUT);//Lb
  pinMode(10,OUTPUT);//Rf
  pinMode(11,OUTPUT);//Rb
  

  
  
  
}

void loop() 
{
  
  if(serial.available()>0)
  {
    c =serial.read();
    Serial.print(c);
  }
  
  if(c == 'a')
  {
    Serial.println("Start");
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  
   else if(c == 'b')
  {
   
    Serial.println("Stop");
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
 
   
  
//  else 
//  {
//    digitalWrite(8,LOW);
//    digitalWrite(9,LOW);
//    digitalWrite(10,LOW);
//    digitalWrite(11,LOW);
//  }
  

}


