#include<Servo.h>
Servo serL;
Servo serR;

#define trigPin 5
#define echoPin 4
long duration;
int distance;

char SerialData;

void setup() {
  // put your setup code here, to run once:
  serL.attach(7);
  serR.attach(6);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void Sonic(){
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance= duration*0.034/2;
  
  
  delay(50);
}

void loop() {
  if(Serial.available() > 0){
      SerialData = Serial.read();
      Serial.print(SerialData);
    }

  if(SerialData == '1'){
      Sonic();
      if(distance < 10){
        serR.write(180);
        serL.write(0);
      }
    }

    if(SerialData == '0'){
        serR.write(90);
        serL.write(90);
      }
}
