//
// Created by anasse on 04/12/16.
//

#include "SynchroBarrier.h"
#include <iostream>
using namespace std;

SynchroBarrier::SynchroBarrier(int i){
    nbThread=i;
    sem_init(&(this->join), 0, 0);
}

void SynchroBarrier::await(){
    nbThread--;
    cout<<"Encore "<<nbThread<<" threads à attendre"<<endl;
}

void SynchroBarrier::block(){
    while(nbThread!=0){}
    cout<<"\nTous le monde est a la barriere"<<endl;
    sem_post(&(this->join));
}