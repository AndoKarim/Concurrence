/*****************************************************************
 * Character.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/
#include "Character.h"
#include <string.h>


Character::Character(){}


Character::Character(int x, int y){
  position = Point(x,y);
  finished = false;
}

Character::Character(Point p){
  position = p;
  finished = false;
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

void Character::move(Point p){
  position = p;
}

void Character::finish(){
  finished = true;
}

bool Character::hasFinished() {
    return  finished;
}

bool Character::isOnNO() {
    return getX() < 256 && getY() < 64 && getX() >= 0 && getY() >= 0;
}

bool Character::isOnNE(){
    return getX() >= 255 && getY() <=63 && getX() >= 0 && getY() >= 0;
}

bool Character::isOnSE(){
    return getX() >= 255 && getY() > 63 && getX() >= 0 && getY() >= 0;
}

bool Character::isOnSO(){
    return getX() < 256 && getY() > 63 && getX() >= 0 && getY() >= 0;
}

bool Character::nearSO() {
    if(getY() > 63 && getX()> 255)
        return getX()-1 == 255;

    if(getY() <= 63 && getX()<= 255)
        return getY()+1 == 64;

    if(getY() <= 63 && getX()> 255)
        return getX()-1 == 255 && getY()+1 == 64;
}

bool Character::nearNE() {
    if(getY() > 63 && getX()> 255)
        return getY()-1 == 63;
}

bool Character::nearSE() {
    if(getY() <= 63 && getX()> 255)
        return getY()+1 == 64;
}

bool Character::nearNO() {
    if(getY() <= 63 && getX()> 255)
        return getX()-1 == 255;
    if(getY() > 63 && getX() <= 255)
        return getY()-1 == 63;


    if(getY() > 63 && getX()> 255)
        return getY()-1 == 63 && getX()-1 == 255;
}

