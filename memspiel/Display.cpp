#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include "display.h"

// Define pin connections
#define TFT_CS   D10
#define TFT_DC   D9
#define TFT_RST  D8
#define TFT_MOSI D11
#define TFT_CLK  D13

//Declarations
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);


Display::Display(){
}
int Display::setup(){
// Start the serial connection
  Serial.begin(9600);

  // Initialize the SPI bus
  SPI.begin();

  // Set up the ILI9341 display
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  return 0;
};

void Display::scoreDisplay(int highscore, int score){
    // Draw the horizontal line at 20% of the screen height
  int lineY = tft.height() * 0.1;
  tft.drawFastHLine(0, lineY, tft.width(), ILI9341_WHITE);

  // Draw the "score:" label at the top left corner
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.print("Score:");
  tft.print(score);

  // Draw the "highscore:" label at the top left corner
  tft.setTextSize(2);
  tft.setCursor(160, 0);
  tft.print("HighScore:");
  tft.print(highscore);
}

void Display::showInput(char input){
  tft.fillRect(160, 120, 25, 25, ILI9341_BLACK);
  tft.setTextSize(3);
  tft.setCursor(160, 120);
  tft.println(input);
}

void Display::countdown(){
   for(int i=0; i<320; i++) {
    int x = i;
    int y = tft.height() - 10;
    int w = tft.width() / 320;
    int h = 5;
    tft.fillRect(x, y, w, h, ILI9341_RED);
    delay(50);
    tft.fillRect(x, y, w, h, ILI9341_WHITE);
  }
}

void Display::redX(){
  tft.fillScreen(ILI9341_BLACK);
  tft.drawLine(0, 0, tft.width(), tft.height(), ILI9341_RED);
  tft.drawLine(0, tft.height(), tft.width(), 0, ILI9341_RED);
  tft.drawLine(0, tft.height(), tft.width(), 0, ILI9341_RED);
}

void Display::checkmark(){
  tft.fillScreen(ILI9341_BLACK);
  int checkmarkWidth = tft.width() * 2 / 3;
  int checkmarkHeight = tft.height() * 2 / 3;
  int checkmarkX = (tft.width() - checkmarkWidth) / 2;
  int checkmarkY = (tft.height() - checkmarkHeight) / 2;

  // Draw green checkmark
  tft.fillRect(checkmarkX, checkmarkY, checkmarkWidth, checkmarkHeight, ILI9341_BLACK);
  tft.drawLine(checkmarkX, checkmarkY + checkmarkHeight / 2, checkmarkX + checkmarkWidth / 2, checkmarkY + checkmarkHeight, ILI9341_GREEN);
  tft.drawLine(checkmarkX + checkmarkWidth / 2, checkmarkY + checkmarkHeight, checkmarkX + checkmarkWidth, checkmarkY, ILI9341_GREEN);
}

