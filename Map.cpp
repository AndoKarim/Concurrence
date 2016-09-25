#include <iostream>
#include <string>

using namespace std;


//Size of the map


class Map
{

    // Méthodes
    void Map::addWall()
    {
        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0; j < WIDTHWALL; j++){
                if(i != WALLOPENINGHEIGHT1)
                    map[i][j]=1;
            }
        }

        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0+WALLDISTANCE; j < WIDTHWALL+WALLDISTANCE; j++){
                if(i != WALLOPENINGHEIGHT2)
                    map[i][j]=1;
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
    Personnage david, goliath;
    //Création de 2 objets de type Personnage : david et goliath

    goliath.attaquer(david);    //goliath attaque david
    david.boirePotionDeVie(20); //david récupère 20 de vie en buvant une potion
    goliath.attaquer(david);    //goliath réattaque david
    david.attaquer(goliath);    //david contre-attaque... c'est assez clair non ?

    goliath.changerArme("Double hache tranchante vénéneuse de la mort", 40);
    goliath.attaquer(david);


    return 0;
}
