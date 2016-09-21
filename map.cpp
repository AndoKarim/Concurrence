#include <iostream>
#include <string>
 
using namespace std;

//Size of the map
const unsigned WIDTH = 512;
const unsigned HEIGHT = 128;
const unsigned WIDTHWALL = 16;
const unsigned WALLOPENINGHEIGHT1 = 8;
const unsigned WALLOPENINGHEIGHT1 = 16;
const unsigned WALLDISTANCE = 112;
 
class map
{
    //Initialize all points at 0 (free)
    vector< vector<int> > map(HEIGHT, vector<int>(WIDTH,0));

    // Méthodes
    void addWall()
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