#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
 
using namespace std;

//Size of the map
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

    //vector< vector<bool> > map(HEIGHT, vector<bool>(WIDTH));
    

    public:
    // Méthodes
    void addWall()
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
};
 
int main()
{
    Map map1;

    map1.addWall();
    map1.printWall();

    return 0;
}