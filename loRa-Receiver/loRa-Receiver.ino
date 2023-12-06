#include <SPI.h>
#include <LoRa.h>

// Define Variables
#define NSS 26
#define RST 12 
#define DIO0 25 

// Define Functions
void initLoRa();
String reciveLoRaPacket();

// =======================================================

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver Initialize ...");
  initLoRa();  
}

// =======================================================

void loop() {
  // try to parse packet
  reciveLoRaPacket();

  // print RSSI of packet
//  Serial.print("' with RSSI ");
//  Serial.println(LoRa.packetRssi());
  delay(10);
}

// =======================================================

// initialize LoRa
void initLoRa(){
  LoRa.setPins(NSS , RST , DIO0);
  
  while(!LoRa.begin(433E6)) {
    Serial.print(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

// =======================================================

// Recive and parse LoRa packet
String reciveLoRaPacket(){
  String loraPacket = "";
  if (LoRa.parsePacket()) { 
    Serial.print("Received packet '");
    
    // read packet
    while (LoRa.available()){
      loraPacket += (char)LoRa.read();
    }
  }
  if(loraPacket != "")
    Serial.println(loraPacket);
  return loraPacket;
}
