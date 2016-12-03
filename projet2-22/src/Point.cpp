/*****************************************************************
 * Point.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#include "Point.h"
#include <iostream>

using namespace std;

Point::Point(){}

Point::Point(int a, int b){
        x = a;
        y = b;
}

int Point::getX(){
  return x;
}

int Point::getY(){
  return y;
}

void Point::print(){
  cout << "X: " << x << " Y: " << y << endl;
}
