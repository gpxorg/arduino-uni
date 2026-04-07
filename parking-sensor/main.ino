/*
The code was writen by Papadopoulos Ioannis on the 12th of November 2022.
Its main use is for academic purposes at the Department of Informatics and 
Telecommunications of University of Ioannina.

This code was designed and compiled in TinkerCAD(using Arduino UNO R3)

Implement a circuit using an Ultrasonic sensor HC-SR04 that will calculate the distance 
between the sensor and the objects in front of it. The circuit will contain 9 LEDs all of which
will blink depending on how close an object is to the Ultrasonic sensor.

Add a Piezo sensor and give it smaller delays between states tone() and noTone() as the distance 
of an object gets smaller.

(Parking Sensor simulator)
*/

// Constant variables for connected sensors
const int echoPin = 2; //for HC-SR04
const int trigPin = 3; //for HC-SR04
const int buzzPin = 4; //for Piezo

// Constant variables for LEDs (according to the table provided)
const int led1 = 7;
const int led2 = 6;
const int led3 = 5;
const int led4 = 10;
const int led5 = 9;
const int led6 = 8;
const int led7 = LED_BUILTIN;
const int led8 = 12; 
const int led9 = 11;

// Used for HC-SR04
long duration;
int distance;

void setup() {
  Serial.begin(9600); //start serial
  
  // Initializing sensor pins
  pinMode(echoPin, INPUT); //set hc-sr04 echo pin as INPUT
  pinMode(trigPin, OUTPUT); //set hc-sr04 trigger pin as OUTPUT
  pinMode(buzzPin, OUTPUT); //set Piezo pin as an OUTPUT
  
  //Initializing all LEDs
  for(int i=5; i<14; i++){ // set every LED as OUTPUT(used a for loop instead of
  	pinMode(i, OUTPUT);    // repeating the same command 9 times for all LEDs)
  }
  
  Serial.println("Loading Parking Sensor simulator...");
}

void loop() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  
  
  digitalWrite(trigPin, HIGH); // Sends sound waves for 10 μs
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); // Stops sending sound waves
  
  // Stores the amount of time it took for the sound wave
  duration = pulseIn(echoPin, HIGH); //to reach an obstacle and return back to the sensor
  
  // Formula to calculate the distance
  distance = duration * 0.034 / 2;
  
  blinkLED(distance); //Call function and pass it distance
}

// Function that sets all LEDs off
void setLow(){
  for(int i=5; i<14; i++){ 
  	digitalWrite(i, LOW); //for every LED set its value to LOW
  }
}

// Function that toggles the Piezo buzzer on and off
// to a specific rate given by the integer n
void beep(int n){
  tone(buzzPin, 1200, n); // emit sound for n ms(1kHz) 
  delay(n); // delay for n ms
  noTone(buzzPin); // stop sound
  delay(n); // delay for n ms
}

// Function that takes the distance of the soundwave as input
// and turns on the correct LED according to the distance table provided
void blinkLED(int d){
  setLow(); // Call function to set all LEDs off
  if(d>=1 && d<=5) {
  	digitalWrite(led1, HIGH); //turn LED on
    beep(10); //beep in intervals of 10ms
  } else if(d<=7){
  	digitalWrite(led2, HIGH); //turn LED on
    beep(30); //beep in intervals of 30ms
  } else if(d<=8){
  	digitalWrite(led3, HIGH); //turn LED on 
    beep(60); //beep in intervals of 60ms
  } else if(d<=9){
    digitalWrite(led4, HIGH); //turn LED on
    beep(90); //beep in intervals of 90ms
  } else if(d<=10){
    digitalWrite(led5, HIGH); //turn LED on 
    beep(130); //beep in intervals of 130ms
  } else if(d<=11){
    digitalWrite(led6, HIGH); //turn LED on
    beep(160); //beep in intervals of 160ms
  } else if(d<=15){
    digitalWrite(led7, HIGH); //turn LED on 
    beep(220); //beep in intervals of 220ms
  } else if(d<=25){
    digitalWrite(led8, HIGH); //turn LED on 
    beep(310); //beep in intervals of 310ms
  } else {
    digitalWrite(led9, HIGH); //turn LED on
    beep(500);
  }
}
