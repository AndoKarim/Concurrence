//
// Created by anasse on 04/12/16.
//

#ifndef PROJET_MONITOR_H
#define PROJET_MONITOR_H

#include <pthread.h>
#include <atomic>
#include <utility>

using namespace std;

class Monitor{


public:
    pair<pthread_mutex_t,pthread_cond_t> zoneNO;
    pair<pthread_mutex_t,pthread_cond_t> zoneNE;
    pair<pthread_mutex_t,pthread_cond_t> zoneSO;
    pair<pthread_mutex_t,pthread_cond_t> zoneSE;

    std::atomic<int> availableZoneNO;
    std::atomic<int> availableZoneNE;
    std::atomic<int> availableZoneSO;
    std::atomic<int> availableZoneSE;


    pthread_cond_t* cond;
    pthread_mutex_t mutex;
    std::atomic<int> availableCharacter;

    Monitor();
    Monitor(pthread_cond_t* cond,pthread_mutex_t& mutex);

};
#endif
