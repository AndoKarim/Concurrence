/*****************************************************************
 * Motor.h
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/
#ifndef MOTOR_H
#define MOTOR_H

using namespace std;
#include "Character.h"
#include "Plateau.h"
#include <vector>
#include <sys/time.h>
#include <sys/resource.h>

class Motor{
private :
    int nbPlayers;
    int nbThreads;
    bool needMeasures;
    Plateau plateau;
    vector<Character> listPlayers;
    float measuresTab[5];
    long maxResident;
    double timeMeasures[5];

    void createPlayers();


  public :
    Motor(int nbPlayers, int nbthreads);
    Motor(int nbPlayers, int nbthreads, bool needmeasures);
    void setPlayer(int i,Character c);
    void printAllPlayers();
    void run();
    Point changePosition(int x, int y);
    bool gameFinished();
    void removeAllPlayers();
    vector<Character> getListPlayers();
    void avancer(int i,Character& p);
    void removePlayer(int i, Character& c);
};

struct thread_Struct
{
	Motor* m;
	Character c;
  int index;
};

#endif
