/*****************************************************************
 * Character.h
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/
#include "Point.h"
class Character {
  private:
    //const int width = 4;
    //const int height = 4;
    Point position;

  public:
    Character();
    Character(int x, int y);
    Character(Point p);
    void move(Point p);
    void print();
    int getX();
    int getY();
    //int getWidth();
    //int getHeight();
};
