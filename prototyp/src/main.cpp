#include <SPI.h>
#include <mcp_can.h>

#define CS_PIN 15
MCP_CAN CAN(CS_PIN);

void setup() {
  Serial.begin(115200);
  
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 gestartet!");
  } else {
    Serial.println("Fehler beim Start des MCP2515...");
    while (1);
  }
}

void loop() {
  unsigned long canId;
  unsigned char len = 0;
  unsigned char buf[8];

  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&canId, &len, buf);
    
    // GVRET-Daten senden
    Serial.write(0xF1); // GVRET Magic Byte
    Serial.write(0x09); // Command: CAN Frame
    Serial.write((uint8_t*)&canId, 4); // CAN-ID
    Serial.write(len); // Länge der Daten
    Serial.write(buf, len); // CAN-Daten
  }
}
