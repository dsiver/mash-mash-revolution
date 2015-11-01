#ifndef Circle_H
#define Circle_H

#include <Esplora.h>
#include <SPI.h>
#include <TFT.h>

class Circle {
  private:
    int xPos;
    int yPos;
    int radius;
    String color;
  
  public:
    static const String GREEN;
    static const String BLUE;
    static const String YELLOW;
    static const String RED;
    Circle();
    void initialize(int xPos, int yPos, int radius, String color);
    void draw();
    void erase();
};

#endif
