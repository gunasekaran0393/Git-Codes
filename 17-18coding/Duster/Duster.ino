void setup(){
  
 Serial.begin(9600);

pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);

pinMode(8,INPUT_PULLUP);
pinMode(9,INPUT_PULLUP);
pinMode(10,INPUT_PULLUP);

digitalWrite(2,LOW);
digitalWrite(3,LOW);
digitalWrite(4,LOW);
digitalWrite(5,LOW);


}

void loop(){
   int count = 2;
  if(digitalRead(8) == LOW){
    
    while(count > 0){
      forward();
      delay(1000);
      backward();
      delay(1000);
      count--;
    }
    
  }
  
  
}

void forward(){
  
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    
    while(digitalRead(9) == HIGH);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    
    digitalWrite(4,LOW);
    digitalWrite(5,LOW); 
}

void backward(){
  
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    
    while(digitalRead(10) == HIGH);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    
    digitalWrite(4,LOW);
    digitalWrite(5,LOW); 
}


