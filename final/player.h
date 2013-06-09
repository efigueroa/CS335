class Player
{
  private:          
  int score;
  double pos;
  double margin;
  int life;
  public:
  double left;
  double right;
    
  public:      
  Player(int m)
  {
   life=10;
   score=0;
   pos=0.0;
   margin = m;
   left = pos - margin;
   right = pos + margin;
  }
      
  int kill()
  {
    score += 1;
  }
  int getScore()
  {
    return score;
  }
  void addPos(double p)
  {
    pos+=p;
    left=pos-margin;
    right=pos+margin;
  }
   void minPos(double p)
  {
    pos-=p;
        left=pos-margin;
    right=pos+margin;
  }
  void setPos(double c) 
  {
    pos=c;
    left=pos-margin;
    right=pos+margin;
  }

  double getPos()
  {
    return pos;
  }
  


};
