/*
The code was writen by Papadopoulos Ioannis on the 14th of December 2022.
Its main use is for academic purposes at the Department of Informatics and 
Telecommunications of University of Ioannina.

This code was designed and compiled in TinkerCAD(using Arduino UNO R3)

Implement a circuit using an Ultrasonic sensor HC-SR04, a Photoresistor, a Piezo and a 
bunch of LEDs. In this project we're utilizing a system called Smart Green House.

Firstly, it detects for the appropriate lighting inside a greenhouse. If the
value returned by the photoresistor is less than 930, the 5 main LED lights will
turn on, giving the appropriate lighting to all the plants inside the greenhouse.

Then, it checks for any obstacles using the HC-SR04 sensor. Depending on
the distance from the obstacle, the RGB LED will change colors and the
Piezo sensor will change its beeping intervals.

If the user types in 0 at any point, the program's constant execution will stop.
*/

// (constant) variable declarations
const int ledRGB[3] {10, 9, 8}; // R=pin10 : G=pin9 : B=pin8
const int lights[6] {6, 5, 4, 3, 2}; // lights

const int piezo = 7; //its obvious isnt it?
const int photores = A0; //photo resistor pin

const int echo = 11; //echo pin for HC-SR04
const int trig = 12; //trigger pin for HC-SR04
long duration;
int distance;

// setup program
void setup() {
  Serial.begin(9600); //start serial
  for(int i=0; i<6; i++) pinMode(lights[i], OUTPUT); //initialize all light pins to OUTPUT
  for(int i=0; i<3; i++) pinMode(ledRGB[i], OUTPUT); //initialize all RGB pins to OUTPUT
  
  pinMode(trig, OUTPUT); //initialize trigger pin for HC-SR04
  pinMode(echo, INPUT); //initialize echo pin for HC-SR04
  
  Serial.println("Program is now running. Type in 0 to stop program execution.");
}

// run repeatedly
void loop() {
  
  //interrupt to check if the user has typed something in Serial input
  //then checks if whatever the user typed is equal to the character 0
  //if that's the case then the program stops running
  if(Serial.available()>0) {
    String usr_input = Serial.readString();
    if (usr_input == "0") {
      Serial.println("User has terminated program execution."); 
      delay(40); //this is added to allow time for the message above to be printed
      exit(0);
    }
  }
  
  int value = analogRead(photores); //light value returned by the photo resistor pin
  
  //check if light value is less than 930 (to turn on the lights)
  if (value < 930) {
    toggleLights(true);
  } else {
    toggleLights(false);
  }
  
  digitalWrite(trig, LOW); //set the trigger pin to LOW just in case
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH); //start transmitting ultrasonic soundwaves
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); //stop transmitting 

  duration = pulseIn(echo, HIGH); //start receiving ultrasonic soundwaves
  
  distance = duration * 0.034 / 2; //formula to calculate the distance 
  
  //set RGB LED to different colors based on the distance
  //make the piezo go beep beep and send messages to the user
  if (distance <=25) {
    setColor(255, 0, 0);
    beep(250);
    Serial.print("There is an object ");
    Serial.print(distance);
    Serial.println("cm away.");
  } else if (distance<=50) {
    setColor(255, 25, 0);
    beep(500);
    Serial.print("There is an object ");
    Serial.print(distance);
    Serial.println("cm away.");
  } else {
    setColor(0, 255, 0);
    beep(750);
    Serial.print("There is an object ");
    Serial.print(distance);
    Serial.println("cm away.");
  }
}

// function that turns the lights on if the value 
// given is true, meaning that the light level is less 
// than 930. Keeps the lights off for all other cases.
void toggleLights(bool value){
  if(value){
    for(int i=0; i<6; i++) digitalWrite(lights[i], HIGH);
  } else {
    for(int i=0; i<6; i++) digitalWrite(lights[i], LOW);
  }
}

// function that allows the user to select RGB colors for
// the RGB LED. ex (255, 0, 0) gives color red.
void setColor(int r, int g, int b){
  analogWrite(ledRGB[0], r);
  analogWrite(ledRGB[1], g);
  analogWrite(ledRGB[2], b);
}

// function that simulates a beeping sound based
// on the intervals (in ms) given by the programmer
void beep(int interval){ 
  tone(piezo, 1200);
  delay(interval);
  noTone(piezo);
  delay(interval);
}
