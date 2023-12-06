#include <SPI.h>
#include <LoRa.h>

// Define Variables
#define NSS 5 
#define RST 13 
#define DIO0 14 
int counter = 0;

// Define Functions
void initLoRa();
void sendLoRaPacket(int packet);

// =======================================================

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender Initialize ...");
  initLoRa();  
}

// =======================================================

void loop() {
  sendLoRaPacket(counter);
  counter++;
  delay(5000);
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

// Send and parse LoRa packet
void sendLoRaPacket(int packet){
  Serial.print("Sending packet: ");
  Serial.println(packet);

  // send packet
  LoRa.beginPacket();
  LoRa.print("test packet ");
  LoRa.print(packet);
  LoRa.endPacket();
}
