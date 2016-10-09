using namespace std;
#include "Character.h"
#include "Plateau.h"
#include <list>

class Motor{
private :
    int nbPlayers;
    int nbThreads;
    bool needMeasures;
    Plateau plateau;
    list<Character> listPlayers;

    void createPlayers();

  public :
    Motor(int nbPlayers, int nbthreads, bool needmeasures);
    void printAllPlayers();
    void run();
    Point changePosition(int x, int y);
};
