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
    float measuresTab[3];
    long maxResident;
    time_t time;

    void createPlayers();


  public :
    Motor(int nbPlayers, int nbthreads);
    void setPlayer(int i,Character c);
    Motor(int nbPlayers, int nbthreads, bool needmeasures);
    void printAllPlayers();
    void run();
    Point changePosition(int x, int y);
    bool gameFinished();
    void removeAllPlayers();
    vector<Character> getListPlayers();
    void avancer(int i,Character& p);
    void removePlayer(int i, Character& c);
};

struct thread_Struct
{
	Motor* m;
	Character c;
  int index;
};
