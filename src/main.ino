// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Receiver");

  //CAN.setPins(cs, irq) CS INT
  //CAN.setPins(15, 2); works

  // MCP2515        ESP8266
  //   CS    ----    GPIO5 ( D1 )
  //   SO    ----    GPIO12 ( D6 )
  //   SI    ----    GPIO13 ( D7 )
  //   SCK   ----    GPIO14 ( D5 )
  //   INT   ----    GPIO4 ( D2 ) Not required
  // Important to set CS port for CAN by CAN.setPins(cs, irq)

  CAN.setPins(5, 4);
  //CAN.setPins(D1, D2);
  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    // received a packet
    Serial.print("Received ");

    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);

      // only print packet data for non-RTR packets
      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }

    Serial.println();
  }
}


