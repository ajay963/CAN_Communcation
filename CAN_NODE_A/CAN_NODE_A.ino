// // CAN node A

#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define NewLine Serial.print("\n");

LiquidCrystal_I2C lcd(0x3F, 16, 2);
struct can_frame node_A;
struct can_frame syncMsg;

MCP2515 mcp2515(53);

struct CAN_Mssg {
  uint32_t id;   // 32-bit unsigned integer for CAN ID
  uint8_t value; // 8-bit unsigned integer for data byte
};

// This function reads a CAN message and returns it
can_frame receiveCANMssg() {
  if (mcp2515.readMessage(&syncMsg) == MCP2515::ERROR_OK) {
    Serial.print("ID: ");
    Serial.print(syncMsg.can_id, HEX); // print ID in HEX
    Serial.print(" ");
    Serial.print("Data 01: ");
    Serial.print(syncMsg.data[1]);
    NewLine;
  }
  return syncMsg; // Always return the current canMsg (even if not updated)
}


void lcd_setup() {
  lcd.init();         // Initialize LCD
  lcd.backlight();    // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("Initiating CAN");
}


void lcdDisplayData(int &val) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("sesnor value: " + val);
  delay(200);
}



void setup() {
  Serial.begin(9600);
  node_A.can_id = 0x100;
  node_A.can_dlc = 8;
 
  lcd_setup();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  delay(400);
}

// synchronization Fn()
void loop() {
  // Read a CAN message from the MCP2515
  receiveCANMssg();
  int sensorVal = 203;
  node_A.data[1] = sensorVal;
  lcdDisplayData(sensorVal); 

    if (syncMsg.can_id == 0x00) {  
            Serial.println("SYNC received, waiting 50ms...");
            
            if (mcp2515.sendMessage(&node_A) == MCP2515::ERROR_OK)
                Serial.println("Node A sent message");
            else
                Serial.println("Node A failed to send");
    }
}


// Non synchronization Fn()
// void loop() {
//   // Read a CAN message from the MCP2515
//   int sensorVal = 203;
//   node_A.data[1] = sensorVal;
//   lcdDisplayData(sensorVal); 
            
//   if (mcp2515.sendMessage(&node_A) == MCP2515::ERROR_OK)
//       Serial.println("Node A sent message");
//   else
//       Serial.println("Node A failed to send");
    
// }