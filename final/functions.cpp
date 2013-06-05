/* Various Functions called from main
 */

#include <GL/glfw.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "enemy.cpp"
#include "functions.h"
#include "player.h"
#include "math.h"

using namespace std;

extern float moveX;                   //player movement
extern float movTick;
extern GLuint backTexture;
const int MAXENEMY = 5;
extern double oldTime;
float LEVEL = .05;
bool beamFlag = 0;

Enemy* baddy = new Enemy[MAXENEMY];
Player* hero = new Player();


void drawEn(int enmy = 0){

  float d = 15;
  glPushMatrix();
  glTranslatef(baddy[enmy].xPos,baddy[enmy].yPos,0);
  glRotatef(180,0,0,1);
 glBegin(GL_TRIANGLES);
 {
   glColor3f(1,0,0); //red
   glVertex3f(-1,-1,-d);
   glVertex3f(1,-1,-d);
   glVertex3f(0,1,-d);
   
  }
  glEnd();
  glPopMatrix();
  
}

void moveEn()
{
  double currTime = glfwGetTime();

  for(int i=0;i<MAXENEMY;i++) {
    baddy[i].yPos  += -LEVEL;
    //cout << -LEVEL << endl;

    if(baddy[i].yPos <= -4.5) 
    {
      baddy[i].resetY();
    }
  }
 
}

void drawBeam()
{
 
  glPushMatrix();
  glTranslatef(hero->getPos(),-3.5,0); 
  
  float f=9;
  glBegin(GL_QUADS);
  {
    
    glColor3f(1, 1,1);    //white
    //glColor3f(1, 0, 0);
    glVertex3f(0, 9.5, -f); //red
    //glColor3f(0, 1, 0);
    glVertex3f(0, 5, -f);  //green
    //glColor3f(0, 0, 1);   //blue
    glVertex3f(.05, -.8, -f);
    //glColor3f(1, 1,1);    //white
    glVertex3f(-.05, -.8, -f);
  }
  glEnd();
  glPopMatrix();
  
}

void shoot()
{
  float min = 0.0,      //low 
        max = 0.0,      //high
        normal = 15.0,  //normalize
        margin = .7;    //margin of error

  for(int i=0;i<MAXENEMY;i++) 
  {
    //reset low/
    min = max = 0; 
    //to avoid negative positions, normalize and add 15.0 which is
    //bigger than the screen size. Then sub/add the margin of error
    min = (normal + baddy[i].getxPos()) - margin;
    max = (normal + baddy[i].getxPos()) + margin;

    if(min <= (normal + hero->getPos()) <= max)
    {
      //baddy[i].resetY();
      //hero->kill();
    }
    /*
    cout << min << endl;
    cout << (15.0 + hero->getPos()) << endl;
    cout << max << endl << endl;
    */
  }

}
 
void keyHandler()
{
      if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
      {
          glfwTerminate();
        	exit(EXIT_SUCCESS);
      }
      if (glfwGetKey('A') == GLFW_PRESS)
      {
      if(hero->getPos() >= 4) 
      { //dont move it further 
      }
      else
      {
        hero->addPos(movTick*2);
      }
    }
    
    /*if(glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS) 
    {
      shoot(); 
      beamFlag=1;
      cout << "BEAM!\n";  
    } */   

    if(glfwGetKey('D') == GLFW_PRESS) //right movement
    {
      //printf("%f\n",moveX);
      if(hero->getPos() <= -4) 
      {  
      }
      else
      {
        hero->minPos(movTick*2);
      }
    }
    if(glfwGetKey('Q') == GLFW_PRESS)  //reserved as debug keys
    {

    }
    if(glfwGetKey('E') == GLFW_PRESS)  //reserved as debug keys    
    {
	  
    }
}
  


void updateEnemy() 
{

  moveEn();
  for(int i = 0;i<MAXENEMY;i++) 
  {
    drawEn(i);    
  }
  //check if it hit the wall
  for(int i = 0;i<MAXENEMY;i++) 
  {
       
  }
}


void shutDown(int return_code)
{
  glfwTerminate();
  exit(return_code);
}

void drawPlayer() {

  glPushMatrix();
  glTranslatef(hero->getPos(),-4.5,0); //move left+down and draw this quad

  float e=.4,f=9;;
  glBegin(GL_QUADS);
  {
    glColor3f(0.07, 0.24, 0.67); //
    glVertex3f(-e, e, -f);
    glVertex3f(e, e, -f);
    glVertex3f(e, -e, -f);
    glVertex3f(-e, -e, -f);
  }
  glEnd();
  glPopMatrix();

}



void drawWall() {

  glPushMatrix();
  glTranslatef(0,-4,0);
  float d = 10;
  glBegin(GL_QUADS); 
  {
    glColor3f(0.15, 0.84,0 ); 
    glVertex3f(-6, 0.3, -d);
    glVertex3f(6, 0.3, -d);
    glVertex3f(6, -0.3, -d);
    glVertex3f(-6,-0.3, -d);
  }
  glEnd();
  glPopMatrix();

}


void render()
{

  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /*
  //background texture
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, backTexture);
  glBegin(GL_QUADS);
  {
    glTexCoord2f(0,0); glVertex2i(100, 500);
    glTexCoord2f(0,1); glVertex2i(100, 600);
    glTexCoord2f(1,1); glVertex2i(200, 600);
    glTexCoord2f(1,0); glVertex2i(200, 100);
  }
  glEnd();
  glPopMatrix();
*/

  
  drawWall();
  updateEnemy();
  if(beamFlag==1)
  {
      cout << "BEAM " << beamFlag << endl;
    cout << "BEAM!\n";
    drawBeam();
    usleep(3000);
    beamFlag=0;
  }
  drawPlayer();
  glfwSwapBuffers();
  glfwPollEvents();
}

void GLFWCALL keyCallBack(int key, int action) 
{
  
  if(key == GLFW_KEY_ESC && action == GLFW_PRESS)
    shutDown(0);

  //Player movement, left and right only
  {
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) 
    {
      shoot(); 
      beamFlag=1;
      cout << "BEAM!\n";  
    } 
        
  }
}


void init(int window_height, int window_width)
{
  //big block of glfw stuff
  if (glfwInit() != GL_TRUE)
    shutDown(1);

  if (glfwOpenWindow(window_width, window_height, 5, 6, 5, 0, 0, 0, GLFW_WINDOW) != GL_TRUE)
    shutDown(1);

  glfwSetWindowPos(500,100);


  glfwSetWindowTitle("FlatLander: Prevent the Uprising");
  glfwSetKeyCallback(keyCallBack);

  // set the projection matrix to a normal frustum with a max depth of 50
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect_ratio = ((float)window_height) / window_width;
  glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
  glMatrixMode(GL_MODELVIEW);


  glClearColor(0,0,0,1);
  glClearDepth(1);
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_COLOR_MATERIAL);


  glDisable(GL_LIGHTING);

  //texture loading
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  //backTexture = loadBMP("background.bmp");
  //printf("Texture %i",backTexture);

  //other inits
  //InitEnemies();
}


