#include <iostream>
#include <string>


#include "Plateau.h"

using namespace std;

//TODO : If -t1, create a new constructor which gonna creates threads for diferent parts of the plateau.Else, create just a simple plateau

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

    // Point Plateau::bestTile(string direction){
    //   //TODO : distance between the arrival and the position of the char.s
    // }

    //  Point Plateau::glimpse(Character c, string direction){
    //    //TODO : Same algo for all directions.
    //
    //   // if(direction.compare("left"))
    //   // if(direction.compare("right"))
    //   // if(direction.compare("up")){
    //   //   int i = xposition-1;
    //   //   for(int j = yposition-1 ; j<=y+width; j++){
    //   //     bool = check(i,j);
    //   //     if(bool){
    //   //       return Point(c.getX(), c.getY());
    //   //     }
    //   //   }
    //   //   return bestTile();
    //   // }
    //   // if(direction.compare("down"))
    //
    // }
