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
#define CIRCLE_ONE 1
#define CIRCLE_TWO 2
#define CIRCLE_THREE 3
#define CIRCLE_FOUR 4
#define FIRST_CIRCLE CIRCLE_ONE
#define LAST_CIRCLE CIRCLE_FOUR
#define NUM_CIRCLES LAST_CIRCLE
#define SWITCH_ONE SWITCH_DOWN
#define SWITCH_TWO SWITCH_LEFT
#define SWITCH_THREE SWITCH_UP
#define SWITCH_FOUR SWITCH_RIGHT
#define NUM_SWITCHES 4
#define LEVEL_2_START 500
#define POINTS 50
#define TIME_PENALTY -25

int score, oldScore, level;
int buttonOne, oldButtonOne, buttonTwo, oldButtonTwo;
int circleNumber, oldCircleNumber, circles;
const long serialTimer = 5000;
const long circleInterval = 1000;
const long debounceDelay = 50;
unsigned long previousTime;
unsigned long previousSerialTime;
unsigned long previousDebounceTime;
char scoreBoard[5];
boolean mashFloor[NUM_CIRCLES];
boolean buttonsDown[NUM_SWITCHES];
boolean proceed = false;

void setup() {
  randomSeed(Esplora.readMicrophone() + Esplora.readTemperature(DEGREES_F) + Esplora.readLightSensor());
  score = 0;
  oldScore = -1;
  level = 1;
  buttonOne = 0;
  buttonTwo = 0;
  oldButtonOne = buttonOne;
  oldButtonTwo = buttonTwo;
  circleNumber = 0;
  oldCircleNumber = circleNumber;
  circles = 0;
  previousTime = 0;
  Serial.begin(SERIAL_BAUD_RATE);
  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
  drawMashFloor();
  drawScoreBoard();
}

void loop() {
  if (score >= LEVEL_2_START) {
    level = 2;
  }
  unsigned long now = millis();
  checkTimer(now);
  updateMashFloor();
  if ( now - previousDebounceTime > debounceDelay){
    readButtons();
  }  
  if (proceed) {
    boolean match = buttonsMatchCircles();
    if (match) {
      previousTime = now;
      updateScoreBoard(POINTS);
    }
    else {
      updateScoreBoard(-POINTS);
    }
    clearMashFloor();
  }
  buttonOne = 0;
  buttonTwo = 0;
}

void checkTimer(unsigned long now) {
  if (now - previousTime > circleInterval) {
    previousTime = now;
    updateScoreBoard(TIME_PENALTY);
    clearMashFloor();
  }
}

void clearMashFloor() {
  int circleIndex = 0;
  for (int i = 1; i <= NUM_CIRCLES; i++) {
    drawCircle(i, false);
    mashFloor[circleIndex] = false;
    circleIndex++;
    circles--;
    if (circles < 0) {
      circles = 0;
    }
  }
}

void updateMashFloor() {
  for (int i = 1; i <= level; i++) {
    circleNumber = getRandomNumber(FIRST_CIRCLE, LAST_CIRCLE + 1);
    if (circles < level) {
      if (mashFloor[circleNumber - 1] == false) {
        drawCircle(circleNumber, true);
        mashFloor[circleNumber - 1] = true;
        circles++;
      }
    }
  }
}

void readButtons() {
  int switchOneState = Esplora.readButton(SWITCH_ONE);
  int switchTwoState = Esplora.readButton(SWITCH_TWO);
  int switchThreeState = Esplora.readButton(SWITCH_THREE);
  int switchFourState = Esplora.readButton(SWITCH_FOUR);
  int switchStateSum = switchOneState + switchTwoState + switchThreeState + switchFourState;
  int switchStates[NUM_SWITCHES] = {switchOneState, switchTwoState, switchThreeState, switchFourState};
  if (switchStateSum == (HIGH * NUM_SWITCHES) - level) {
    proceed = true;
  }
  else {
    proceed = false;
  }
  if (proceed) {
    setButtons(switchStates);
  }
}

void setButtons(int switchStates[]) {
  boolean buttonOneFound = false;
  int j = NUM_SWITCHES - 1;
  for (int i = 0; i < j; i++) {
    for (j; j > i; j--) {
      if (switchStates[i] == LOW) {
        buttonOne = i + 1;
        buttonOneFound = true;
      }
      if (switchStates[j] == LOW) {
        if (buttonOneFound) {
          buttonTwo = j + 1;
        }
        else {
          buttonOne = j + 1;
          buttonOneFound = true;
        }
      }
    }
  }
  oldButtonOne = buttonOne;
  oldButtonTwo = buttonTwo;
}

boolean buttonsMatchCircles() {
  boolean buttonOneMatches = mashFloor[buttonOne - 1] == true;
  boolean buttonTwoMatches = mashFloor[buttonTwo - 1] == true;
  if (level == 2) {
    return buttonOneMatches && buttonTwoMatches;
  }
  else if (level == 1) {
    return buttonOneMatches;
  }
  else {
    return false;
  }
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

/**
 * Draws the Mash Floor grid where circles will be drawn.
 */
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

void printDiagnostics() {
  unsigned long now = millis();
  if (now - previousSerialTime > serialTimer) {
    previousSerialTime = now;
    Serial.println("buttonOne: " + String(buttonOne) + " buttonTwo: " + String(buttonTwo));
    String diagnostic = "mashFloor = {";
    for (int i = 0; i < NUM_CIRCLES; i++) {
      if (i < NUM_CIRCLES - 1) {
        diagnostic += String(mashFloor[i]) + ", ";
      }
      else {
        diagnostic += String(mashFloor[i]) + "}";
      }
    }
    Serial.println(diagnostic);
    Serial.println("buttonsMatchCircles(): " + String(buttonsMatchCircles()));
    Serial.println("level: " + String(level));
    Serial.println();
  }
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
