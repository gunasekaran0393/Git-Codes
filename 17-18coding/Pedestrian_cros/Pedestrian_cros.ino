void setup(){
  
 Serial.begin(9600);

pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);

pinMode(6,OUTPUT);
pinMode(7,OUTPUT);

pinMode(8,OUTPUT);


digitalWrite(2,LOW);
digitalWrite(4,LOW);
digitalWrite(6,LOW);
digitalWrite(7,LOW);

digitalWrite(8,LOW);


analogWrite(3,255);

}

void loop(){
  
  char c;
  if(Serial.available()>0){
    
   c =Serial.read();
//   Serial.print(c); 
   
   if(c =='a'){
     
     analogWrite(3,128);
     
     digitalWrite(8,HIGH);

     for(int i =0;i<=5;i++){
       digitalWrite(7,HIGH);
       delay(100);
       digitalWrite(7,LOW);
       delay(200);
     }
     digitalWrite(8,LOW);


  }
}
}
