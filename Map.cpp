#include <iostream>
#include <string>
<<<<<<< HEAD:Map.cpp

=======
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
 
>>>>>>> 19023694c27127e810ffeebc2919aee180546224:map.cpp
using namespace std;


//Size of the map
<<<<<<< HEAD:Map.cpp


class Map
{
=======
const unsigned WIDTH = 512;
const unsigned HEIGHT = 128;
const unsigned WIDTHWALL = 16;
const unsigned WALLOPENINGHEIGHT1 = 8;
const unsigned WALLOPENINGHEIGHT2 = 16;
const unsigned WALLDISTANCE = 112;
 
vector< vector<bool> > map(HEIGHT, vector<bool>(WIDTH));

class Map
{
    private:

    //typedef vector<vector<bool> >Ground;
    //Ground map(HEIGHT, std::vector<bool> (WIDTH, 0));
 
    //typedef vector<vector<bool> >Grille;
    //Grille g(128, std::vector<bool> (512, false));
    //Initialize all points at 0 (free)
>>>>>>> 19023694c27127e810ffeebc2919aee180546224:map.cpp

    //vector< vector<bool> > map(HEIGHT, vector<bool>(WIDTH));
    

    public:
    // Méthodes
    void Map::addWall()
    {
        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0; j < WIDTHWALL; j++){
                if(i < (HEIGHT-WALLOPENINGHEIGHT1)/2 || i >= (HEIGHT+WALLOPENINGHEIGHT1)/2)
                    map[i][j]=1;
            }
            for(int j = 0+WALLDISTANCE; j < WIDTHWALL+WALLDISTANCE; j++){
                if(i < (HEIGHT-WALLOPENINGHEIGHT2)/2 || i >= (HEIGHT+WALLOPENINGHEIGHT2)/2)
                    map[i][j]=1;
            }
        }
    }

    void printWall()
    {
        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0; j < WIDTH; j++){
                if(map[i][j]==1)
                    printf("IL Y A UN MUR EN %d, %d\n", i,j );
            }
        }
    }

    bool Map::check(int x, int y){
      return map[x][y];
    }

    Point Map::bestTile(string direction){
      //TODO : distance between the arrival and the position of the char.s
    }

     Point Map::glimpse(Character c, string direction){
       //TODO : Same algo for all directions.

      if(direction.compare("left"){}
      if(direction.compare("right"){}
      if(direction.compare("up"){
        int i = xposition-1;
        for(int j = yposition-1 ; j<=y+width; j++){
          bool = check(i,j);
          if(bool){
            return Point(c.getX(), c.getY());
          }
        }
        return bestTile();
      }
      if(direction.compare("down"){}

    }
};

int main()
{
<<<<<<< HEAD:Map.cpp
    Personnage david, goliath;
    //Création de 2 objets de type Personnage : david et goliath

    goliath.attaquer(david);    //goliath attaque david
    david.boirePotionDeVie(20); //david récupère 20 de vie en buvant une potion
    goliath.attaquer(david);    //goliath réattaque david
    david.attaquer(goliath);    //david contre-attaque... c'est assez clair non ?

    goliath.changerArme("Double hache tranchante vénéneuse de la mort", 40);
    goliath.attaquer(david);

=======
    Map map1;

    map1.addWall();
    map1.printWall();
>>>>>>> 19023694c27127e810ffeebc2919aee180546224:map.cpp

    return 0;
}
