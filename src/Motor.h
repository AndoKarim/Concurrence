using namespace std;
#include "Character.h"
#include "Plateau.h"
#include <vector>

class Motor{
private :
    int nbPlayers;
    int nbThreads;
    bool needMeasures;
    Plateau plateau;
    vector<Character> listPlayers;

    void createPlayers();


  public :
<<<<<<< HEAD
    Motor(int nbPlayers, int nbthreads);
    void setPlayer(int i,Character c);
=======
    Motor(int nbPlayers, int nbthreads, bool needmeasures);
>>>>>>> 36a75e3c0cfa44dab59e29c19a438e6126ebc7e6
    void printAllPlayers();
    void run();
    Point changePosition(int x, int y);
    bool gameFinished();
    void removeAllPlayers();
    vector<Character> getListPlayers();
    void avancer(int i,Character& p);
    void removePlayer(int i, Character& c);
};
