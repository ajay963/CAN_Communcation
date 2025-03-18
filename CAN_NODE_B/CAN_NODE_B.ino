// // CAN node B

#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define NewLine Serial.print("\n");
#define ONE_WIRE_BUS 2  // DS18B20 connected to pin 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


struct can_frame node_B;
struct can_frame syncMsg;

MCP2515 mcp2515(53);

float getTemp() {
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);

    if (tempC == DEVICE_DISCONNECTED_C) {
        Serial.println("Sensor not detected! Check wiring.");
        return -127.0; // Error value for DS18B20
    } else {
        Serial.print("Temperature: ");
        Serial.print(tempC);
        Serial.println("°C");
    }

    return tempC;
}


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
  node_B.can_id = 0x200;
  node_B.can_dlc = 8;
  
  sensors.begin();    
  Serial.println("Searching for DS18B20 sensors...");
  if (sensors.getDeviceCount() == 0) {
        Serial.println("No sensors found! Check wiring.");
  }
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  delay(400);
}

// synchronization Fn()
void loop() {
  // Read a CAN message from the MCP2515
  receiveCANMssg();
  int sensorVal = getTemp();
  node_B.data[1] = sensorVal;
  lcdDisplayData(sensorVal); 
  

    if (syncMsg.can_id == 0x00) {  // Check for SYNC message
            Serial.println("SYNC received, waiting 50ms...");
            delay(50); // Small delay before sending
            
            if (mcp2515.sendMessage(&node_B) == MCP2515::ERROR_OK)
                Serial.println("Node A sent message");
            else
                Serial.println("Node A failed to send");
    }
}


// Non synchronization Fn()
// void loop() {
//   // Read a CAN message from the MCP2515
//   receiveCANMssg();
//   int sensorVal = getTemp();
//   node_B.data[1] = sensorVal;
//   lcdDisplayData(sensorVal); 
  
            
//   if (mcp2515.sendMessage(&node_B) == MCP2515::ERROR_OK)
//       Serial.println("Node A sent message");
//   else
//       Serial.println("Node A failed to send");
    
// }
