/*
  Tutorial 7 & 8 Modified Light Sensitive Gate
  Jakob Kay Parpart
  GHS 2021/2022
  Electrical Engineering Honors
  Coach L.
 
  This program makes use of a photoresistor, servo and a push button.
  The photoresistor is used to detect the light, depending on the light that it takes in
  determines how far the servo will turn to either direction.
  This is supposed to mimic an automated gate. Once the button is pushed, If there is light, the gate will open.
  If the button is pushed but no light, the servo will stay "closed"
  This could be used in your everyday life, say your driving up to your property,
  to open the gate you would usually have to get out and manually open it. Or you have a remote.
  But what if the gate malfunctions and opens even if you havent pressed the remote. This would leave your house vulnerable.
  Using this you have to push the button, then when driving up to the gate,
  the photoresistor will sense the light from your headlights. THis will open the gate.
  Once you have passed through, the gate will close after it doesn't sense light from your headlights or tailights.
 
  Board Setup:
  5V pin -> positive strip on breadboard
  GND pin -> negative strip of breadboard
  DIO 9 -> Input side of servo
  Positive strip -> Middle pin of servo
  GND strip -> GND pin of Servo
  DIO 2 -> positive leg of push button
  GND strip -> Negative leg of push button
  GND strip -> 330ohm resistor -> Photoresistor
  A0 -> Analog leg of Photoresistor
  GND strip -> Negaive leg of Photoresistor
*/

#include <Servo.h> //add servo

Servo myservo; //sets up servo
int button = 2; // assigns pin to button
int val; //sets up the value
int photocell; // sets up the photoresistor
volatile int buttonState = 0; // used to store the button state

void setup() { // start of setup
  myservo.attach(9); //declares what pin the servo is assigned to
  pinMode(button, INPUT); // sets button to input
  attachInterrupt(digitalPinToInterrupt(2), buttonISR, RISING); //function call, ISR initialization
  Serial.begin(9600); //sets up serial monitor
} //end of void

void buttonISR () { buttonState++; } // ISR function declaration and definition

void loop() { //start of void loop

  /* FLUSH SERIAL MONITOR */
  for(int i = 0; i < 20; i++) { // for loop
    Serial.println(); // newline
  } // end of for loop
  
  /* READ AND MANIPULATE VALUES */
  
  photocell=analogRead(A0); //sets up analog pin to Photoresistor
  
  Serial.print("Photoresistor Value: "); // assertment (escape sequences to make it look nicer)
  Serial.println(photocell); // assertment
  
  photocell = map(photocell,0,1023,0,180); // maps analog value to servo range

  /* UPDATE BUTTON STATE */
  if(buttonState > 2) { // if buttonState is greater than 2
    buttonState = 0; // set buttonState to linked
  } // end of if statement

  /* UPDATE AND WRITE TO OUTPUTS */
 
  Serial.print("Mode: "); // assertment
  
  switch (buttonState) {
    case 0: /* SERVO IS LINKED TO LED*/
      Serial.println("Linked"); // assertment
      myservo.write(photocell); // update servo motor position
      break; // exit case
      
    case 1: /* SERVO IS CLOSED */
      Serial.println("Closed"); // assertment
      myservo.write(0); // update servo motor position
      break; // exit case
      
    case 2: /* SERVO IS OPEN */
      Serial.println("Open"); // assertment
      myservo.write(180); // update servo motor position
      break; // exit case
      
    default: // if for some reason it goes past the value
      Serial.println("Inside default case???"); // assertment
      break; // exit case
  } // end of switch case

  delay(500); // delay
} // end  of program
