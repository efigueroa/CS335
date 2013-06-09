#include <GL/glfw.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include "math.h"

//mine
#include "enemy.cpp"
#include "functions.h"
#include "player.cpp"

//gordons
#include "defs.h"
#include "fonts.h"
#include "bmp.c"


using namespace std;

extern double moveX;      //player movement
extern double movTick;    //object movement speed adjustment

int MAXENEMY = 10;    //max number of enemies

double LEVEL = .05;   //set speed of enemies
bool beamFlag = 0;    //for drawing beam
double MARG = 0.5;    //margin from center for hit detection
int MENU=0;           //for portion of screen selection
int sflag=1;

int xres=800;
int yres=512;

//create objects
Enemy* baddy = new Enemy[MAXENEMY];
Player* hero = new Player();



////////////////////texture loading////////////////
GLuint badTexture;
GLuint hboxTexture;
GLuint heroTexture;
GLuint backTexture;
GLuint beamTexture;
GLuint startTexture;
GLuint gridTexture;
GLuint d1Tex;
GLuint d2Tex;
GLuint d3Tex;
GLuint loseTex;
GLuint titleTex;
GLuint gridTex;
GLuint s10Tex;
GLuint s0Tex;
GLuint s1Tex;
GLuint s2Tex;
GLuint s3Tex;
GLuint s4Tex;
GLuint s5Tex;
GLuint s6Tex;
GLuint s7Tex;
GLuint s8Tex;
GLuint s9Tex;
GLuint lifeTex;


//update speed of enemies based on score
void levelUpdate()
{
  if(hero->score%30==0)
  {
    LEVEL += .005;
  }
}

//move enemies down based on time and level
void moveEn()
{
  double currTime = glfwGetTime();

  for(int i=0;i<MAXENEMY;i++) {
    baddy[i].yPos  += -LEVEL;
    //cout << -LEVEL << endl;

    if(baddy[i].yPos <= -2) 
    {
      baddy[i].reset();
      hero->life -= 1;
    }
  }
 
}


//hit detection
void shoot(int i)
{
  double left = hero->getPos() - MARG;
  double right = hero->getPos()+ MARG;
  double height = baddy[i].getyPos();
  
  if(left < baddy[i].xPos && baddy[i].xPos < right && height < 5.4)
  {
    baddy[i].state = 1;
    baddy[i].deathPos = baddy[i].getyPos();
    hero->kill();
    levelUpdate();
    return;
  }
}
 
//this handles keys that are held down
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
	  
	  //following two are for debug purposes
	  if(glfwGetKey('N') == GLFW_PRESS) //right movement
    {
      //if(baddy[0].xPos >= -4) 
      {
        baddy[0].xPos+=(movTick*2);
      }
	  }
	  
	  if(glfwGetKey('M') == GLFW_PRESS) //right movement
    {
      //if(baddy[0].xPos <= 4) 
      {
        baddy[0].xPos-=(movTick);
      }
	  }
	    
}
  
//update position and then draw it
void updateEnemy() 
{
  moveEn();
  
  for(int i = 0;i<MAXENEMY;i++) 
  {
    drawEn(i);    
  }
}


void shutDown(int return_code)
{
  glfwTerminate();
  exit(return_code);
}


