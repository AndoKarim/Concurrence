#include "Point.h"
class Character {
  private:
    const int width = 8;
    const int height = 8;
    Point position;

  public:
    Character();
    Character(int x, int y);
    Character(Point p);
     void move(Point p);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
};
