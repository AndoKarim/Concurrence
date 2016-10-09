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
    while(!m->gameFinished()){
      cout << "not Finish"<< endl;
      int nb = m->getListPlayers().size();
      int i = 0;

      for(int i=0;i<m->getListPlayers().size();i++){
        m->avancer(i,m->getListPlayers().at(i));
      }
      m->printAllPlayers();
      for(int i = 0;i<m->getListPlayers().size();i++){
        Character p = m->getListPlayers()[i];
        if(p.getX() <=0 && p.getY()>=60 && p.getY()<=67){
          m->removePlayer(i,p);
        }
      }
    }
  }else{
    cerr << "error in thread" << endl;
  }

}


void Motor::run(){

  if(nbThreads == 0){ // On peut enlever ce thread et lancer dans le main
    pthread_t t0;
    pthread_create(&t0, NULL, moveAll , this);
    pthread_join(t0, NULL);
  }

  if(nbThreads == 1){
    pthread_t t0;
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_create(&t0, NULL, moveAll , this); //s'occupe de la partie nord ouest
    pthread_create(&t1, NULL, moveAll , this); //s'occupe de la partie nord est
    pthread_create(&t2, NULL, moveAll , this); //s'occupe de la partie sud ouest
    pthread_create(&t3, NULL, moveAll , this); //s'occupe de la partie sud est
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
  }

  if(nbThreads == 2){

  }

}

Motor::Motor(int nbPl, int nbTd, bool nbMs){
  nbPlayers = nbPl;
  nbThreads = nbTd;
  needMeasures = nbMs;
  plateau = Plateau();
  this->createPlayers();
  /*this->changePosition(508,0);
  this->changePosition(508,124);
  this->changePosition(508, 25);
  this->changePosition(508, 63);
  this->changePosition(508, 110);
  this->changePosition(128,0);
  this->changePosition(128,6);
  this->changePosition(128,55);
  this->changePosition(128,56);
  this->changePosition(128,124);
  this->changePosition(128,90);
  this->changePosition(127,56);
  this->changePosition(127,59);
  this->changePosition(127,61);
  this->changePosition(127,63);
  this->changePosition(127,68);
  this->changePosition(128,69);
  this->changePosition(128,70);
  this->changePosition(16,0);
  this->changePosition(16,25);
  this->changePosition(16,59);
  this->changePosition(16,60);
  this->changePosition(16,64);
  this->changePosition(16,65);
  this->changePosition(16,80);
  this->changePosition(16,124);*/
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
      cout << "X : " << randX << " Y : " << randY << endl;
    }
    Character c(randX, randY);
    listPlayers.push_back(c);

  }
}

void Motor::removePlayer(int i, Character& c){
  this->listPlayers.erase(this->listPlayers.begin() + i);
  this->plateau.removePlayer(c.getX(),c.getY());
}

void Motor::printAllPlayers(){
  for (vector<Character>::iterator it=this->listPlayers.begin(); it!=this->listPlayers.end(); ++it)
	    it-> print();
}

bool Motor::gameFinished(){
  cout << "nb" <<this->listPlayers.size() << endl;
  return this->listPlayers.size() == 0;
}

vector<Character> Motor::getListPlayers(){
  return this->listPlayers;
}

void Motor::removeAllPlayers(){
  this->listPlayers.clear();
}

void Motor::setPlayer(int i,Character c){
  listPlayers[i] = c;
}

void Motor::avancer(int index,Character& p){
  cout << "before" << endl;
  p.print();
  Point pt = changePosition(p.getX(),p.getY());
  cout << "Nico ";
  pt.print();
  cout << endl;
  cout << "after" << endl;
  if(this->plateau.movePlayer(p.getX(),p.getY(),pt.getX(),pt.getY())){
    p.move(pt);
  }
  p.print();
  listPlayers[index] = p;
  this->plateau.printAllPlayersCases();
}

Point Motor::changePosition(int x, int y){
  int LockD = 0;
  int LockH = 0;
  int LockV = 0;

  if((y < (plateau.getHeigth()-plateau.getOpenHeigthWall1())/2 && x < plateau.getWidthLastWall())
    || (y < (plateau.getHeigth()-plateau.getOpenHeigthWall2())/2 && x >= plateau.getWidthLastWall())){
  //if((y < 60 && x < 128) || (y < 56 && x > 127)){
    for(int i = 0; i < 5; i++){
      if(plateau.check(x-1, y+i)){
        if(i!=4)
          LockH = 1;
        if(i!=0)
          LockD = 1;
      }
    }
    for(int i = 0; i < 4; i++){
      if(plateau.check(x+i, y+4)){
        LockV = 1;
        if(i!=3)
          LockD = 1;
      }
    }
    if(LockD == 0){
      //printf("Oui Diagonale de: %d, %d à %d, %d \n", x, y, x-1, y+1);
      return Point(x-1, y+1);
    }else if(LockH ==0){
      //printf("Oui Horizontal de: %d, %d à %d, %d \n", x, y, x-1, y);
      return Point(x-1, y);
    }else if(LockV == 0){
      //printf("Oui Vertical de: %d, %d à %d, %d \n", x, y, x, y+1);
      return Point(x, y+1);
    }else{
      //printf("Non pas bouger en: %d, %d \n", x, y);
      return Point(x, y);
    }
  //}else if((y > 67 && x < 128) || (y > 71 && x > 127)){
}else if((y >= ((plateau.getHeigth()+plateau.getOpenHeigthWall1())/2)-3 && x < plateau.getWidthLastWall())
        || (y >= ((plateau.getHeigth()+plateau.getOpenHeigthWall2())/2)-3 && x >= plateau.getWidthLastWall())){

    for(int i = 0; i < 5; i++){
      if(plateau.check(x-1, y-i+3)){
        if(i!=4)
          LockH = 1;
        if(i!=0)
          LockD = 1;
      }
    }
    for(int i = 0; i < 4; i++){
      if(plateau.check(x+i, y-1)){
        LockV = 1;
        if(i!=3)
          LockD = 1;
      }
    }
    if(LockD == 0){
      //printf("Oui Diagonale de: %d, %d à %d, %d \n", x, y, x-1, y-1);
      return Point(x-1, y-1);
    }else if(LockH ==0){
      //printf("Oui Horizontal de: %d, %d à %d, %d \n", x, y, x-1, y);
      return Point(x-1, y);
    }else if(LockV == 0){
      //printf("Oui Vertical de: %d, %d à %d, %d \n", x, y, x, y-1);
      return Point(x, y-1);
    }else{
      //printf("Non pas bouger en: %d, %d \n", x, y);
      return Point(x, y);
    }
  }
  else{
    for(int i = 0; i < 4; i++){
      if(plateau.check(x-1, y+i)){
        LockH = 1;
      }
    }
    if(LockH == 0){
      //printf("Oui Horizontal de: %d, %d à %d, %d \n", x, y, x-1, y);
      return Point(x-1, y);
    }else{
      //printf("Non pas bouger en: %d, %d \n", x, y);
      return Point(x, y);
    }
  }
}
