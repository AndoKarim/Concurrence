/*****************************************************************
 * Main.cpp
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

#include "Motor.h"
#include "OptionChecker.h"
#include <iostream>
#include <math.h>

//#include <SFML/Graphics.hpp>


using namespace std;

void initialisation(int nbPlayers, int nbThreads, bool needMeasures, int phase) {
  //TODO: Add the arg phase on the motor constructor
  Motor m = Motor(nbPlayers, nbThreads, needMeasures, phase);
}


int main(int argc, char *argv[]) {
  /*sf::RenderWindow window(sf::VideoMode(640,480,32),"Hello SFML");

  sf::Font font;
  font.loadFromFile("OpenSans-Bold.ttf");

  sf::Text text("Hello World",font,11);
  text.setCharacterSize(32);
  text.setPosition(window.getSize().x/2 - text.getGlobalBounds().width/2,
                   window.getSize().y/2 - text.getGlobalBounds().height/2);


  while(window.isOpen()){

    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed){
        window.close();
      }

      window.clear(sf::Color::Black);
      window.draw(text);
      window.display();
    }
  }
  return 0;*/
//}

OptionChecker a = OptionChecker(argc, argv);
  int nbPlayers = (int) pow(2, a.getnbPeople());
  int nbThreads = a.getnbThread();
  bool needMeasures = a.getMeasures();
  int nbPhase = a.getnbPhase();

  cout << "Nb People : " << nbPlayers << endl;
  cout << "Nb Thread : " << nbThreads << endl;

  initialisation(nbPlayers, nbThreads, needMeasures, nbPhase);
}