//draw life meter
void drawLife()
{ //draw Lives text
  glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
  glPushMatrix();

  glTranslatef(3.3,-4.9,0); 
  glRotatef(90,0,0,1);
  glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);

  glBindTexture(GL_TEXTURE_2D, lifeTex);	
  
  double e=.15,f=9,d=1;;
  glBegin(GL_QUADS);
  {
    glColor3f(1, 1, 1); //
    //glTexCoord3f(0.0f, 0.0f,-f);glVertex3f(-e, e, -f);
    //glTexCoord3f(0.0f, 1.0f,-f);glVertex3f(e, e, -f);
    //glTexCoord3f(1.0f, 1.0f,-f);glVertex3f(e, -e, -f);
    //glTexCoord3f(1.0f, 0.0f,-f);glVertex3f(-e, -e, -f);
    glTexCoord3f(1.0f, 0.0f,-f);glVertex3f(-e, d, -f);
    glTexCoord3f(1.0f, 1.0f,-f);glVertex3f(e, d, -f);
    glTexCoord3f(0.0f, 1.0f,-f);glVertex3f(e, -d, -f);
    glTexCoord3f(0.0f, 0.0f,-f);glVertex3f(-e, -d, -f);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_ALPHA_TEST);
  glPopMatrix();
  
  
  //////////////draw amount of life left///////////////
  glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
  glPushMatrix();

  glTranslatef(2,-4.9,0); 
  glRotatef(90,0,0,1);
  glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);

  switch (hero->life)
  {
    case 10:
      glBindTexture(GL_TEXTURE_2D, s10Tex);	
      break;
    case 9:
      glBindTexture(GL_TEXTURE_2D, s9Tex);	
      break;
    case 8:
      glBindTexture(GL_TEXTURE_2D, s8Tex);
      break;
    case 7:
      glBindTexture(GL_TEXTURE_2D, s7Tex);
      break;
    case 6:
      glBindTexture(GL_TEXTURE_2D, s6Tex);
      break;
    case 5:
      glBindTexture(GL_TEXTURE_2D, s5Tex);
      break;
    case 4:
      glBindTexture(GL_TEXTURE_2D, s4Tex);
      break;
    case 3:
      glBindTexture(GL_TEXTURE_2D, s3Tex);
      brea:;
    case 2:
      glBindTexture(GL_TEXTURE_2D, s2Tex);
      break;
    case 1:
      glBindTexture(GL_TEXTURE_2D, s1Tex);
      break;
    default:
      glBindTexture(GL_TEXTURE_2D, s0Tex);
      break;
   }  
	
  
  double g=.15,h=.20;;
  glBegin(GL_QUADS);
  {
    glColor3f(1, 1, 1); //
    glTexCoord3f(1.0f, 0.0f,-f);glVertex3f(-g, h, -f);
    glTexCoord3f(1.0f, 1.0f,-f);glVertex3f(g, h, -f);
    glTexCoord3f(0.0f, 1.0f,-f);glVertex3f(g, -h, -f);
    glTexCoord3f(0.0f, 0.0f,-f);glVertex3f(-g, -h, -f);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_ALPHA_TEST);
  glPopMatrix();

}




void render()
{
  // clear the buffer
  glViewport(0, 0, 512,600);
  
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glOrtho(0, 0, 512,600,-1,1);
    
  if(MENU==0)
  {
    drawBeginning();
    int temp=system("clear");
  }
  else if(MENU==1)
  {
    drawBackground();
    drawLife();
    drawPlayer();
    updateEnemy(); //draw/move functions for enemies
    if(beamFlag==1)
    {
      drawBeam();
      usleep(5000); //just long enough to flash on screen
      beamFlag=0;
    }
    if(hero->life <= 0)
      MENU=2;
      
  }
  else if(MENU==2)
  {
    drawGameOver();
    if(sflag)
    {
      sflag=0;
      int temp=system("clear");
      cout << "You scored " << hero->score << endl;
    }
  } 
  

  glfwSwapBuffers();
  
}


//draw grid on first menu screen
void drawGrid()
{
  glPushMatrix();
  glTranslatef(0,0,0);
  glBindTexture(GL_TEXTURE_2D, gridTex);

  double d = 5;
  double h=2.5,w=2.99;

  glBegin(GL_QUADS); 
  {
    glColor3f(.7,.7,.7);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(h, -w, -d);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(h, w, -d);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-h, w, -d);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-h,-w, -d);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();

}

//title on first menu screen
void drawTitle()
{
  glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
  glPushMatrix();
  //move image down to where player actually is
  glTranslatef(0,1,0); 
  glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	//rotate on z axis
  glRotatef(90, 0, 0, 1);
  
  glBindTexture(GL_TEXTURE_2D, titleTex);	
  
  double e=.5,f=5;;
  glBegin(GL_QUADS);
  {
    glColor3f(1, 1, 1); //
    glTexCoord3f(0.0f, 0.0f,-f);glVertex3f(-e, 1.5, -f);
    glTexCoord3f(0.0f, 1.0f,-f);glVertex3f(e, 1.5, -f);
    glTexCoord3f(1.0f, 1.0f,-f);glVertex3f(e, -1.5, -f);
    glTexCoord3f(1.0f, 0.0f,-f);glVertex3f(-e, -1.5, -f);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_ALPHA_TEST);
  glPopMatrix();
}


//draw start instructions on first menu
void drawStart()
{
    glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
  glPushMatrix();

  glTranslatef(0,-4,0); 
  glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);

  glRotatef(90, 0, 0, 1);
  glBindTexture(GL_TEXTURE_2D, startTexture);	
  
  double e=.5,f=9;;
  glBegin(GL_QUADS);
  {
    glColor3f(1, 1, 1); //
    glTexCoord3f(0.0f, 0.0f,-f);glVertex3f(-e, 1.5, -f);
    glTexCoord3f(0.0f, 1.0f,-f);glVertex3f(e, 1.5, -f);
    glTexCoord3f(1.0f, 1.0f,-f);glVertex3f(e, -1.5, -f);
    glTexCoord3f(1.0f, 0.0f,-f);glVertex3f(-e, -1.5, -f);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_ALPHA_TEST);
  glPopMatrix();
}

//handler for intro screen
void drawBeginning()
{
  drawGrid();
  drawTitle();
  drawStart();
}

