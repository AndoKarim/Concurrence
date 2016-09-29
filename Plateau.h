using namespace std;
typedef vector<int> Row; // One row of the matrix
typedef vector<Row> Matrix; // Matrix: a vector of rows
#include "Point.h"
#include "Character.h"
class Plateau{
  private :

  //Site of the Map
  const unsigned WIDTH = 512;
  const unsigned HEIGHT = 128;
  const unsigned WIDTHWALL = 16;
  const unsigned WALLOPENINGHEIGHT1 = 8;
  const unsigned WALLOPENINGHEIGHT2 = 16;
  const unsigned WALLDISTANCE = 112;
  //Initialize all points at 0 (free)
  Matrix grille;
  //const vector< vector<int> > plateau(HEIGHT, vector<int>(WIDTH,0));

  public ://Initialize all points at 0 (free)
    Plateau();
    void setCase(int a, int b);
    int getCase(int a, int b);
    void addWall();
    void printWall();
    bool check(int a, int b);
    Point glimpse(Character c, string direction);
    Point bestTile(string direction);





};
