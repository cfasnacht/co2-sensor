#include "SSD1306.h"
#include "SCD30.h"
#include "WebServer.h"
#include "WiFi.h"

const char* ssid = "WifiSSID";
const char* password = "Wifipassword";

// This is needed to inialize SCL (Pin 4) / SDA (Pin 5)
SSD1306 display (0x3c, 5, 4);
WebServer server(80);
float sensor_values[3] = {0};

void handleRoot() {
  if ( sensor_values[0] == 0 )
  {
    server.send(200, "text/plain", "Sensor not found");
  } else {
    String body = "";
    body += "T:   " + String(sensor_values[1]) + " C" + "\n";
    body += "W:   " + String(sensor_values[2]) + " %" + "\n";
    body += "CO2: " + String(sensor_values[0]) + " ppm" + "\n";
    server.send(200, "text/plain", body);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup begin");

  // This is needed to inialize SCL (Pin 4) / SDA (Pin 5)
  display.init();
  display.setColor(BLACK);
  display.fillRect(0,0,127,10);

  display.flipScreenVertically ();
  display.clear();
  display.setTextAlignment (TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);

  display.drawString(0, 0, String("Setup begin"));
  display.drawString(0, 15, String("Connecting to WiFi"));
  display.display();

  WiFi.begin(ssid, password);
  delay(500);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi");
  }
  Serial.println("Connected to the WiFi network");
  display.drawString(0, 30, String("Connected"));
  display.display();

  //start webserver:
  server.begin();
  server.on("/", handleRoot);

  scd30.initialize();
  Serial.println("Setup done");
  display.drawString(0, 45, String("Setup done"));
  display.display();
  delay(1000);
}

void loop()
{
  server.handleClient();

  display.setColor(BLACK);
  display.fillRect(0,0,127,10);
  display.clear();
  delay(1000);
  if(scd30.isAvailable())
  {
    scd30.getCarbonDioxideConcentration(sensor_values);
  }
  if ( sensor_values[0] == 0)
  {
    display.setColor(WHITE);
    display.drawString(0, 0, String("Sensor not found"));
    display.drawString(0, 15, "IP: " + WiFi.localIP().toString());
  } else{
    display.setColor(WHITE);
    display.drawString(0, 0, "CO2: " + String(sensor_values[0]) + " ppm");
    display.drawString(0, 15, "T:       " + String(sensor_values[1]) + " C");
    display.drawString(0, 30, "W:      " + String(sensor_values[2]) + " %");
    display.drawString(0, 45, "IP: " + WiFi.localIP().toString());
  }
  display.display();

  delay(500);
}
