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

#include <semaphore.h>
#include <map>
#include "Monitor.h"
#include "SynchroBarrier.h"


class Motor{
private :
    int nbPlayers;
    int nbThreads;
    bool needMeasures;
    Plateau plateau;
    vector<Character> listPlayers;
    int numEtape;
    float measuresTab[5];
    long maxResident;
    double timeMeasures[5];

    map<string,sem_t*>* semaphores;

    Monitor* monitor;
    SynchroBarrier* barrier;

    void createPlayers();


  public :
    Motor(int nbPlayers, int nbthreads);
    Motor(int nbPlayers, int nbthreads, bool needmeasures);
    Motor(int nbPl, int nbTd, bool nbMs, int numEtap);
    void setPlayer(int i,Character c);
    void printAllPlayers();
    void run();
    Point changePosition(int x, int y);
    bool gameFinished();
    void removeAllPlayers();
    vector<Character> getListPlayers();
    void avancer(int i,Character& p);
    void removePlayer(int i, Character& c);
	int getNumEtape();
    Plateau *getPlateau();

    int nbP();

    void test();

    SynchroBarrier* getBarrier();
    Monitor* getMonitor();


    map<string, sem_t *> *getSemaphores();

    map<string,sem_t*> lockAround(Character character);

    void unlockSemList(map<string, sem_t *> sems);
};

struct thread_Struct
{
	Motor* m;
  int index;
};
#endif
