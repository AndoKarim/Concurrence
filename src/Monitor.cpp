/*****************************************************************
 * Monitor.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#include "Monitor.h"
#include <iostream>
#include <cstdio>
using namespace std;


Monitor::Monitor(){

    availableZoneNO=1;
    pthread_mutex_t lock1;
    if (pthread_mutex_init(&lock1, NULL) != 0)
    {
        cout<<"Impossible d'initialisé le mutex"<<endl;
        exit(1);
    }
    pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
    zoneNO=make_pair(lock1,cond1);

    availableZoneNE=1;
    pthread_mutex_t lock2;
    if (pthread_mutex_init(&lock2, NULL) != 0)
    {
        cout<<"Impossible d'initialisé le mutex"<<endl;
        exit(1);
    }
    pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
    zoneNE=make_pair(lock2,cond2);

    availableZoneSO=1;
    pthread_mutex_t lock3;
    if (pthread_mutex_init(&lock3, NULL) != 0)
    {
        cout<<"Impossible d'initialisé le mutex"<<endl;
        exit(1);
    }
    pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
    zoneSO=make_pair(lock3,cond3);

    availableZoneSE=1;
    pthread_mutex_t lock4;
    if (pthread_mutex_init(&lock4, NULL) != 0)
    {
        cout<<"Impossible d'initialisé le mutex"<<endl;
        exit(1);
    }
    pthread_cond_t cond4 = PTHREAD_COND_INITIALIZER;
    zoneSE=make_pair(lock4,cond4);
}

Monitor::Monitor(pthread_cond_t* cond,pthread_mutex_t& mutex){
    cond=cond;
    mutex=mutex;
    availableCharacter=1;
}