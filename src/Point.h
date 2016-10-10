/*****************************************************************
 * Point.h
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

class Point {
  private:
    int x;
    int y;

  public:
    Point();
    Point(int a, int b);
    void print();
    int getX();
    int getY();
};
