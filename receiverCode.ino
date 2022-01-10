
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//RF24 radio(10, 9);   // nRF24L01 (CE, CSN)
RF24 radio(6, 7);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
