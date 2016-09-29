#include <iostream>
#include <string>

#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

#include "Plateau.h"

using namespace std;

    //typedef vector<vector<bool> >Ground;
    //Ground plateau(HEIGHT, std::vector<bool> (WIDTH, 0));

    //typedef vector<vector<bool> >Grille;
    //Grille g(128, std::vector<bool> (512, false));
    //Initialize all points at 0 (free)

    //vector< vector<bool> > plateau(HEIGHT, vector<bool>(WIDTH));


  Plateau::Plateau(){
    grille = Matrix(HEIGHT,Row(WIDTH));
  }

  void Plateau::setCase(int x, int y){
    grille[x][y] = 1;
  }

  int Plateau::getCase(int x, int y){
    return grille[x][y];
  }



    void Plateau::addWall()
    {
        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0; j < WIDTHWALL; j++){
                if(i < (HEIGHT-WALLOPENINGHEIGHT1/2 || i >= (HEIGHT+WALLOPENINGHEIGHT1/2)))
                    grille[i][j]=1;
            }
            for(int j = 0+WALLDISTANCE; j < WIDTHWALL+WALLDISTANCE; j++){
                if(i < (HEIGHT-WALLOPENINGHEIGHT2)/2 || i >= (HEIGHT+WALLOPENINGHEIGHT2)/2)
                    grille[i][j]=1;
            }
        }
    }

    void Plateau::printWall()
    {
        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0; j < WIDTH ; j++){
                if(grille[i][j]==1)
                    printf("IL Y A UN MUR EN %d, %d\n", i,j );
            }
        }
    }

    bool Plateau::check(int x, int y){
      return grille[x][y];
    }

    Point Plateau::bestTile(string direction){
      //TODO : distance between the arrival and the position of the char.s
    }

     Point Plateau::glimpse(Character c, string direction){
       //TODO : Same algo for all directions.

      // if(direction.compare("left"))
      // if(direction.compare("right"))
      // if(direction.compare("up")){
      //   int i = xposition-1;
      //   for(int j = yposition-1 ; j<=y+width; j++){
      //     bool = check(i,j);
      //     if(bool){
      //       return Point(c.getX(), c.getY());
      //     }
      //   }
      //   return bestTile();
      // }
      // if(direction.compare("down"))

    }

int main()
{
    // Personnage david, goliath;
    // //Création de 2 objets de type Personnage : david et goliath
    //
    // goliath.attaquer(david);    //goliath attaque david
    // david.boirePotionDeVie(20); //david récupère 20 de vie en buvant une potion
    // goliath.attaquer(david);    //goliath réattaque david
    // david.attaquer(goliath);    //david contre-attaque... c'est assez clair non ?
    //
    // goliath.changerArme("Double hache tranchante vénéneuse de la mort", 40);
    // goliath.attaquer(david);

    // plateau plateau1;
    //
    // plateau1.addWall();
    // plateau1.printWall();

    Plateau  p = Plateau();
    p.addWall();
    p.printWall();

    return 0;
}
