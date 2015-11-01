/*
 * Circle.cpp
 * Circle class for Mash Mash Revolution
 * Board: Arduino Esplora
 * 
 * David Siver
 * CS 4985
 * Fall 2015
 */

#include "Circle.h"

#define GREEN_RGB 0, 255, 0
#define BLUE_RGB 255, 0, 0
#define YELLOW_RGB 0, 255, 255
#define RED_RGB 0, 0, 255
#define BLACK_RGB 0, 0, 0

const String Circle::GREEN = "green";
const String Circle::BLUE = "blue";
const String Circle::YELLOW = "yellow";
const String Circle::RED = "red";

Circle::Circle() {
  
}

void Circle::initialize(int xPos, int yPos, int radius, String color){
  this->xPos = xPos;
  this->yPos = yPos;
  this->radius = radius;
  this->color = color;
}

void Circle::draw() {
  if (color == GREEN) {
    EsploraTFT.stroke(GREEN_RGB);
    EsploraTFT.fill(GREEN_RGB);
  }
  else if (color == BLUE) {
    EsploraTFT.stroke(BLUE_RGB);
    EsploraTFT.fill(BLUE_RGB);
  }
  else if (color == YELLOW) {
    EsploraTFT.stroke(YELLOW_RGB);
    EsploraTFT.fill(YELLOW_RGB);
  }
  else if (color == RED) {
    EsploraTFT.stroke(RED_RGB);
    EsploraTFT.fill(RED_RGB);
  }
  EsploraTFT.circle(this->xPos, this->yPos, this->radius);
}

void Circle::erase() {
  EsploraTFT.stroke(BLACK_RGB);
  EsploraTFT.fill(BLACK_RGB);
  EsploraTFT.circle(this->xPos, this->yPos, this->radius);
}

