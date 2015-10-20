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
  
  
  drawCircleOne();
  drawCircleTwo();
  drawCircleThree();
  drawCircleFour();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void drawMashFloor() {
  //EsploraTFT.line(xStart, yStart, xEnd, yEnd);
  EsploraTFT.stroke(255, 255, 255);
  EsploraTFT.line(40, 0, 0, 40);
  EsploraTFT.line(0, 40, 40, 80);
  EsploraTFT.line(40, 80, 80, 40);
  EsploraTFT.line(80, 40, 40, 0);
  EsploraTFT.line(20, 20, 60, 60);
  EsploraTFT.line(20, 60, 60, 20);
}

void drawCircleOne(){
  //EsploraTFT.circle(xPos, yPos, radius);
  EsploraTFT.stroke(0,255,0);
  EsploraTFT.fill(0,255,0);
  EsploraTFT.circle(40, 60, 10);
}

void drawCircleTwo(){
    EsploraTFT.stroke(255,0,0);
  EsploraTFT.fill(255,0,0);
  EsploraTFT.circle(20, 40, 10);
}

void drawCircleThree(){
  EsploraTFT.stroke(0,255,255);
  EsploraTFT.fill(0, 255,255);
  EsploraTFT.circle(40, 20, 10);
}

void drawCircleFour(){
  EsploraTFT.stroke(0,0,255);
  EsploraTFT.fill(0,0,255);
  EsploraTFT.circle(60, 40, 10);
}

