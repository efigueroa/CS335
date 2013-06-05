class Enemy {

  public:
    int health;
    bool alive;
    float xPos;
    float yPos;

  public:
    Enemy()
    {
      health = 1;
      alive = true;
      
      //rand x coord
      usleep(rand()%10000+800); //good enough sleep period (microseconds)
      float x=(rand()%8000-4000)/1000.0; //rand float 
      xPos = x;
      
      //rand y coord
      usleep(rand()%10000+800);
      float y=(rand()%60000)/1000.0;
      yPos = y; //9.7 is just above top of screen
      //as of now less than -4.5 means it touched the wall, GAME OVER
    }

    void setX(float x) 
    {
      xPos=x;
    }

    void setY(float y)
    {
      yPos=y;
    }

    void resetY()
    {
      usleep(rand()%10000+800);
      yPos=(rand()%60000)/1000.0;
      
    }
    
  float getPos()
  {
    return xPos;
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
      
