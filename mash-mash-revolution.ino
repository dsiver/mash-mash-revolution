/*
 * Mash Mash Revolution
 * Board: Arduino Esplora
 *
 * David Siver
 * CS 4985
 * Fall 2015
 */

#include <SPI.h>
#include <TFT.h>
#include <Esplora.h>

#define DEBUG 1
#define SERIAL_BAUD_RATE 9600

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
  drawMashFloor();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void drawMashFloor() {
  EsploraTFT.stroke(255, 255, 255);
  //EsploraTFT.line(xStart, yStart, xEnd, yEnd);
  EsploraTFT.line(40, 0, 0, 40);
  EsploraTFT.line(0, 40, 40, 80);
  EsploraTFT.line(40, 80, 80, 40);
  EsploraTFT.line(80, 40, 40, 0);

  EsploraTFT.line(20, 20, 60, 60);
  EsploraTFT.line(20, 60, 60, 20);
}
