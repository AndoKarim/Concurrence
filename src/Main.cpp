/*****************************************************************
 * Main.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#include "Motor.h"
#include "OptionChecker.h"
#include <iostream>
#include <math.h>


using namespace std;

void initialisation(int nbPlayers, int nbThreads, bool needMeasures) {
  Motor m = Motor(nbPlayers, nbThreads, needMeasures);
}


int main(int argc, char *argv[]) {
  OptionChecker a = OptionChecker(argc, argv);
  int nbPlayers = (int) pow(2, a.getnbPeople());
  int nbThreads = a.getnbThread();
  bool needMeasures = a.getMeasures();

  cout << "Nb People : " << nbPlayers << endl;
  cout << "Nb Thread : " << nbThreads << endl;

  initialisation(nbPlayers, nbThreads, needMeasures);
}
