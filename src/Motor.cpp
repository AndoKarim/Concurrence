#include <iostream>
#include <string>

#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

#include "Motor.h"

using namespace std;

void *moveAll(void *t_data){
  cout << "MoveAll" <<endl;

  if (t_data != NULL){
    Motor* m=(Motor*) t_data;
    /* Fct qui doit faire bouger tous les joueurs pendant toute la durée du jeu lorsque l'on a l'option -t0
    Tant que le jeu n'est pas fini, on prend la liste des joueurs et on fait avancer chacun d'eux
    */
  }else{
    cerr << "error in thread" << endl;
  }

}


void Motor::run(){

  if(nbThreads == 0){
        pthread_t t0;
        pthread_create(&t0, NULL, moveAll , this);
        pthread_join(t0, NULL);
  }

  if(nbThreads == 1){

  }

  if(nbThreads == 2){

  }

}

Motor::Motor(int nbPl, int nbTd){
  nbPlayers = nbPl;
  nbThreads = nbTd;
  plateau = Plateau();
  this->createPlayers();

  this->run();
}

void Motor::createPlayers(){
  for(int i = 0; i<this->nbPlayers;i++){
    int randX = rand()% 512;
    int randY = rand()% 128;
    cout << "X : " << randX << " Y : " << randY << endl;
    while(!plateau.addPlayer(randX,randY)){
      randX = rand()% 512;
      randY = rand()% 128;
    }
    Character c(randX, randY);
    listPlayers.push_back(c);
  }
}

void Motor::printAllPlayers(){
  for (list<Character>::iterator it=this->listPlayers.begin(); it!=this->listPlayers.end(); ++it)
	    it-> print();
}

Point Motor::changePosition(int x, int y){
  int LockD = 0;
  int LockH = 0;
  int LockV = 0;

  if(y < plateau.getYAzimut()){
    for(int i = 0; i < 5; i++){
      if(!(plateau.checkCase(x-1, y+i))){
        if(i!=4)
          LockH = 1;
        if(i!=0)
          LockD = 1;
      }
    }

    for(int i = 0; i < 4; i++){
      if(!(plateau.checkCase(x+i, y+4))){
        LockV = 1;
        if(i!=3)
          LockD = 1;
      }
    }
    if(LockD == 0){
      return Point(x-1, y+1);
    }else if(LockH ==0){
      return Point(x-1, y);
    }else if(LockV == 0){
      return Point(x, y+1);
    }else{
      return Point(x, y);
    }
  }else if(y > plateau.getYAzimut()){
    for(int i = 0; i < 5; i++){
      if(!(plateau.checkCase(x-1, y-i+3))){
        if(i!=4)
          LockH = 1;
        if(i!=0)
          LockD = 1;
      }
    }

    for(int i = 0; i < 4; i++){
      if(!(plateau.checkCase(x+i, y-1))){
        LockV = 1;
        if(i!=3)
          LockD = 1;
      }
    }
    if(LockD == 0){
      return Point(x-1, y-1);
    }else if(LockH ==0){
      return Point(x-1, y);
    }else if(LockV == 0){
      return Point(x, y-1);
    }else{
      return Point(x, y);
    }
  }
  else{
    for(int i = 0; i < 4; i++){
      if(!(plateau.checkCase(x-1, y+i))){
        LockH = 1;
      }
    }
    if(LockH == 0){
      return Point(x-1, y);
    }else{
      return Point(x, y);
    }
  }
}
