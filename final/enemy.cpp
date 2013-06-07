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
      usleep(rand()%10000+800); 
      double x=(rand()%8000-4000)/1000.0; //rand double 
      xPos = x;
      
      //rand y coord
      usleep(rand()%10000+800);
      double y=(rand()%60000)/1000.0;
      yPos = y; 
      while (yPos < 9)
      {
        usleep(rand()%10000+800);
        yPos =(rand()%60000)/1000.0;
      }
        
    }

    void setX(double x) 
    {
      xPos=x;
    }

    void setY(double y)
    {
      yPos=y;
    }

    void reset()
    {
      while(yPos<10.0)
      yPos=(rand()%60000)/1000.0;
      xPos=(rand()%8000-4000)/1000.0;
      
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
      
