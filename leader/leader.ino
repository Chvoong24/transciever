/* nRF_swLED_transmitter_tester.ino
Sketch 1 of 2: transmitter, aka Sendr,
the sending sketch for use with the nRF24L01+ */
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
uint16_t sensorReading;
int LED = 5;
int swPin = 4;
void setup(){
Serial.begin(9600);
pinMode(LED, OUTPUT);
pinMode(swPin, INPUT);
Mirf.spi = &MirfHardwareSpi;
Mirf.init();
Mirf.setRADDR((byte *)"Sendr");
Mirf.payload = sizeof(sensorReading);
Mirf.channel = 90;
Mirf.config();
}
void loop(){
if(digitalRead(swPin)==HIGH)
{
sensorReading = 1;
digitalWrite(LED,HIGH);
delay(20);
}
else {
sensorReading = 0;
digitalWrite(LED,LOW);
delay(20);
}
Serial.println(sensorReading);
Mirf.setTADDR((byte *)"Rcvr");
Mirf.send((byte *) &sensorReading);
while(Mirf.isSending()){}
delay(50); // wait some time
before taking another reading
} 