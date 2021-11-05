/*
Tutorial 2 BLE
Jakob Parpart
11/4/2021
GHS 2021/2022
Electrical Engineering Honors
Coach L.

This Program makes use of a Piezo buzzer and a RGB LED along with the bluetooth function of the Arduino board.
Using the nRF connect app on your cellphone, you can connect to the arduino, then you are able to navigate to the bottom right of the screen, press the "up"
arrow and type in any number between 1 and 4.

Number 1 will turn on Red LED
Number 2 will turn on Green LED
Number 3 will turn on Blue LED
Number 4 will turn on the Piezo

If you type in lets say, 1, and then a 2. It will combine both commands and light up Red and Green.
Same with the Piezo, if you are to type 1 and 4, the Red light will turn on along with the Piezo.
There are many different combinations that you are able to make.

Board Setup:
The GND port goes to the ground leg of the RGB LED
GND port (2) goes to the negative side of the piezo.
DIO 13 leads to positive side of the piezo
DIO 12 to a 220 ohm resistor followed by the Red leg of the LED
DIO 11 to 220 ohm resistor followed by the Green leg of LED
DIO 10 to 220 ohm resistor followed by the Blue leg of LED
GND port (2) goes to the negative side of the piezo.

 */





#include <CurieBLE.h> // including CurieBLE header file (think of the file as being inserted on top of this program)

BLEService piezoService("19B10000-E8F2-537E-4F6C-D104768A1214"); // create a new instance of the BLEService class

BLEUnsignedIntCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite); // create a new instance of the CharCharacteristic class

const int piezoPin = 13; // constant pin number (Piezo Tone Pin)
const int redPin = 12; // constant pin number (Red LED in RGB)
const int bluePin = 11; // constasnt pin number (Blue LED in RGB)
const int greenPin = 10; // constant pin number (Green LED in RGB)

void setup() { // setup function declaration and definition
  
  Serial.begin(9600); // serial monitor initialization at 9600 baud rate

  pinMode(piezoPin, OUTPUT); // setup piezo pin
  pinMode(redPin, OUTPUT); // setup redLED pin
  pinMode(bluePin, OUTPUT); // setup blueLED pin
  pinMode(greenPin, OUTPUT); // setup greenLED pin
  
  BLE.begin(); // start initialization of the ble device
  BLE.setLocalName("Jacob's Thing"); // set the local name of the ble device
  BLE.setAdvertisedService(piezoService); // place service in periphial socket
  piezoService.addCharacteristic(switchCharacteristic); // add characteristic to the service
  BLE.addService(piezoService); // add service to the periphial
  switchCharacteristic.setValue(0); // set initial value of characteristic
  BLE.advertise(); // start advertising

  Serial.println("BLE Piezo Peripheral"); // serial print (assertment)
} // end of setup function declaration and definition 

bool redLED = true; // boolean variable declaration and assignment
bool blueLED = true; // boolean variable declaration and assignment
bool greenLED = true; // boolean variable declaration and assignment
bool piezoFlop = false;

void loop() { // loop function declaration and definition

  BLEDevice central = BLE.central(); // scan for central devices
  
  if (central) { // once device has been found, "central" will return "true"
    
    Serial.print("Connected to central: "); // serial (assertmen)
    Serial.println(central.address()); // print out the mac address of the central device (usually a phone)
    
    while (central.connected()) { // this loop will terminate when the central device disconnects
    
      if (switchCharacteristic.written()) { // if a value is written to the periphial device

        delay(100); // catch up on request
        Serial.println(switchCharacteristic.value()); // print out the value that is being sent to the periphial device
        
        if (switchCharacteristic.value() == 1) { // if the characteristic value is equal to 1
          Serial.println("This is inside the if statement (1)");
          digitalWrite(redPin, redLED); // turn on or off the led based on the boolean variable
          redLED = !redLED; // invert the boolean variable
          
        } else if (switchCharacteristic.value() == 2) { // if the characteristic value is equal to 2
          digitalWrite(greenPin, greenLED); // turn on or off the led based on the boolean variable
          greenLED = !greenLED; // invert the boolean variable
          
        } else if (switchCharacteristic.value() == 3) { // if the characteristic value is equal to 3
          digitalWrite(bluePin, blueLED); // turn on or off the led based on the boolean variable
          blueLED = !blueLED; // invert the boolean variable
          
        } else if (switchCharacteristic.value() == 4) { // if the characteristic value is equal to 4
          piezoFlop = !piezoFlop; // invert the flop value
          piezoFlop ? tone(piezoPin,1000) : noTone(piezoPin); // turn on the piezo (look up the ternary operator)
        } else if (switchCharacteristic.value() == 5) { // if the characteristic value is equal to 5
          
        } else if (switchCharacteristic.value() == 6) { // if the characteristic value is equal to 6
          
        } // end of else if statement chain
      } // end of characterstic written if statement
    } // end of central device while loop
    
    Serial.print(F("Disconnected from central: ")); // this assertment is called when the central device is disconnected
    Serial.println(central.address()); // print out the mac address of the central device
  } // end of checking if device has connected
} // end of loop function definition
