using namespace std;
#include "Character.h"
#include "Plateau.h"
#include <vector>

class Motor{
private :
    int nbPlayers;
    int nbThreads;
    Plateau plateau;
    vector<Character> listPlayers;

    void createPlayers();


  public :
    Motor(int nbPlayers, int nbthreads);
    void setPlayer(int i,Character c);
    void printAllPlayers();
    void run();
    Point changePosition(int x, int y);
    bool gameFinished();
    void removeAllPlayers();
    vector<Character> getListPlayers();
    void avancer(int i,Character& p);
    void removePlayer(int i, Character& c);
};
