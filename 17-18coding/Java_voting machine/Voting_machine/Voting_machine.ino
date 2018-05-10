void setup(){
 Serial.begin(9600);
pinMode(2,INPUT_PULLUP);
pinMode(3,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);
pinMode(6,INPUT_PULLUP);
pinMode(7,INPUT_PULLUP);
pinMode(8,INPUT_PULLUP);
pinMode(9,INPUT_PULLUP);
pinMode(10,INPUT_PULLUP);
pinMode(11,INPUT_PULLUP);

pinMode(12,OUTPUT);

pinMode(13,OUTPUT);

digitalWrite(13,LOW);

digitalWrite(12,LOW);

}

void loop(){
  
  char c;
 int  count = 0;
  if(Serial.available()>0){
   
   c = Serial.read();
  
    if(c == 'a'){
      while(count < 25){
       digitalWrite(12,HIGH);
       delay(100);
       digitalWrite(12,LOW);
       delay(100);
       count++;
      }
    } 
  }
  
  int flag = 0;
  if(digitalRead(2) == LOW){
    delay(50);
    if(digitalRead(2) == LOW){
    Serial.println("1");
    flag = 1;
    }
  }
  if(digitalRead(3) == LOW){
    delay(50);
    if(digitalRead(3) == LOW){
    Serial.println("2");
    flag = 1;
    }
  }
  if(digitalRead(4) == LOW){
    delay(50);
    if(digitalRead(4) == LOW){
    Serial.println("3");
    flag = 1;
    }
  }
  if(digitalRead(5) == LOW){
    delay(50);
    if(digitalRead(5) == LOW){
    Serial.println("4");
    flag = 1;
    }
  }
  if(digitalRead(6) == LOW){
    delay(50);
    if(digitalRead(6) == LOW){
    Serial.println("5");
    flag = 1;
    }
  }
  if(digitalRead(7) == LOW){
    delay(50);
    if(digitalRead(7) == LOW){
    Serial.println("6");
    flag = 1;
    }
  }
  if(digitalRead(8) == LOW){
    delay(50);
    if(digitalRead(8) == LOW){
    Serial.println("7");
    flag = 1;
    }
  }
  if(digitalRead(9) == LOW){
    delay(50);
    if(digitalRead(9) == LOW){
    Serial.println("8");
    flag = 1;
    }
  }
  if(digitalRead(10) == LOW){
    delay(50);
    if(digitalRead(10) == LOW){
    Serial.println("9");
    flag = 1;
    }
  }
  if(digitalRead(11) == LOW){
    delay(50);
    if(digitalRead(11) == LOW){
    Serial.println("10");
    flag = 1;
    }
  }
  
  if(flag == 1){
    delay(2000);
  }
  
}
