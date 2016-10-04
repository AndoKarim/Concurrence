#include <iostream>
#include <string>


#include "Plateau.h"

using namespace std;

//TODO : If -t1, create a new constructor which gonna creates threads for diferent parts of the plateau.Else, create just a simple plateau

  Plateau::Plateau(){
    grille = Matrix(HEIGHT,Row(WIDTH));
    this->initialize();
  }

  void Plateau::initialize(){
  }

  void Plateau::setCase(int x, int y){
    grille[y][x] = 1;
  }

  int Plateau::getCase(int x, int y){
    return grille[y][x];
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
      return grille[y][x];
    }

    bool Plateau::checkCase(int x, int y){
      if(x < 0 || y < 0)
		    return false;
	    if(x + 3 > 511)
		    return false;
	    if(y + 3 > 127)
		    return false;

	    for(int pos_x = 0; pos_x < 4; pos_x++){
		      for(int pos_y = 0; pos_y < 4; pos_y++){
			         if(this->grille[y+pos_y][x+pos_x] == 1 || this->grille[y=pos_y][x+pos_x] == 2 ){
                 cerr << "impossible to add at this position" << endl;
					       return false;
              }
		      }
	    }
      return true;
    }

    bool Plateau::addPlayer(int x, int y){

      if(!this->checkCase(x,y))
        return false;

      for(int pos_x = 0; pos_x < 4; pos_x++){
		      for(int pos_y = 0; pos_y < 4; pos_y++){
			         this->grille[y][x] = 2;
		      }
	    }
      cout << "added successfully" << endl;
	    return true;
    }

    Plateau &Plateau::operator=(const Plateau &other){
      this->grille = other.grille;
      return *this;
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
