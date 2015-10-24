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
#define SWITCH_ONE SWITCH_DOWN
#define SWITCH_TWO SWITCH_LEFT
#define SWITCH_THREE SWITCH_UP
#define SWITCH_FOUR SWITCH_RIGHT
#define LEVEL_2_START 1000

int score, oldScore, level, buttonOne, oldButtonOne, circleNumber, oldCircleNumber, circles;
const long circleOnDuration = 1000;
const long circleOffDuration = 1250;
unsigned long previousTime;
char scoreBoard[5];
boolean mashFloor[4];

void setup() {
  randomSeed(Esplora.readMicrophone() + Esplora.readSlider() + Esplora.readTemperature(DEGREES_F) + Esplora.readLightSensor());
  score = 0;
  oldScore = -1;
  level = 1;
  buttonOne = 0;
  circles = 0;
  oldButtonOne = buttonOne;
  circleNumber = 0;
  oldCircleNumber = circleNumber;
  previousTime = 0;
  Serial.begin(SERIAL_BAUD_RATE);
  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
  drawMashFloor();
  drawScoreBoard();
}

void loop() {
  if (score == LEVEL_2_START) {
    level = 2;
  }
  circleNumber = getRandomNumber(FIRST_CIRCLE, LAST_CIRCLE + 1);
  if (circles < level) {
    if (mashFloor[circleNumber - 1] == false) {
      drawCircle(circleNumber, true);
      mashFloor[circleNumber - 1] = true;
      circles++;
      Serial.println("circles++: " + String(circles));
    }
  }
  buttonOne = getButtonPress();
  if (buttonOne != oldButtonOne && buttonOne > 0) {
    Serial.println("buttonOne#: " + String(buttonOne));
    if (mashFloor[buttonOne-1]) {
      updateScoreBoard(50);
      drawCircle(buttonOne, false);
      circles--;
      mashFloor[buttonOne-1] = false;
      Serial.println("circles--: " + String(circles));
    } else {
      updateScoreBoard(-50);
    }
  }
  oldButtonOne = buttonOne;
}

int getButtonPress() {
  int switchStates[] = {Esplora.readButton(SWITCH_ONE), Esplora.readButton(SWITCH_TWO), Esplora.readButton(SWITCH_THREE), Esplora.readButton(SWITCH_FOUR)};
  int sum = 0;
  int pressedSwitch = 0;
  for (int i = 0; i < 4; i++) {
    sum += switchStates[i];
    if (switchStates[i] == LOW) {
      pressedSwitch = i + 1;
    }
  }
  if (sum == 3) {
    return pressedSwitch;
  }
  return -1;
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
  for (int i = 0; i < LAST_CIRCLE; i++) {
    mashFloor[i] = false;
  }
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
  updateScoreBoard(0);
  oldScore = score;
}

void updateScoreBoard(int points) {
  score += points;
  if (score < 0) {
    score = 0;
  }
  if (score != oldScore) {
    String scoreString = String(oldScore);
    scoreString.toCharArray(scoreBoard, 5);
    EsploraTFT.stroke(0, 0, 0);
    EsploraTFT.text(scoreBoard, 0, 105);
    scoreString = String(score);
    scoreString.toCharArray(scoreBoard, 5);
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.text(scoreBoard, 0, 105);
  }
  oldScore = score;
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

int getRandomNumber(int low, int high) {
  return random(low, high);
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
