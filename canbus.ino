#include <SPI.h>
#include <CAN_BUS_Shield.h>

CAN_BUS_Shield canBus;
unsigned long previousMillis = 0;
const long interval = 1000; // Read data every 1 second

void setup() {
  Serial.begin(9600);
  if (canBus.init(CANSPEED_500)) {
    Serial.println("CAN bus init success!");
  } else {
    Serial.println("CAN bus init failed!");
    while (1);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

   
    canBus.sendMsgBuf(0x7DF, 0, 8, 2, 1);

    
    if (canBus.readMsgBuf(&len, buf)) {
      unsigned long canId = canBus.getCanId();
      
      
      if (canId == 0x7E8) {
        // Extract RPM data from buf and print it
        int rpm = (buf[3] * 256 + buf[4]) / 4; // Example, adjust for your car
        Serial.print("RPM: ");
        Serial.println(rpm);
      }
    }
  }
}
