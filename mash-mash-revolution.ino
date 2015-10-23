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
#define FIRST_CIRCLE 1
#define LAST_CIRCLE 4
#define CIRCLE_ONE 1
#define CIRCLE_TWO 2
#define CIRCLE_THREE 3
#define CIRCLE_FOUR 4

int score, level;
boolean circleOneDrawn, circleTwoDrawn, circleThreeDrawn, circleFourDrawn;

void setup() {
  score = 0;
  level = 1;
  circleOneDrawn = false;
  circleTwoDrawn = false;
  circleThreeDrawn = false;
  circleFourDrawn = false;
  Serial.begin(SERIAL_BAUD_RATE);
  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
  drawMashFloor();
  drawScoreBoard();
  //demoCircles();
}

void loop() {

}

int getRandomNumber(int low, int high) {
  return random(low, high);
}

/*
 * Draws a specific circle on the TFT display.
 * circleNumber:  Defined circle number from FIRST_CIRCLE to
 *                LAST_CIRCLE
 * draw:          Pass either 'true' to draw or 'false' to erase
 */
void drawCircle(int circleNumber, boolean draw) {
  if (circleNumber == CIRCLE_ONE) {
    drawCircleOne(draw);
  }
  else if (circleNumber == CIRCLE_TWO) {
    drawCircleTwo(draw);
  }
  else if (circleNumber == CIRCLE_THREE) {
    drawCircleThree(draw);
  }
  else if (circleNumber == CIRCLE_FOUR) {
    drawCircleFour(draw);
  }
}

void drawMashFloor() {
  EsploraTFT.stroke(255, 255, 255);
  EsploraTFT.line(80, 0, 40, 40);
  EsploraTFT.line(40, 40, 80, 80);
  EsploraTFT.line(80, 80, 120, 40);
  EsploraTFT.line(120, 40, 80, 0);
  EsploraTFT.line(60, 20, 100, 60);
  EsploraTFT.line(60, 60, 100, 20);
}

void drawScoreBoard() {
  EsploraTFT.stroke(255, 255, 255);
  EsploraTFT.setTextSize(2);
  EsploraTFT.text("Score:", 0, 85);
  EsploraTFT.text("0", 0, 105);
}

void drawCircleOne(boolean draw) {
  if (draw) {
    EsploraTFT.stroke(0, 255, 0);
    EsploraTFT.fill(0, 255, 0);
    circleOneDrawn = true;
  }
  else {
    erase();
    circleOneDrawn = false;
  }
  EsploraTFT.circle(80, 60, RADIUS);
}

void drawCircleTwo(boolean draw) {
  if (draw) {
    EsploraTFT.stroke(255, 0, 0);
    EsploraTFT.fill(255, 0, 0);
    circleTwoDrawn = true;
  }
  else {
    erase();
    circleTwoDrawn = false;
  }
  EsploraTFT.circle(60, 40, RADIUS);
}

void drawCircleThree(boolean draw) {
  if (draw) {
    EsploraTFT.stroke(0, 255, 255);
    EsploraTFT.fill(0, 255, 255);
    circleThreeDrawn = true;
  }
  else {
    erase();
    circleThreeDrawn = false;
  }
  EsploraTFT.circle(80, 20, RADIUS);
}

void drawCircleFour(boolean draw) {
  if (draw) {
    EsploraTFT.stroke(0, 0, 255);
    EsploraTFT.fill(0, 0, 255);
    circleFourDrawn = true;
  }
  else {
    erase();
    circleFourDrawn = false;
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
