/*****************************************************************
 * OptionChecker.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#include <iostream>
#include "OptionChecker.h"

using namespace std;


OptionChecker::OptionChecker(int argc, char *argv[]) {
  OptionChecker::parameterFiller(argc, argv);
  OptionChecker::parameterChecker();
  cout << "Parameter test OK" << endl;

}

bool OptionChecker::checkThread(int thread) {
  return (thread >= 0 && thread < 3);
}

bool OptionChecker::checkPeople(int people) {
  return (people >= 0 && people < 10);
}

bool OptionChecker::checkPhase(int phase) {
  //To be changed when 3rd phase is on track
  return phase >0 && phase <=3 ;
}

void OptionChecker::parameterFiller(int nbArgs, char *parameters[]) {
  extern char *optarg;
  int c;
  while ((c = getopt(nbArgs, parameters, PARAM_MASK)) != -1) {
    switch (c) {
      case 'p':
        peopleArg = 1;
        nbPeople = atoi(optarg);
        break;
      case 't':
        threadArg = 1;
        nbThread = atoi(optarg);
        break;
      case 'm':
        measures = 1;
        break;
      case 'e':
        phaseArg = atoi(optarg);
    }
  }
}

void OptionChecker::parameterChecker() {
  if (!peopleArg) {
    cerr << "No people parameter" << endl;
    exit(1);
  }
  if (!threadArg) {
    cerr << "No thread parameter" << endl;
    exit(1);
  }

  if(!phaseArg){
    cerr << "No Phase parameter" << endl;
    exit(1);
  }

  if (peopleArg) {
    if (threadArg) {
      if (!checkThread(nbThread)) {
        cerr << "Parameter of thread invalid" << endl;
        exit(1);
      }
      if (!checkPeople(nbPeople)) {
        cerr << "Number of people invalid" << endl;
        exit(1);
      }
      if(!checkPhase(phaseArg)){
        cerr << "Parameter of phase invalid" << endl;
        exit(1);
      }
    }
  }
}

int OptionChecker::getnbPeople() {
  return nbPeople;
}

int OptionChecker::getnbThread() {
  return nbThread;
}


bool OptionChecker::getMeasures() {
  if(measures==0)
    return false;
  return true;
}

int OptionChecker::getnbPhase(){
  return phaseArg;
}