 /*
Tutorial 9 + 10 Home Security System
Jakob Kay Parpart
GHS 2021/2022
Electrical Engineering Honors
Coach L.
This program makes use of a laser, photoresistor, piezo and 4 LEDs and a button.
The button has 3 states, on, reset, and off. 
There are two LED's to let you know whether the system is armed or disarmed.
Once you turn on the system, the laser will shine at the photoresistor.
Once the beam is interrupted by something passing by, the piezo will sound and the LED's will blink.
To turn off the piezo and lights you simply press the button once to reset the system.
Board Setup:
DIO 4-> Red LED
330ohm resistor from ground to negative leg of Red LED
DIO 5-> Green LED
330 ohm resistor from GND to negative leg of Green LED
DIO 6 -> positive side of button
DIO 7 -> Blue LED
330 ohm resistor from GND to negative leg of Blue LED
DIO 8 -> Red LED
330 ohm resistor from GND to negative leg of Red LED
GND strip -> negative side of piezo
DIO 12 -> positive of piezo
A0 -> photoresistor
GND -> 330 ohm resistor -> photoresistor
positive strip -> photoresistor
GND strip -> negative pin of laser
3.3V pin -> positive pin of laser
*/
const int triggeredLED = 7; //declare led pin (red)
const int triggeredLED2 = 8; //declare led pin (blue)
const int RedLED = 4; //declare led pin        
const int GreenLED = 5; //declare led pin      
const int inputPin = A0; //declare analog pin     
const int speakerPin = 12; //declare piezo pin  
const int armButton = 6; //declare push button     

boolean isArmed = true; //arm the system      
boolean isTriggered = false; //trigger the system
int buttonVal = 0; //button value           
int prev_buttonVal = 0; //button value     
int reading = 0; //reading value             
int threshold = 0; //threshold value           


const int lowrange = 2000; //piezo frequency (lowrange)   
const int highrange = 4000; //piezo frequency (highrange)

void setup(){ //setup function
  
  Serial.begin(9600);
  pinMode(triggeredLED, OUTPUT); //set led as output (red)
  pinMode(triggeredLED2, OUTPUT); //set led as output (blue)
  pinMode(RedLED, OUTPUT); //set red led as output
  pinMode(GreenLED, OUTPUT); //set green led as output
  pinMode(armButton, INPUT); //button that arms the system
  digitalWrite(triggeredLED, HIGH); //red led on
  delay(500); // 500ms delay
  digitalWrite(triggeredLED, LOW); //red led low

   calibrate(); //calibrates the system
   setArmedState(); //determines whether the system is armed or not
} //end of setup

void loop(){ //start of loop

 
  reading = analogRead(inputPin); //sets analog as input pin

 
  int buttonVal = digitalRead(armButton); //digital read arm button
  if ((buttonVal == HIGH) && (prev_buttonVal == LOW)){ //
    setArmedState();
    delay(500);
  }

  if ((isArmed) && (reading < threshold)){ //if its armed and reading below threshold
    isTriggered = true;
    Serial.println("INTRUDER ALERT"); //serial monitor printout
  } //it will trigger

  if (isTriggered){ //if statement

     for (int i = lowrange; i <= highrange; i++) //for loop
    { //start of for
      tone (speakerPin, i, 250); //play note
    } //end of for
   
    for (int i = highrange; i >= lowrange; i--) //for loop
    { //start of for
      tone (speakerPin, i, 250); //play note
    } //end of for

 
    digitalWrite(triggeredLED, HIGH); //red led high
    delay(50); //50ms delay
    digitalWrite(triggeredLED, LOW); //red led low
    delay (50); //50ms delay
    digitalWrite(triggeredLED2, HIGH); //blue led high
    delay (50); // 50ms delay
    digitalWrite(triggeredLED2, LOW); //blue led low
    delay (50); //50ms delay
    } //end of for

  delay(20); //20ms delay
} //end of if loop

void setArmedState(){ //start of void

  if (isArmed){ //start of if
    digitalWrite(GreenLED, HIGH); //green led high
    digitalWrite(RedLED, LOW); //red led low
    isTriggered = false; //not triggered
    isArmed = false; //not armed
    Serial.println("System is unarmed"); //serial monitor printout
  } else { //else statement
    digitalWrite(GreenLED, LOW); //green led low
    digitalWrite(RedLED, HIGH); //red led high
    tone(speakerPin, 220, 125); //play tone
    delay(200); //200ms delay
    tone(speakerPin, 196, 250); //play tone
    Serial.println("System Activated"); //serial monitor printout
    isArmed = true; //is armed
  } //end of if
} //end of else

void calibrate(){ //calibrate

  int sample = 0; //set sample             
  int baseline = 0; //set baseline            
  const int min_diff = 200; //difference 
  const int sensitivity = 50; //baseline value
  int success_count = 0; //count
  
  digitalWrite(RedLED, LOW); //red led low
  digitalWrite(GreenLED, LOW); //green led low

  for (int i=0; i<10; i++){ //for loop
    sample += analogRead(inputPin); //analog read input
    digitalWrite(GreenLED, HIGH); //green high
    delay (50); //50ms delay
    digitalWrite(GreenLED, LOW); //green led low
    delay (50); //50ms delay
  } //end of for loop

  do //do this:
  { //start of do
    sample = analogRead(inputPin); //analog read input    

    if (sample > baseline + min_diff){ //start of if
      success_count++; //success counter
      threshold += sample; //keeps track of samples

      digitalWrite(GreenLED, HIGH); //green led high
      delay (100); //100ms delay                    
      digitalWrite(GreenLED, LOW); //green led low
      delay (100); //100ms delay                    
    } else { //start of else
      success_count = 0; //success count             
      threshold = 0; //threshold count
    } //end of else

  } while (success_count < 3); //start of while loop

  threshold = (threshold/3) - sensitivity; //divide threshold by 3

  tone(speakerPin, 196, 250); //play tone
  delay(200); //200ms delay
  tone(speakerPin, 220, 125); //play tone
} //end of while
