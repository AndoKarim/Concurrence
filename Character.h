class Character {
  private:
    int width;
    int height;
    int xPosition;
    int yPosition;

  public:
    Character(int w,int h, int x, int y);
    void move();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
};
