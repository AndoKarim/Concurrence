class Map{
  private :

  //Site of the Map
  const unsigned WIDTH = 512;
  const unsigned HEIGHT = 128;
  const unsigned WIDTHWALL = 16;
  const unsigned WALLOPENINGHEIGHT1 = 8;
  const unsigned WALLOPENINGHEIGHT1 = 16;
  const unsigned WALLDISTANCE = 112;
  //Initialize all points at 0 (free)
  const vector< vector<int> > map(HEIGHT, vector<int>(WIDTH,0));


  public ://Initialize all points at 0 (free)
    Map();
    void addWall();
    bool check();
    Point glimpse(string direction);
    Point bestTile();





}
