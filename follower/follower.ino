#include <SPI.h>
#include "Mirf.h“
#include "nRF24L01.h“
#include "MirfHardwareSpiDriver.h"
uint16_t sensorReading;
int8_t reps = 10;
void setup(){
Serial.begin(9600);
Mirf.spi = &MirfHardwareSpi;
Mirf.init();
Mirf.setRADDR((byte *)“HomeB");
Mirf.payload = sizeof(sensorReading);
Mirf.channel = 90;
Mirf.config();
}
void loop(){
sensorReading = 0;
for(int i=0;i<reps;i++){
sensorReading += analogRead(0);
}
sensorReading = sensorReading/reps;
Mirf.setTADDR((byte *)“Rover");
Mirf.send((byte *) &sensorReading);
while(Mirf.isSending()){}
delay(10);
}

