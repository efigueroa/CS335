/*
player class function bodies
*/

#include "player.h"


player::player()        //constructor for player class
{
  health = 100;
  score = 0;
}
player::~player()
{
  
}


player::getHealth()
{
  return health;
}

player::getMovement(int x, int y)
{
  
}

player::getAmmo()
{
  return ammo;
}
