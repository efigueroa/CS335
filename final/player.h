class Player
{
  private:          
  int score;
  float pos;
    
  public:      
  Player()
  {
   score=0;
   pos=0.0;
  }
      
  int kill()
  {
    score += 1;
  }
  void addPos(float p)
  {
    pos+=p;
  }
   void minPos(float p)
  {
    pos-=p;
  }
  void setPos(float c) 
  {
    pos=c;
  }

  float getPos()
  {
    return pos;
  }
  


};
