/*
 Jakob Parpart
 10/12/2021
 Coach L
 Electrical Engineering Honors
 GHS 2021/2022

  When uploaded, the program runs in a loop, alternating between the two pairs of LED's. 
  Blinking them repeatedly on and off with a 200ms delay.
  Pair 1 blinks 5 times at a frequency of 200ms, then switches to Pair 2 which also blinks 5 times at a frequency of 200ms.
*/

// the setup function runs once when you press reset or power the board
void setup() {                   // function declaration
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT); // sets up the pin
  pinMode(12,OUTPUT);           // sets up the pin
}                              // end of setup

// the loop function runs over and over again forever
void loop() {                          // function declaration
  for(int i = 0; i < 5; i++) {         // for loop declaration
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a 200ms
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(200);                       // wait for 200ms
  }                                     // end of for loop 

  for(int i = 0; i < 5; i++) {   // for loop declaration
    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for 200ms
    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
    delay(200);                // wait 200ms
  }                            // end of for loop
}                              //end of loop


