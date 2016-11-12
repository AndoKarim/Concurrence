/*****************************************************************
 * Plateau.h
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/
 #ifndef PLATEAU_H
 #define PLATEAU_H

#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <semaphore.h>


using namespace std;
typedef vector<struct struct_Mutex> Row; // One row of the matrix
typedef vector<Row> Matrix; // Matrix: a vector of rows

class Plateau{
  private :

  //Size of the Map
  const unsigned WIDTH = 512;
  const unsigned HEIGHT = 128;
  const unsigned WIDTHWALL = 16;
  const unsigned WALLOPENINGHEIGHT1 = 8;
  const unsigned WALLOPENINGHEIGHT2 = 16;
  const unsigned WALLDISTANCE = 112;
  const unsigned XAZIMUT = 0;
  const unsigned YAZIMUT = 63;
  const unsigned WIDTHLASTWALL = 128;
  //Initialize all points at 0 (free)
  Matrix grille;
  void initialize();

  public :
    Plateau();
    struct struct_Mutex getCase(int a, int b);
    void addWall();
    void printWall();
    bool addPlayer(int x, int y);
    int check(int a, int b);
    bool checkCase(int x, int y);
    int getXAzimut();
    int getYAzimut();
    int getHeigth();
    int getOpenHeigthWall1();
    int getOpenHeigthWall2();
    int getWidthLastWall();
    bool movePlayer(int x, int y, int new_x, int new_y);
    void printAllPlayersCases();
    void removePlayer(int x, int y);



    // clone
    Plateau& operator=(const Plateau&);

};

struct struct_Mutex
{
    int isOccupied;
    sem_t* mutex;
};
#endif
