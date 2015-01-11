//This code is modified from the DHTester sketch Adafruit puts out, and the Sweep sketch that Arduino does. 
//The effect is a robot that does not like people to be nearby. if you breathe on it, it will run away.

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include <Servo.h> 

boolean scared = true;

Servo myservo;
int pos = 0; 

int sensorPin = A0;

//Variables for determining increase or decrease, which appears to be very steady with this sensor.
int lastLightVal = 0;
int ledPin = 13;
// make sure that the data stream is consistent before being able to be aroused.

int light;

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  myservo.attach(9);

  lastLightVal = analogRead(sensorPin);
  pinMode(ledPin,OUTPUT);
}


void loop() {
  // Wait half a second between measurements.
  delay(500);

  light = analogRead(sensorPin);
  Serial.println (light);

  if (light > lastLightVal && (light-lastLightVal) > 50 ){
    Serial.println("triggered");
    if (scared == false){
      digitalWrite(ledPin,HIGH);
      for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
      } 
      scared =true;
      Serial.println("ran away A");
    } 
    else {
      digitalWrite(ledPin,HIGH);
      for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
      {                                
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
      }
      scared =false; 
       Serial.println("ran away B");
    }
    delay (100);
  }
  
   lastLightVal = light;
  //read light
  
//  if (h>30){
//    digitalWrite(ledPin,HIGH);
//  } else {
//    digitalWrite(ledPin,LOW);
//  }  
}

