#include "Graph.h"
#include <iostream>
#include <unistd.h>
#include "Motor.h"


void Graph::print(void *p_data) {
  cout << ">> debut thread graphique" << endl;
  if (p_data != nullptr) {
    Motor *m = (Motor *) p_data;
    Plateau *ptr_plateau = m->getPlateau();
    sf::RenderWindow window(sf::VideoMode(512, 128), "Titre");
    window.clear(sf::Color(214, 214, 214));

    sf::Color black = sf::Color::Black;
    sf::Color white = sf::Color::White;
    sf::Color red = sf::Color::Red;

    while (window.isOpen() && !m->gameFinished()) {
      if (m->gameFinished()) {
        break;
      }
      window.clear();
      for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 128; j++) {
          sf::RectangleShape rectangle;
          rectangle.setSize(sf::Vector2f(1, 1)); // Taille (1x1)
          rectangle.setPosition(i, j); //Position sur l'écran");
          //sa couleur :
            int test = ptr_plateau->getCase(i,j).isOccupied;
          switch (test) {
            case 2 :
              rectangle.setFillColor(black);
              break;
            case 1 :
              rectangle.setFillColor(red);
              break;

          }
          window.draw(rectangle);

        }
      }
        cout << "nn"<<endl;
      window.display();
        cout << "nnnok"<<endl;
        cout << m->nbP() <<endl;
    }
    cout << "la simulation est terminée" << endl;
    window.close();
    //}
  } else {
    cout << "problème dans la récupération du contexte applicatif du thread (affichage graphique)" << endl;
  }
  cout << ">> fin du thread graphique" << endl;
}



