// 🏍️ FINAL CODE for UNO (The Bike) - Corrected Version
#include <RH_ASK.h>
// Receiving on Digital Pin 11, unused Transmit Pin 10
RH_ASK rf_driver(2000, 11, 10); 

const int relayPin = 8;
const int buzzerPin = 9; 

void setup() {
  // 1. Initialize Communication
  if (!rf_driver.init()) {
    // If RF initialization fails, code will hang here.
  }

  // 2. Initialize Output Pins
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT); 

  // 3. Set Initial State (Motor OFF, Buzzer OFF)
  digitalWrite(relayPin, HIGH); // Motor OFF (Relay HIGH is OFF)
  digitalWrite(buzzerPin, LOW);  // Buzzer OFF
} // <--- Ensure this closing brace is present!

void loop() {
  // --- VARIABLE DECLARATION ---
  uint8_t buf[10];      
  uint8_t buflen = sizeof(buf); 

  // Check if a message has been received
  if (rf_driver.recv(buf, &buflen)) {
    buf[buflen] = 0; // Null-terminate the string
    String message = (char*)buf;

    if (message == "START") {
      // Safety Confirmed: Motor ON, Buzzer OFF
      digitalWrite(relayPin, LOW);  
      digitalWrite(buzzerPin, LOW);   
    } 
    else if (message == "STOP") {
      // Safety Protocol Failure: Motor OFF, Buzzer ON
      digitalWrite(relayPin, HIGH); 
      digitalWrite(buzzerPin, HIGH);  
      
      // OPTIONAL: Make buzzer pulse instead of solid tone
      delay(200);
      digitalWrite(buzzerPin, LOW);
      delay(200);
    }
  }
}