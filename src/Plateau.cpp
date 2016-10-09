#include <iostream>
#include <string>


#include "Plateau.h"

using namespace std;

//TODO : If -t1, create a new constructor which gonna creates threads for diferent parts of the plateau.Else, create just a simple plateau

  Plateau::Plateau(){
    grille = Matrix(HEIGHT,Row(WIDTH));
    this->addWall();
  }

  void Plateau::initialize(){
  }

  void Plateau::setCase(int x, int y, int value){
    grille[y][x] = value;
  }

  int Plateau::getCase(int x, int y){
    return grille[y][x];
  }



    void Plateau::addWall()
    {
        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0; j < WIDTHWALL; j++){
                if(i < (HEIGHT-WALLOPENINGHEIGHT1)/2 || i >= (HEIGHT+WALLOPENINGHEIGHT1)/2)
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
			         if(this->grille[y+pos_y][x+pos_x] == 1 || this->grille[y+pos_y][x+pos_x] == 2 ){
                 cerr << "impossible to add at this position" << endl;
					       return false;
              }
		      }
	    }
      return true;
    }

    bool Plateau::movePlayer(int x, int y, int new_x, int new_y){
      if(x > 0 && y > 0 && x + 3 < 511 && y + 3 < 127){
        removePlayer(x,y);
        if(!addPlayer(new_x,new_y)){
          addPlayer(x,y);
          cout<< "impossible to move player"<< endl;
          return false;
        }
          return true;
      }
    }

    bool Plateau::addPlayer(int x, int y){

      if(!this->checkCase(x,y))
        return false;

      for(int delta_y = 0; delta_y < 4; delta_y++){
        for(int delta_x = 0; delta_x < 4; delta_x++){
		         this->grille[y+delta_y][x+delta_x] = 2;
		      }
	    }
      cout << "added successfully" << endl;
	    return true;
    }

    void Plateau::removePlayer(int x, int y){
      for(int delta_y = 0; delta_y < 4; delta_y++){
        for(int delta_x = 0; delta_x < 4; delta_x++){
		         this->grille[y+delta_y][x+delta_x] = 0;
		      }
	    }
    }

    Plateau &Plateau::operator=(const Plateau &other){
      this->grille = other.grille;
      return *this;
    }

    void Plateau::printAllPlayersCases(){
      int count = 0;
      for(int i = 0; i < HEIGHT; i++){
          for(int j = 0; j < WIDTH ; j++){
              if(grille[i][j]==2){
                  printf("IL Y A UNE PERSONNE EN %d, %d\n", j,i );
                  count ++;
              }
          }
      }
      cout << count/16 << endl;

    }


    int Plateau::getXAzimut(){
      return XAZIMUT;
    }

    int Plateau::getYAzimut(){
      return YAZIMUT;
    }

    int Plateau::getHeigth(){
      return HEIGHT;
    }

    int Plateau::getOpenHeigthWall1(){
      return WALLOPENINGHEIGHT1;
    }

    int Plateau::getOpenHeigthWall2(){
      return WALLOPENINGHEIGHT2;
    }

    int Plateau::getWidthLastWall(){
      return WIDTHLASTWALL;
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
