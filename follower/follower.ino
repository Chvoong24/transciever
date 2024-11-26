/* nRF_swLED_receiver_tester.ino
* Sketch 2 of 2: receiver, aka Rcvr, the receiving
sketch for use with the nRF24L01+ */
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

int LED = 2;
int sensorReading;
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"BOOOO");
  Mirf.payload = sizeof(sensorReading);
  Mirf.channel = 90;
  Mirf.config();
  Serial.println("starting");
}
void loop() {
  while(!Mirf.dataReady()){}
  Mirf.getData((byte *) &sensorReading);
  Serial.println(sensorReading);
  if(sensorReading == 1)
  {digitalWrite(LED,HIGH);}
  else
  {digitalWrite(LED,LOW);}
  delay(50);
}