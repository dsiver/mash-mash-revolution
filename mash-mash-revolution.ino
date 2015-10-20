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
#define DELAY 250
#define RADIUS 10

int score;

void setup() {
  score = 0;
  Serial.begin(SERIAL_BAUD_RATE);
  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
  drawMashFloor();
  EsploraTFT.stroke(255, 255, 255);
  EsploraTFT.setTextSize(2);
  //EsploraTFT.text(text, xPos, yPos);
  EsploraTFT.text("Score:", 0, 85);
  EsploraTFT.text("0", 0, 105);

  demoCircles();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void drawMashFloor() {
  //EsploraTFT.line(xStart, yStart, xEnd, yEnd);
  EsploraTFT.stroke(255, 255, 255);
  EsploraTFT.line(80, 0, 40, 40);
  EsploraTFT.line(40, 40, 80, 80);
  EsploraTFT.line(80, 80, 120, 40);
  EsploraTFT.line(120, 40, 80, 0);
  EsploraTFT.line(60, 20, 100, 60);
  EsploraTFT.line(60, 60, 100, 20);
}

void drawCircleOne(boolean draw) {
  if (draw) {
    EsploraTFT.stroke(0, 255, 0);
    EsploraTFT.fill(0, 255, 0);
  }
  else {
    erase();
  }
  EsploraTFT.circle(80, 60, RADIUS);
}

void drawCircleTwo(boolean draw) {
  if (draw) {
    EsploraTFT.stroke(255, 0, 0);
    EsploraTFT.fill(255, 0, 0);
  }
  else {
    erase();
  }
  EsploraTFT.circle(60, 40, RADIUS);
}

void drawCircleThree(boolean draw) {
  if (draw) {
    EsploraTFT.stroke(0, 255, 255);
    EsploraTFT.fill(0, 255, 255);
  }
  else {
    erase();
  }
  EsploraTFT.circle(80, 20, RADIUS);
}

void drawCircleFour(boolean draw) {
  if (draw) {
    EsploraTFT.stroke(0, 0, 255);
    EsploraTFT.fill(0, 0, 255);
  }
  else {
    erase();
  }
  EsploraTFT.circle(100, 40, RADIUS);
}

void erase() {
  EsploraTFT.stroke(0, 0, 0);
  EsploraTFT.fill(0, 0, 0);
}

void demoCircles() {
  drawCircleOne(true);
  delay(DELAY);
  drawCircleOne(false);
  drawCircleTwo(true);
  delay(DELAY);
  drawCircleTwo(false);
  drawCircleThree(true);
  delay(DELAY);
  drawCircleThree(false);
  drawCircleFour(true);
  delay(DELAY);
  drawCircleFour(false);
}

