// CO2 Sensor

#include "SCD30.h"

// Slow
// For the breakout, you can use any (4 or) 5 pins
//#define sclk 4
//#define mosi 5
//#define cs   6
//#define dc   7
//#define rst  8

//Fast
//Use these pins for the shield!
#define sclk 13  // SainSmart: SCL
#define mosi 11  // SainSmart: SDA
#define cs   10  // SainSmart: CS
#define dc   9   // SainSmart: RS/DC
#define rst  8   // SainSmart: RES

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// Option 1: use any pins but a little slower
//Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

// Option 2: must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

void setup(void) {
  Serial.begin(115200);
  Serial.print("setup!");

  // If your TFT's plastic wrap has a Black Tab, use the following:
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);


  // initialize CO2
  Wire.begin();
  Serial.println("SCD30 Raw Data");
  scd30.initialize();

  Serial.println("setup done");
  delay(1000);
}

void loop() {
  float result[3] = {0};
    
  if(scd30.isAvailable())
  {
    scd30.getCarbonDioxideConcentration(result);
    Serial.print("Carbon Dioxide Concentration is: ");
    Serial.print(result[0]);
    Serial.println(" ppm");
    Serial.println(" ");
    Serial.print("Temperature = ");
    Serial.print(result[1]);
    Serial.println(" ℃");
    Serial.println(" ");
    Serial.print("Humidity = ");
    Serial.print(result[2]);
    Serial.println(" %");
  
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 15);
    
    tft.setTextColor(ST7735_RED);    
    tft.setTextSize(2);
    tft.println("CO2: ");
    tft.print(result[0]);
    tft.println(" ppm");

    tft.setTextColor(ST7735_WHITE);
    tft.println("Temp: ");
    tft.print(result[1]);
    tft.println(" C");

    tft.setTextColor(ST7735_GREEN);
    tft.println("Feuchte: ");
    tft.print(result[2]);
    tft.println(" %");

    tft.println("");
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print("Running: ");
    tft.print(millis() / 1000 / 60 /60);
    tft.print(" hours");
  }
  delay(4000);
  
}
