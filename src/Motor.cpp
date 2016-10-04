#include <iostream>
#include <string>

#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

#include "Motor.h"

using namespace std;

Motor::Motor(int nbPl, int nbTd){
  nbPlayers = nbPl;
  nbThreads = nbTd;
  plateau = Plateau();
  this->createPeople();
  printAllPlayers();
}

void Motor::createPeople(){
  for(int i = 0; i<this->nbPlayers;i++){
    int randX = rand()% 512;
    int randY = rand()% 128;
    cout << "X : " << randX << " Y : " << randY << endl;
    while(!plateau.addPeople(randX,randY)){
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
