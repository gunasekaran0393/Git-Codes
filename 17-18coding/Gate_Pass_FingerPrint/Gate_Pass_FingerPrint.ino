#include<SoftwareSerial.h>

SoftwareSerial serial(2,3);

#define TIME_OUT 60000

char *Name[] = {"Give finger","V.Ramya","A.Riswana","C.P Aadelin","V.Aishwarya","G.Lekha","L.Lokeswari","T.Tharaghai","E.Emalda Jenifer", "A.Suvalakshmi","S.Suwetha" };
char *No[]={"","14JEIT220","14JEIT213","14JEIT234","14JEIT141","14JEIT241","14JEIT137","14JEIT169","14JEIT115","15JEME117","13JEBT118"};

long int time_out =0;
long int previous =0;
int count[20];

String s="";
int id = 0;
bool flag =false;
bool time_flag =false;


void setup(){
  
 Serial.begin(9600);
 serial.begin(9600);
 
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(13,OUTPUT);
 
 digitalWrite(8,LOW);
 digitalWrite(9,LOW);
 
 memset(count,0,sizeof(count));
 
}

void loop(){
  
   long int current= millis();

  
   while (serial.available() > 0) {
     
     id = serial.parseInt();
     
     int ret = serial.parseInt();//dumy read
     
     int ret1 = serial.parseInt();//dumy read
     
//     Serial.println(id);
    

     if((id ==21)||(id ==20)){
       id = 4;
     }
     
     Parse_Name(id);
     
     if((id >0)&&(id<=10)){
       
       digitalWrite(8,HIGH); //buzzer
       delay(50);
       digitalWrite(8,LOW);
       
       if(count[id] !=0){
         count[id] = 0;
       }
       else{
         count[id] = 1;
       }
//       Serial.print("id:");
//       Serial.println(count[id]);
       flag = true;
       
       
     }
     
     
   }
   
  if((time_out >= TIME_OUT)&&(flag == true)){
     time_out = 0;
     flag = false;
     time_flag = true;
//     Serial.println("timeout");
       digitalWrite(8,HIGH); //buzzer
       delay(1000);
       digitalWrite(8,LOW);
//     if(count[id] == 1){
//       
//      
//      Serial.println("timeOut");//send late alert
//        s +="NAME: ";
//        s += Name[id];
//        s +="ID: ";
//        s += No[id];
//        s +=" Late Entry to the Hostel";
//        
//       Send_Message(s);
//     }
//     else{
//         Serial.println("ok");
//       
//     }
  }

   else{
  
         time_out += current - previous;
         previous = current;
   
   }
  
}


void Parse_Name(int id){
  
  String s = "";

 
// Serial.println(s);
  
  if (count[id] == 0)
  {
        s +="NAME: ";
        s += Name[id];
        s +=" ID: ";
        s += No[id];
        s +=" Left the Hostel";
  
        Send_Message1(s);
        delay(4000);
        Send_Message2(s);
        delay(4000);
        Send_Message3(s);
        delay(4000);
        time_out = 0;
  }
  
  else if ((count[id] == 1)&&(time_flag == false)){
    
        time_flag = 0;
        s +="NAME: ";
        s += Name[id];
        s +=" ID: ";
        s += No[id];
        s +=" Came on time to the Hostel";
        Send_Message1(s);
        delay(4000);
        Send_Message2(s);
        delay(4000);
        Send_Message3(s);
        delay(4000);
  }
  
  else if ((count[id] == 1)&&(time_flag == true)){
    
        time_flag = 0;
        s +="NAME: ";
        s += Name[id];
        s +=" ID: ";
        s += No[id];
        s +=" Came late to the Hostel";
        Send_Message1(s);
        delay(4000);
        Send_Message2(s);
        delay(4000);
        Send_Message3(s);
        delay(4000);
  }
    
    
}


void Send_Message1(String s)
{
 
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+919791677274\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println(s);// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
//  Serial.println("Sent_message");
}
void Send_Message2(String s)
{
 
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+918870069366\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println(s);// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
//  Serial.println("Sent_message");
}
void Send_Message3(String s)
{
 
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+917826852794\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println(s);// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
//  Serial.println("Sent_message");
}

