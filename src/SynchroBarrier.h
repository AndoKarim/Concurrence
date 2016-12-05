/*****************************************************************
 * SynchroBarrier.h
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#ifndef PROJET_SYNCHROBARRIER_H
#define PROJET_SYNCHROBARRIER_H
#include <atomic>
#include <semaphore.h>



class SynchroBarrier{
private:
    std::atomic<int> nbThread;
    sem_t join;
public:
    SynchroBarrier(int i);
    void await();
    void block();
};
#endif
