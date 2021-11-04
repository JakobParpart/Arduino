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
          
        } else if (switchCharacteristic.value() == 5) { // if the characteristic value is equal to 5
          
        } else if (switchCharacteristic.value() == 6) { // if the characteristic value is equal to 6
          
        } // end of else if statement chain
      } // end of characterstic written if statement
    } // end of central device while loop
    
    Serial.print(F("Disconnected from central: ")); // this assertment is called when the central device is disconnected
    Serial.println(central.address()); // print out the mac address of the central device
  } // end of checking if device has connected
} // end of loop function definition
