// 🧠 FINAL CODE for NANO (The Smart Helmet)
#include <RH_ASK.h>
RH_ASK rf_driver(2000, 10, 12); // Transmit on Digital Pin 12
int ALCOHOL_LIMIT = 400; // Your calibrated threshold

void setup() {
  rf_driver.init();
  pinMode(3, INPUT_PULLUP); // Limit Switch on Digital Pin 3
}

void loop() {
  bool helmetOn = (digitalRead(3) == LOW); // LOW means switch is pressed/closed
  int alcoholLevel = analogRead(A0);       // MQ3 Sensor on Analog Pin A0

  // Safety Logic: Helmet ON AND Alcohol BELOW limit
  if (helmetOn && (alcoholLevel < ALCOHOL_LIMIT)) {
    const char *msg = "START";
    rf_driver.send((uint8_t *)msg, strlen(msg));
  } 
  else {
    const char *msg = "STOP";
    rf_driver.send((uint8_t *)msg, strlen(msg));
  }
  rf_driver.waitPacketSent();
  delay(500); // Send command twice a second
}
