#include <LiquidCrystal.h> // Library used to commuincate with Character LCD
#include "SoftwareSerial.h" // Library used to serially communicate with other chips
#include "DFRobotDFPlayerMini.h" // Library used to control the MP3 Player

SoftwareSerial SoftSerial(10, 11); // Creating Software Serial object and indicating TX & RX pins
DFRobotDFPlayerMini MP3Player; // Creating MP3 player object
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creating Character LCD object and indicating RS, EN, D4, D5, D6 and D7 pins.

uint16_t AnalogReading = 0; // Reading from analog pin A0

uint16_t LeftConf = 0;
uint8_t RightConf = 0;
uint8_t MidConf = 0;
uint8_t ConfThres = 50;
uint16_t SensorThres = 1009;

void setup() {
  Serial.begin(9600);
  SoftSerial.begin(9600);
  lcd.begin(20, 4);
  lcd.home();
  if (!MP3Player.begin(SoftSerial)) {
    // Unable to begin
    while (true);
  }
  MP3Player.volume(20);  // 0 - 30
}

void loop() {
  AnalogReading = analogRead(A0);
  if (AnalogReading > SensorThres) {
    LeftConf++;
    RightConf = 0;
    MidConf = 0;
    if (LeftConf > ConfThres) {
      /* DOWNWARD BEND FUNCTION */
      lcd.clear();
      lcd.print("I want water");
      MP3Player.play(3);
      LeftConf = 0;
      delay(2000);
    }
  } else if (AnalogReading < SensorThres) {
    RightConf++;
    LeftConf = 0;
    MidConf = 0;
    if (RightConf > ConfThres) {
      lcd.clear();
      lcd.print("I want food");
      MP3Player.play(4);
      RightConf = 0;
      delay(2000);
    }
  } else {
    MidConf++;
    LeftConf = 0;
    RightConf = 0;
    if (MidConf > ConfThres) {
      lcd.clear();
      lcd.print("NO COMMAND");
      MidConf = 0;
      delay(2000);
    }
  }
}
