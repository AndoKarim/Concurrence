using namespace std;
#include "Point.h"
#include "Character.h"

class Map{
  private :

  //Site of the Map
  const unsigned WIDTH = 512;
  const unsigned HEIGHT = 128;
  const unsigned WIDTHWALL = 16;
  const unsigned WALLOPENINGHEIGHT1 = 8;
  const unsigned WALLOPENINGHEIGHT2 = 16;
  const unsigned WALLDISTANCE = 112;
  //Initialize all points at 0 (free)
  const vector< vector<int> > map(HEIGHT, vector<int>(WIDTH,0));


  public ://Initialize all points at 0 (free)
    Map();
    void addWall();
    void printWall();
    bool check(int a, int b);
    Point glimpse(Character c, string direction);
    Point bestTile(string direction);





};
