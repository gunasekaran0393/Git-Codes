#define NUMREADINGS 40 // raise this number to increase data smoothing

int senseLimit = 15; // raise this number to decrease sensitivity (up to 1023 max)
int probePin = 0; // analog 5
int val = 0; // reading from probePin

// variables for smoothing

int readings[NUMREADINGS];                // the readings from the analog input
int index = 0;                            // the index of the current reading
int total = 0;                            // the running total
int average = 0;                          // final average of the probe reading

//CHANGE THIS TO affect the speed of the updates for numbers. Lower the number the faster it updates.
int updateTime = 10;


void setup() {

  Serial.begin(9600);  // initiate serial connection for debugging/etc

  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;                      // initialize all the readings to 0

  pinMode(13, OUTPUT);

  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  digitalWrite(13,LOW);
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
//    delay(updateTime);
 if(average > 600){
  digitalWrite(13,HIGH);
  Trigger_Spark();
 }
 else{
  digitalWrite(13,LOW);

 }
 }
 
 }

void Trigger_Spark(){
  int count = 100;
  
  while (count>0) {
   digitalWrite(3,HIGH);
   digitalWrite(2,LOW);
   delay(10);
   digitalWrite(3,LOW);
   digitalWrite(2,HIGH);
   delay(10);
   count--;
  }

}

