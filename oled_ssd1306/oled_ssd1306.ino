#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// NodeMCU: D1 = GPIO5 (SCL), D2 = GPIO4 (SDA)
#define OLED_SDA 4
#define OLED_SCL 5

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1       // Reset no conectado
#define OLED_ADDR 0x3C      // Dirección I2C típica del SSD1306 (0x3D en algunos módulos)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println("=== NodeMCU ESP8266 - OLED SSD1306 128x64 ===");

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("Error: no se detectó SSD1306 en 0x3C. Revisa cableado/dirección.");
    while (true) {
      delay(1000);
    }
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("NodeMCU ESP8266");
  display.println("OLED SSD1306 OK");
  display.println("I2C: SDA=D2(4)");
  display.println("     SCL=D1(5)");
  display.println("Addr: 0x3C");
  display.display();

  Serial.println("OLED inicializado correctamente.");
}

void loop() {
  static unsigned long last = 0;
  static unsigned long counter = 0;

  if (millis() - last >= 1000) {
    last = millis();
    counter++;

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("NodeMCU + SSD1306");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    display.setCursor(0, 20);
    display.print("Uptime: ");
    display.print(counter);
    display.println(" s");

    display.setCursor(0, 32);
    display.print("128x64 I2C OK");

    display.setCursor(0, 48);
    display.print("D1=SCL D2=SDA");

    display.display();

    Serial.printf("Uptime: %lu s\n", counter);
  }
}
