/* nRF_swLED_transmitter_tester.ino
Sketch 1 of 2: transmitter, aka Sendr,
the sending sketch for use with the nRF24L01+ */
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
uint16_t sensorReading;
int LED = 9;
int joypin = 2;
int swPin = 3;
int channel;

struct joystick
{
  uint16_t rX;
  uint16_t rY;
} stick;



void setup(){
Serial.begin(9600);
pinMode(LED, OUTPUT);
pinMode(swPin, INPUT);
pinMode(joypin, INPUT_PULLUP);
Mirf.spi = &MirfHardwareSpi;
Mirf.init();
Mirf.setRADDR((byte *)"TALKS");
Mirf.payload = sizeof(stick);
Mirf.channel = 90;
Mirf.config();
}
void loop(){
joystick stick = {analogRead(A2), analogRead(A3)};
if(digitalRead(swPin)==HIGH){
sensorReading = 1;
digitalWrite(LED,HIGH);
delay(20);
}
else {
sensorReading = 0;
digitalWrite(LED,LOW);
delay(20);
}
if(digitalRead(joypin)==HIGH){
channel = 1;
Mirf.setTADDR((byte *)"TERPA");
delay(20);
}
else {
channel = 0;
Mirf.setTADDR((byte *)"CHRIS");
delay(20);
}
delay(50);
Mirf.send((byte *) &stick);
while(Mirf.isSending()){}
delay(50); // wait some time
}
