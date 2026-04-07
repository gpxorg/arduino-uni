/*
The code was writen by Papadopoulos Ioannis on the 31st of October 2022.
Its main use is for academic purposes at the Department of Informatics and 
Telecommunications of University of Ioannina.

This code was designed and compiled in TinkerCAD(using Arduino UNO R3)

Write a program that simulates a system lock with 3 buttons. Each button
is assigned to a number (1, 2 or 3). The user should have the ability to click on
the buttons in any order @ wishes. Only when the buttons are pressed in
the correct order should the green LED light up. As for any other case, the red LED
will turn on. The combination is 3 digits long.
*/


// Store the pins that are used (buttons)
const int btn1 = 2; // pin 2
const int btn2 = 3; // pin 3
const int btn3 = 4; // pin 4

// Store the pins that are used (LEDs)
const int success = 5;
const int failure = 6; 

int combo[] = {3, 1, 2}; // Correct combination stored here

int input[3]; // User input stored here

int n=0; //counter to keep track of array input cells

// Set-up the program
void setup() 
{
  // start Serial and print a message
  Serial.begin(9600);
  Serial.println("Click on the buttons in the correct order.");
  
  /* Initializing each pin to a specific type (buttons)
     ::INVERSED STATE::
     INPUT_PULLUP is used to add resistance while keeping the input stable
     this is going to inverse the states of the buttons, meaning: when a 
     button would be LOW, its now HIGH and when it would be HIGH, its now LOW. 
  */
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  
  //Initializing each pin to a specific type (LEDs)
  pinMode(success, OUTPUT);
  pinMode(failure, OUTPUT);
}

// run repeatedly
void loop() {
  if (digitalRead(btn1) == LOW) { //check if button 1 has been pressed(see INVERSED STATE)
    Serial.println("Button 1 has been pressed."); 
    checkEntry(1); //call function passing it a 1
    delay(250); //delay to avoid false inputs
  } 
  else if (digitalRead(btn2) == LOW) { //check if button 2 has been pressed
    Serial.println("Button 2 has been pressed.");
    checkEntry(2); //call function passing it a 2
    delay(250); //delay to avoid false inputs
  }
  else if(digitalRead(btn3) == LOW) { //check if button 3 has been pressed
    Serial.println("Button 3 has been pressed.");
    checkEntry(3); //call function passing it a 3
    delay(250); //delay to avoid false inputs
  }
}

// function that inserts user input in an array to compare
void checkEntry(int number) {
  if (input[n] != 0) { //if slot n of the array has a number stored
    n++; //go to the next slot 
    checkEntry(number); //call the function again
  } else if (input[n] == 0) { //if slot n of the array doesnt have a number stored
    input[n] = number; //insert the number
  }
  if (n >=2){ //if the array is full
    isCorrect(); //call function that checks if input matches the correct combination
  }
}

// checks if the code entered matches the one correct combination
void isCorrect(){
  bool temp = true; // used to check if all digits entered are correct
  int i; // declared i here because of errors
  for(i=0; i<3; i++){ //if atleast one input is wrong, temp will become false
    if(input[i] != combo[i]){
      temp = false;
      break; // break out of the loop if at least one is false
    }
  }
  if (temp == false) { //if combination doesnt match user input
    digitalWrite(failure, HIGH);
    delay(1000); 
    digitalWrite(failure, LOW);
  } else { //combination matches user input
    digitalWrite(success, HIGH);
    delay(1000);
    digitalWrite(success, LOW);
  }
}
