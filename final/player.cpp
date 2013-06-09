class Player
{
  public:          
  int score;
  int life;
  double pos;
  double left;
  double right;
  double marg;
    
  public:     
  Player()
  {
   life=10;
   score=0;
   pos=0.0;
   marg = 2.0;
   left = pos - marg;
   right = pos + marg;
  }
      
  int kill()
  {
    score += 10;
  }
  
  int getScore()
  {
    return score;
  }
  
  void addPos(double p)
  {
    pos+=p;
    usleep(1000);
    left = pos+marg;
    right =pos+marg;
  }
  
  void minPos(double p)
  {
    pos -= p;
    usleep(1000);
    left = pos - marg;
    right= pos - marg;
  }
  void setPos(double c) 
  {
    pos=c;
    left = pos-marg;
    right= pos+marg;
  }

  double getPos()
  {
    return pos;
  }
};















