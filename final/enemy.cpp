class Enemy {

  public:
    int health;
    bool alive;
    double xPos;
    double yPos;

  public:
    Enemy()
    {
      health = 1;
      alive = true;
      
      //rand x coord
      usleep(rand()%10000+800); //good enough sleep period (microseconds)
      double x=(rand()%8000-4000)/1000.0; //rand double 
      xPos = x;
      
      //rand y coord
      usleep(rand()%10000+800);
      double y=(rand()%60000)/1000.0;
      yPos = y; //9.7 is just above top of screen
      //as of now less than -4.5 means it touched the wall, GAME OVER
    }

    void setX(double x) 
    {
      xPos=x;
    }

    void setY(double y)
    {
      yPos=y;
    }

    void resetY()
    {
      yPos=(rand()%60000)/1000.0;
      
    }
    
  double getxPos()
  {
    return xPos;
  }
  
    double getyPos()
  {
    return yPos;
  }
    bool isAlive() 
    {
      return alive;
    }

    int hearts() 
    {
      return health;
    }
    
};
      
