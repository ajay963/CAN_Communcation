// Master Node 

#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define NewLine Serial.print("\n");

struct CAN_Mssg {
  uint32_t id;   // 32-bit unsigned integer for CAN ID
  uint8_t value; // 8-bit unsigned integer for data byte
};

LiquidCrystal_I2C lcd(0x3F, 16, 2);

struct can_frame synMssg;
struct can_frame rcvMssg;
CAN_Mssg data;


MCP2515 mcp2515(53);

void lcd_setup() {
  lcd.init();         // Initialize LCD
  lcd.backlight();    // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("Initiating CAN");
}


void lcdDisplayData(const CAN_Mssg &mssg) {
  Serial.print("Stored Value: ");
  Serial.println(mssg.value);
  Serial.print("Stored ID: ");
  Serial.println(mssg.id, HEX);
  NewLine;
  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ID: ");
  lcd.print(mssg.id, HEX);  
  lcd.setCursor(0, 1);
  lcd.print("Val: ");
  lcd.print(mssg.value);
  
  delay(200);
}


void sendCANMssg(can_frame &mssg){
    // mcp25115.
    if(mcp2515.sendMessage(&synMssg)==MCP2515::ERROR_OK) {
     Serial.print("Sent Value: ");
     Serial.print(synMssg.data[1]);
     NewLine;
    }else{
      Serial.print("Error");
    }

     delay(1000);  // Send every 1 second
}

void recieveCANMssg(){
    if (mcp2515.readMessage(&rcvMssg) == MCP2515::ERROR_OK) {
    Serial.print(rcvMssg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(rcvMssg.can_dlc, HEX); // print DLC
    Serial.print(" ");

    Serial.print(rcvMssg.data[1]);
   
  }
}

void setup() {
    Serial.begin(9600);
    synMssg.can_id = 0x00;  
    synMssg.can_dlc = 8; 

    SPI.begin();
  
    lcd_setup();
    lcd.print("Waiting...");

    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();
    delay(400);

}


// synchronization Fn()
void loop() {
    
    synMssg.data[1] = 00;
    sendCANMssg(synMssg);
    
    recieveCANMssg();
    data.id = rcvMssg.can_id;
    data.value = rcvMssg.data[1];

    lcdDisplayData(data);
    delay(100);
    
}

// Non synchronization Fn()
// void loop() { 
//     recieveCANMssg();
//     data.id = rcvMssg.can_id;
//     data.value = rcvMssg.data[1];

//     lcdDisplayData(data);    
// }
