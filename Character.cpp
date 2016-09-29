#include "Character.h"
#include <string.h>

using namespace std;

Character::Character(){}


Character::Character(int w, int h, int x, int y){
  width = w;
  height = h;
  xPosition = x;
  yPosition= y;
}

int Character::getX(){
  return xPosition;
}
int Character::getY(){
  return yPosition;

}

int Character::getWidth(){
  return width;
}

int Character::getHeight(){
  return height;
}

// void Character::move(string direction){
//   // if(strcmp(direction,"right")==0){
//   //
//   // }
//   // //   if(strcmp(direction,"right")==0){
//   // //
//   // // }
//   // // if(strcmp(direction,"right")==0){
//   // //
//   // // }
//   // // if(strcmp(direction,"right")==0){
//   // //
//   // // }
//   // // if(strcmp(direction,"right")==0){
//   // //
//   // // }
//   // // if(strcmp(direction,"right")==0){
//   // //
//   // // }
//
// }
