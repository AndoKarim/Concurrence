class Character {
  private:
    const int width = 8;
    const int height = 8;
    int xPosition;
    int yPosition;

  public:
    Character(int w,int h, int x, int y);
    // void move(string direction);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
};
