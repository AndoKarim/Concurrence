/*****************************************************************
 * Plateau.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#include <iostream>
#include <semaphore.h>


#include "Plateau.h"

using namespace std;

Plateau::Plateau() {
  grille = Matrix(HEIGHT, Row(WIDTH));
  initialize();
  this->addWall();
}

void Plateau::initialize() {
  for(int i = 0; i < HEIGHT; i++){
    for(int j = 0; j< WIDTH ; j++){
      sem_t mutex;
      sem_init(&mutex,0,1);
      grille[i][j].mutex = &mutex;
        grille[i][j].isOccupied = 0;
    }
  }
}

struct struct_Mutex Plateau::getCase(int x, int y) {
  return grille[y][x];
}


void Plateau::addWall() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTHWALL; j++) {
      if (i < (HEIGHT - WALLOPENINGHEIGHT1) / 2 || i >= (HEIGHT + WALLOPENINGHEIGHT1) / 2)
        grille[i][j].isOccupied = 1;
    }
    for (int j = 0 + WALLDISTANCE; j < WIDTHWALL + WALLDISTANCE; j++) {
      if (i < (HEIGHT - WALLOPENINGHEIGHT2) / 2 || i >= (HEIGHT + WALLOPENINGHEIGHT2) / 2)
        grille[i][j].isOccupied = 1;
    }
  }
}

void Plateau::printWall() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (grille[i][j].isOccupied == 1)
        printf("IL Y A UN MUR EN %d, %d\n", i, j);
    }
  }
}

int Plateau::check(int x, int y) {
  return grille[y][x].isOccupied;
}

bool Plateau::checkCase(int x, int y) {
  if (x < 0 || y < 0)
    return false;
  if (x + 3 > 511)
    return false;
  if (y + 3 > 127)
    return false;

  for (int pos_x = 0; pos_x < 4; pos_x++) {
    for (int pos_y = 0; pos_y < 4; pos_y++) {
      if (check(x + pos_x,y + pos_y) == 1 || check(x + pos_x,y + pos_y) == 2) {
        //cerr << "impossible to add at this position" << endl;
        return false;
      }
    }
  }
  return true;
}

bool Plateau::movePlayer(int x, int y, int new_x, int new_y) {
  if (x > 0 && y > 0 && x + 3 < 511 && y + 3 < 127) {
    removePlayer(x, y);
    if (!addPlayer(new_x, new_y)) {
      addPlayer(x, y);
      return false;
    }
    return true;
  }
  return true;
}

bool Plateau::addPlayer(int x, int y) {

  if (!this->checkCase(x, y))
    return false;

  for (int delta_y = 0; delta_y < 4; delta_y++) {
    for (int delta_x = 0; delta_x < 4; delta_x++) {
      this->grille[y + delta_y][x + delta_x].isOccupied = 2;
    }
  }
  //cout << "added successfully" << endl;
  return true;
}

void Plateau::removePlayer(int x, int y) {
  for (int delta_y = 0; delta_y < 4; delta_y++) {
    for (int delta_x = 0; delta_x < 4; delta_x++) {
      this->grille[y + delta_y][x + delta_x].isOccupied = 0;
    }
  }
}

Plateau &Plateau::operator=(const Plateau &other) {
  this->grille = other.grille;
  return *this;
}

void Plateau::printAllPlayersCases() {
  int count = 0;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (check(j, i) == 2) {
        printf("IL Y A UNE PERSONNE EN %d, %d\n", j, i);
        count++;
      }
    }
  }
}


int Plateau::getXAzimut() {
  return XAZIMUT;
}

int Plateau::getYAzimut() {
  return YAZIMUT;
}

int Plateau::getHeigth() {
  return HEIGHT;
}

int Plateau::getOpenHeigthWall1() {
  return WALLOPENINGHEIGHT1;
}

int Plateau::getOpenHeigthWall2() {
  return WALLOPENINGHEIGHT2;
}

int Plateau::getWidthLastWall() {
  return WIDTHLASTWALL;
}