//game over screen
void drawDeath()
{
  glPushMatrix();
  glTranslatef(0,0,0);
  glBindTexture(GL_TEXTURE_2D, loseTex);

  double d = 5;
  double h=2.5,w=2.99;

  glBegin(GL_QUADS); 
  {
    glColor3f(.7,.7,.7);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(h, -w, -d);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(h, w, -d);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-h, w, -d);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-h,-w, -d);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();

}

//handler for game over screen for when i was going to add more
//displays like score/highscores
void drawGameOver()
{
  drawDeath();
}

//draw enemy, hanndles ALL drawn enemies objects include death animation
void drawEn(int enmy = 0)
{ 
  if(baddy[enmy].state==0) //if it's alive
  {
    glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
    glPushMatrix();
    //baddy[enmy].xPos=1.5;baddy[enmy].yPos=0; //STOP 
    glTranslatef(baddy[enmy].xPos,baddy[enmy].yPos,0);
    glRotatef(90+180,0,0,1);
    glEnable(GL_ALPHA_TEST);
  	glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, badTexture);

    double e=.75,f=9,d= 15;

    glBegin (GL_QUADS);
    {
      glTexCoord3f(0.0f, 0.0f,-f);glVertex3f(-e, e, -f);
      glTexCoord3f(0.0f, 1.0f,-f);glVertex3f(e, e, -f);
      glTexCoord3f(1.0f, 1.0f,-f);glVertex3f(e, -e, -f);
      glTexCoord3f(1.0f, 0.0f,-f);glVertex3f(-e, -e, -f);
    }
    
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  	glDisable(GL_ALPHA_TEST);
    glPopMatrix();
  }
  else //if it's dead, draw death sequence
  {
    glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
    glPushMatrix();
    glTranslatef(baddy[enmy].xPos,baddy[enmy].deathPos,0);
    glRotatef(90+180,0,0,1);
    glEnable(GL_ALPHA_TEST);
  	glAlphaFunc(GL_GREATER, 0.0f);
  	//death sequence
  	if(baddy[enmy].state==1) { glBindTexture(GL_TEXTURE_2D, d1Tex); baddy[enmy].state++; }
  	else if(baddy[enmy].state==2) { glBindTexture(GL_TEXTURE_2D, d2Tex); baddy[enmy].state++; }
    else { glBindTexture(GL_TEXTURE_2D, d3Tex); baddy[enmy].state=0; baddy[enmy].reset(); }
    
    double e=.75,f=9,d= 15;

    glBegin (GL_QUADS);
    {
      glTexCoord3f(0.0f, 0.0f,-f);glVertex3f(-e, e, -f);
      glTexCoord3f(0.0f, 1.0f,-f);glVertex3f(e, e, -f);
      glTexCoord3f(1.0f, 1.0f,-f);glVertex3f(e, -e, -f);
      glTexCoord3f(1.0f, 0.0f,-f);glVertex3f(-e, -e, -f);
    }
    
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  	glDisable(GL_ALPHA_TEST);
    glPopMatrix();
  }
      
}


//beam looks totally different than drawn image
//but I think it looks cooler that way
void drawBeam()
{
 
  glPushMatrix();
  //draw beam over hero
  glTranslatef(hero->getPos(),-4,0);
  
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.0f);
  glBindTexture(GL_TEXTURE_2D,beamTexture);
  
  double f=9,h=10,w=.25;
  
  //drawn incorrectly from image, but I actually 
  //like the way it looks better, so i'm keeping it
  glBegin(GL_QUADS);
  {
    glTexCoord3f(0.0f, 0.0f,-f);glVertex3f(-w, h, -f);
    glTexCoord3f(0.0f, 1.0f,-f);glVertex3f(w, h, -f);
    glTexCoord3f(1.0f, 1.0f,-f);glVertex3f(w, 0, -f);
    glTexCoord3f(1.0f, 0.0f,-f);glVertex3f(-w, 0, -f);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_ALPHA_TEST);
  glPopMatrix();
  
}

//handls drawing hero object
void drawPlayer() {
  
  //spinning it just for fun
  double rot = hero->getPos() * -90;

  glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
  glPushMatrix();
  //move image down to where player actually is
  glTranslatef(hero->getPos(),-4.5,0); 
  glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	//rotate on z axis
  glRotatef(rot, 0, 0, 1);
  glBindTexture(GL_TEXTURE_2D, heroTexture);	
  
  double e=.4,f=9;;
  glBegin(GL_QUADS);
  {
    glColor3f(1, 1, 1); //
    glTexCoord3f(0.0f, 0.0f,-f);glVertex3f(-e, e, -f);
    glTexCoord3f(0.0f, 1.0f,-f);glVertex3f(e, e, -f);
    glTexCoord3f(1.0f, 1.0f,-f);glVertex3f(e, -e, -f);
    glTexCoord3f(1.0f, 0.0f,-f);glVertex3f(-e, -e, -f);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_ALPHA_TEST);
  glPopMatrix();

}

