#include "SSD1306.h"
#include "SCD30.h"

SSD1306 display (0x3c, 5, 4);

void setup()
{
    Serial.begin(115200);
    Serial.println("Setup begin");
    delay(500);

    // This is needed to inialize SCL (Pin 4) / SDA (Pin 5)
    display.init();
    display.flipScreenVertically ();
    display.clear();
    display.setTextAlignment (TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);

    scd30.initialize();
    Serial.println("Setup done");
    delay(2000);
}

void loop()
{
    display.setColor(BLACK);
    display.fillRect(0,0,127,10);
    display.clear();
    float result[3] = {0};

    if(scd30.isAvailable())
    {
      scd30.getCarbonDioxideConcentration(result);
      display.setColor(WHITE);
      display.drawString(0, 0, "CO2: " + String(result[0]) + " ppm");
      display.drawString(0, 15, "T:       " + String(result[1]) + " C");
      display.drawString(0, 30, "W:      " + String(result[2]) + " %");
    } else {
      display.drawString(0, 0, String("Sensor not found"));
    }
    Serial.println("CO2: " + String(result[0]) + " ppm");

    display.display();

    delay(2000);
}
