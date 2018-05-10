#include<SoftwareSerial.h>
#include<Servo.h>

#define NUMREADINGS 30 // raise this number to increase data smoothing
#define THRESHOLD 700
#define MOTORTIME 200
Servo servo1,servo2;

int senseLimit = 15; // raise this number to decrease sensitivity (up to 1023 max)
int probePin = 0; // analog 5
int val = 0; // reading from probePin

// variables for smoothing

int readings[NUMREADINGS];                // the readings from the analog input
int index = 0;                            // the index of the current reading
int total = 0;                            // the running total
int average = 0;                          // final average of the probe reading
int oldaverage = 0;                          // final average of the probe reading


long int currenttimer = 0;
long int previoustimer = 0;
int timeout =0;

bool motorflag = false;



//CHANGE THIS TO affect the speed of the updates for numbers. Lower the number the faster it updates.
int updateTime = 40;


void setup() {

   Serial.begin(9600);  // initiate serial connection for debugging/etc
 
   servo1.attach(8);
   servo2.attach(9);
 
  for (int i = 0; i < NUMREADINGS; i++){
    readings[i] = 0;                      // initialize all the readings to 0
  }
pinMode(13,OUTPUT);
digitalWrite(13,LOW);

  servo1.write(60);
  servo2.write(90);
}



 void loop() {

   val = analogRead(probePin);  // take a reading from the probe

  if(val >= 1){                // if the reading isn't zero, proceed
    val = constrain(val, 1, senseLimit);  // turn any reading higher than the senseLimit value into the senseLimit value
    val = map(val, 1, senseLimit, 1, 1023);  // remap the constrained value within a 1 to 1023 range

    total -= readings[index];               // subtract the last reading
    readings[index] = val; // read from the sensor
    total += readings[index];               // add the reading to the total
    index = (index + 1);                    // advance to the next index

    if (index >= NUMREADINGS)               // if we're at the end of the array...
      index = 0;                            // ...wrap around to the beginning

    average = total / NUMREADINGS;          // calculate the average
   
   Serial.println(average); // use output to aid in calibrating
//delay(updateTime);
  CheckThreshold(average,oldaverage); 

   oldaverage = average;

  }
  
}


void CheckThreshold(int Sensor_val,int oldavg){
 long int currenttimer = millis();
  if(Sensor_val > THRESHOLD){
   motorflag = true;
  }

  if(motorflag == true){
    Serial.println("motor1");
    digitalWrite(13,HIGH);
    servo2.write(70);
    if(timeout > MOTORTIME){
     servo1.write(180);

     Serial.println("motor2");
     if(timeout > MOTORTIME+MOTORTIME){
       motorflag = false;
     }
    }
 
}
 else if(motorflag == false){
    servo1.write(60);
    servo2.write(90);
    digitalWrite(13,LOW);
    Serial.println("else");
    timeout = 0;
  }

  timeout += currenttimer - previoustimer;
  previoustimer = currenttimer;
  
}

