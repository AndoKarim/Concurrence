/*****************************************************************
 * Character.h
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Point.h"
class Character {
  private:
    Point position;
    bool finished;

  public:
    Character();
    Character(int x, int y);
    Character(Point p);
    void move(Point p);
    void print();
    int getX();
    int getY();
    void finish();
    bool hasFinished();

    bool isOnNO();
    bool isOnNE();
    bool isOnSE();
    bool isOnSO();

    bool nearSO();
    bool nearNE();
    bool nearSE();
    bool nearNO();
};
#endif
