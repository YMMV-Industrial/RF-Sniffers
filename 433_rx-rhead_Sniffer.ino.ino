/*
  Using RadioHead library to trigger the 433 mhz transmission
  Supposedly more reliable than RPI
  http://www.airspayce.com/mikem/arduino/RadioHead/RadioHead-1.41.zip
  
  Reversing protocols can be tricky as the best of times,  trying to work 
  through deciphering bits from raw wave output can be very frustrating.  
  This example is built for ASK but any modulation could work the same,
  if the demodulation is correct then you can feed it to stream input.
  

*/

#include <RH_ASK.h>
#include <SPI.h>


RH_ASK rxdriver;

void setup() {

  Serial.begin(9600);
  if (!rxdriver.init())
    Serial.println("RH ASK init failed");
}


// good for testing what is comming in over ASK
void loop() {
  uint8_t buf[50]; // A buffer of 50 bytes, adjust based on what the mesage appears to be
  uint8_t buflen=sizeof(buf);
  
  // do data processing as strings for now,  refactor as bytes if time permits
  String msgstr ; 

  if (rxdriver.recv(buf, &buflen)) {
    //extract data from input stream
    unsigned long dvep=millis();
    // write the log line out in pieces instead of sprintf
    Serial.print("RX_Message: ");
    Serial.print(dvep); 
    Serial.print(": ");    
    for (uint8_t i =0; i < buflen; i++) {
      Serial.print(buf[i]);
    } 
    Serial.println("");
    }

  }