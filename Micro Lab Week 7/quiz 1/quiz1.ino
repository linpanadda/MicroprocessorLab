#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,OLED_RESET);
void setup() {
 pinMode(A0,INPUT);
 pinMode(A1,INPUT);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
 display.clearDisplay(); // clears the screen and buffer
 display.drawCircle(50, 50, 12, WHITE);
 display.drawCircle(80, 50, 12, WHITE);
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(44,28);
 display.println("S1   S2");
 display.setTextSize(2);

 display.display();
}
void loop() {
  display.clearDisplay();
  display.drawCircle(50, 50, 12, WHITE);
 display.drawCircle(80, 50, 12, WHITE);
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(44,28);
 display.println("S1   S2");
 display.setTextSize(2);

  Serial.print("S1 :");
  Serial.print(digitalRead(A0));
  Serial.print("   S2 :");
  Serial.print(digitalRead(A1));
  Serial.println();
  if(digitalRead(A0) ==0){
    display.fillCircle(50, 50, 12, WHITE);
    display.display();
    
  }
    if(digitalRead(A1) ==0){
    display.fillCircle(80, 50, 12, WHITE);
    display.display();
    
  }
    display.display();
}
