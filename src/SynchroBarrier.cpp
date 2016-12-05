/*****************************************************************
 * SynchroBarrier.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#include "SynchroBarrier.h"
#include <iostream>
using namespace std;

SynchroBarrier::SynchroBarrier(int i){
    nbThread=i;
    sem_init(&(this->join), 0, 0);
}

void SynchroBarrier::await(){
    nbThread--;
}

void SynchroBarrier::block(){
    while(nbThread!=0){}
    sem_post(&(this->join));
}