/* nRF_swLED_receiver_tester.ino
* Sketch 2 of 2: receiver, aka Rcvr, the receiving
sketch for use with the nRF24L01+ */
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

struct joystick {
  uint16_t rX;
  uint16_t rY;
} stick;

const int LED = A0;
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"TERPA");
  Mirf.payload = sizeof(stick);
  Mirf.channel = 90;
  Mirf.config();
  Serial.println("starting");
}
void loop() {
  while (!Mirf.dataReady()) {}
  Mirf.getData((byte *)&stick);
  int val = map(stick.rX, 0, 1023, 0, 255);
  Serial.println(stick.rX);
  analogWrite(LED, val);
  delay(50);
}