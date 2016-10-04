#include "Motor.h"
#include "OptionChecker.h"
#include <iostream>
#include <math.h>



using namespace std;

void initialisation(int nbPlayers, int nbThreads){
  Motor m = Motor(nbPlayers,nbThreads);

}


int main(int argc, char *argv[]) {
  OptionChecker a = OptionChecker(argc,argv);

  int nbPlayers = (int)pow(2,a.getnbPeople());
  int nbThreads = a.getnbThread();

  cout << "Nb People : " << nbPlayers << endl;
  cout << "Nb Thread : " << nbThreads << endl;

  initialisation(nbPlayers, nbThreads);

}
