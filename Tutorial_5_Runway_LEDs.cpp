/****************************************************************************************************************************************************************************
Tutorial 5 Modified Runway Array                                                                                                                                           **
Jakob Parpart                                                                                                                                                              **
GHS 2021/2022                                                                                                                                                              **
Electrical Engineering Honors                                                                                                                                              **
Coach L.                                                                                                                                                                   **
This program makes use of 10 LEDS total. Along with a potentiometer.                                                                                                       **
3 red LEDS, 3 yellow LEDS, 3 green LEDS and one blue LED                                                                                                                   **
Twisting the potentiometer will turn on the leds in order from the 1st red LED to the last green one.                                                                      **
When the potentiometer is turned to max all the LEDS will b on along with the blue one.                                                                                    **
The blue LED is just to show that the potentiometer is turned all the way.                                                                                                 **
                                                                                                                                                                           **
Board Setup:                                                                                                                                                               **
DIO -> 330ohm Resistor -> Red LED                                                                                                                                          **
DIO -> 330ohm Resistor -> Red LED                                                                                                                                          **
DIO -> 330ohm Resistor -> Red LED                                                                                                                                          **
DIO -> 330ohm Resistor -> Yellow LED                                                                                                                                       **
DIO -> 330ohm Resistor -> Yellow LED                                                                                                                                       **
DIO -> 330ohm Resistor -> Yellow LED                                                                                                                                       **
DIO -> 330ohm Resistor -> Green LED                                                                                                                                        **
DIO -> 330ohm Resistor -> Green LED                                                                                                                                        **
DIO -> 330ohm Resistor -> Green LED                                                                                                                                        **
DIO -> 330ohm Resistor -> Blue LED (to show max)                                                                                                                           **
                                                                                                                                                                           **
GND -> Ground strip on Breadboard                                                                                                                                          **
GND -> Ground leg of Potentiometer                                                                                                                                         **
5V -> Positive leg of Potentiometer                                                                                                                                        **
A0 -> Analog leg of LED                                                                                                                                                    **
                                                                                                                                                                           **
*Note*                                                                                                                                                                     **
I used the 5V pin instead of the 3.3V because the 3.3V didn't have nearly enough power                                                                                     **
to light all 10 LEDs, it would only light the red and yellows leaving the green and blues                                                                                  **
with no power.                                                                                                                                                             **
****************************************************************************************************************************************************************************/



const int analogPin = A0;   // the pin that the potentiometer is attached to
const int ledCount = 10;    // the number of LEDs in the bar graph

int ledPins[] = { //declares each pin to an LED
 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 // an array of pin numbers to which LEDs are attached
};   // end of LED pin declaration

void setup() { //beginning of setup
  Serial.begin(9600); //start serial monitor
  while(!Serial); //wait till usb device is recognized
  for (int led : ledPins) { // loop over the pin array and set them all to output:
    pinMode(led, OUTPUT);// setting the pinmode as output
  }//end of for loop
  //Serial.println("End of Setup"); //serial print for end of setup
}// end of void setup

void loop() { //beginning of void loop
  // read the potentiometer:
  int sensorReading = analogRead(analogPin); //potentiometer analog pin setup
  // map the result to a range from 0 to the number of LEDs:
  int ledLevel = map(sensorReading, 0, 1023, 0, ledCount); //setting potentiometer reading to 0-1023

  // loop over the LED array:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) { //start of for loop
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed < ledLevel) { //start of if statement
      digitalWrite(ledPins[thisLed], HIGH); //setting LED to high
      
    }//end of if statement
    
    else {// start of else statement
      digitalWrite(ledPins[thisLed], LOW); // turn off all pins higher than the ledLevel:
    } //end of else
    
  } //end of for loop
    Serial.print("led Level = "); //serial monitor printout
    Serial.println(ledLevel); //printing out LED level
}//end of whole program