//draws the, uh, background
void drawBackground()
{
  glPushMatrix();
  glTranslatef(0,0,0);
  glBindTexture(GL_TEXTURE_2D, backTexture);

  double d = 5;
  double h=2.5,w=2.99;

  glBegin(GL_QUADS); 
  {
    glColor3f(.7,.7,.7);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(h, -w, -d);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(h, w, -d);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-h, w, -d);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-h,-w, -d);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();

}



//handles single key presses, only does one action per press
void GLFWCALL keyCallBack(int key, int action) 
{
  
  if(key == GLFW_KEY_ESC && action == GLFW_PRESS)
    shutDown(0);

  
  {
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) 
    {
      for(int i=0;i<MAXENEMY;i++)
        shoot(i); 
      beamFlag=1;  
    }
    if(key == GLFW_KEY_ENTER && action == GLFW_PRESS) 
    {
      if(MENU==0)
        MENU=1;
      else if(MENU==1 && hero->life <= 0)
        MENU=2;  
    }  
        
  }
  if(key == 'P' && action == GLFW_PRESS)
  {
    LEVEL += .05;printf("uppered level %f \n",LEVEL);
  }
  if(key == 'O' && action == GLFW_PRESS)
  {
    LEVEL -= .05; printf("lowered level %f \n",LEVEL);
  }
  if(key == 'U' && action == GLFW_PRESS)
  {
    hero->life=100;
  }
  
}


//intialize eveything
void init_opengl(void)
{
	
	glShadeModel(GL_SMOOTH);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);
	//
	glEnable(GL_TEXTURE_2D);
	backTexture = tex_readgl_bmp((char *)"backdrop.bmp",1);
	badTexture = tex_readgl_bmp((char *)"baddy.bmp",1);
	heroTexture = tex_readgl_bmp((char *)"hero.bmp",1);
	hboxTexture = tex_readgl_bmp((char *)"bBox.bmp",1);
	beamTexture = tex_readgl_bmp((char *)"beam.bmp",1);
	startTexture = tex_readgl_bmp((char *)"start.bmp",1);
	gridTexture = tex_readgl_bmp((char *)"background.bmp",1);
	d1Tex = tex_readgl_bmp((char *)"d1.bmp",1);
	d2Tex = tex_readgl_bmp((char *)"d2.bmp",1);
	d3Tex = tex_readgl_bmp((char *)"d3.bmp",1);
	loseTex = tex_readgl_bmp((char *)"gOver.bmp",1);
	titleTex = tex_readgl_bmp((char *)"title.bmp",1);
	gridTex = tex_readgl_bmp((char *)"GRID.bmp",1);
	s1Tex = tex_readgl_bmp((char *)"s1.bmp",1);
	s2Tex = tex_readgl_bmp((char *)"s2.bmp",1);
	s3Tex = tex_readgl_bmp((char *)"s3.bmp",1);
	s4Tex = tex_readgl_bmp((char *)"s4.bmp",1);
	s5Tex = tex_readgl_bmp((char *)"s5.bmp",1);
	s6Tex = tex_readgl_bmp((char *)"s6.bmp",1);
	s7Tex = tex_readgl_bmp((char *)"s7.bmp",1);
	s8Tex = tex_readgl_bmp((char *)"s8.bmp",1);
	s9Tex = tex_readgl_bmp((char *)"s9.bmp",1);
	s0Tex = tex_readgl_bmp((char *)"s0.bmp",1);	
	s10Tex = tex_readgl_bmp((char *)"s10.bmp",1);
	lifeTex = tex_readgl_bmp((char *)"life.bmp",1);

		
	
	glBindTexture(GL_TEXTURE_2D, 0);

}

//init windows
void init(int window_height, int window_width)
{
    init_opengl();
  //big block of glfw stuff
  if (glfwInit() != GL_TRUE)
    shutDown(1);

  if (glfwOpenWindow(window_width, window_height, 5, 6, 5, 0, 0, 0, GLFW_WINDOW) != GL_TRUE)
    shutDown(1);

  glfwSetWindowPos(500,0);
  
  glShadeModel(GL_SMOOTH);
	//texture maps must be enabled to draw fonts
	glEnable(GL_TEXTURE_2D);
//	initialize_fonts();
    


  glfwSetWindowTitle("FlatLander: Prevent the Uprising");
  glfwSetKeyCallback(keyCallBack);

  // set the projection matrix to a normal frustum with a max depth of 50

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double aspect_ratio = ((double)window_height) / window_width;
  glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
  glMatrixMode(GL_MODELVIEW);

  //glEnable(GL_BLEND);

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


