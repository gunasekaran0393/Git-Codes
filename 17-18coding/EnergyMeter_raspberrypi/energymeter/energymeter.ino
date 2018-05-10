void setup(){
  Serial.begin(9600);
}  

void loop(){
  
  int load_1 = analogRead(0);
  int load_2 = analogRead(1);
  
  String s ="";
  
  if(load_1 > 20){
    load_1 -= 20;
   
  }
  if(load_2 > 20){
     load_2 -= 20;
  }
  
  s += load_1/2;
  s += '+';
  s += load_2;
  s +='\n';
//  Serial.print("Load1:");
//  Serial.println(load_2);
//  

Serial.print(s);
delay(1000);
}
