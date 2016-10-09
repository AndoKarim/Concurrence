#include "Character.h"
#include <string.h>

using namespace std;

Character::Character(){}


Character::Character(int x, int y){
  position = Point(x,y);
}

Character::Character(Point p){
  position = p;
}

int Character::getX(){
  return position.getX();
}
int Character::getY(){
  return position.getY();
}

void Character::print(){
	position.print();
}

// int Character::getWidth(){
//   return width;
// }
//
// int Character::getHeight(){
//   return height;
// }

void Character::move(Point p){
  position = p;
}
