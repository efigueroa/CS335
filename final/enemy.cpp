class Enemy {

  public:
    int health;
    int state;
    double xPos;
    double yPos;
    double deathPos;

  public:
    Enemy()
    {
      health = 1;
      state = 0;
      
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


    int hearts() 
    {
      return health;
    }
    
};
      
