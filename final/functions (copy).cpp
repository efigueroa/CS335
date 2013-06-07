/* Various Functions called from main
 */

#include <GL/glfw.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "enemy.cpp"
#include "functions.h"
#include "player.cpp"
#include "math.h"
#include "defs.h"
#include <time.h>
#include <string.h>
#include "fonts.h"
#include "bmp.c"


using namespace std;

extern double moveX;                   //player movement
extern double movTick;
extern GLuint backTexture;
const int MAXENEMY = 1;
extern double oldTime;
double LEVEL = .05;
bool beamFlag = 0;
int border[2]={200,100};
double hOffset=.6;
double MARGIN=.5;
bool HITBOX = 0;

int xres=800;
int yres=600;

Enemy* baddy = new Enemy[MAXENEMY];
Player* hero = new Player();

int lbutton=0;
int rbutton=0;
//
GLuint badTexture;
GLuint hboxTexture;
GLuint heroTexture;
GLuint backTexture;
GLuint beamTexture;
//extern GLuint loadBMP(const char *imagepath);
//extern GLuint tex_readgl_bmp(char *fileName, int alpha_channel);

//
#define MAXBUTTONS 4
typedef struct t_button {
	Rect r;
	char text[32];
	int over;
	int down;
	int click;
	double color[3];
	double dcolor[3];
	unsigned int text_color;
} Button;
Button button[MAXBUTTONS];
int nbuttons=0;


void drawEn(int enmy = 0)
{ 
  glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
  glPushMatrix();
  //baddy[enmy].xPos=1.5;baddy[enmy].yPos=0; //STOP 
  glTranslatef(baddy[enmy].xPos,baddy[enmy].yPos,0);
  glRotatef(90+180,0,0,1);
  glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
  glBindTexture(GL_TEXTURE_2D, badTexture);

  double e=1,f=9,d= 15;

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

void moveEn()
{
  double currTime = glfwGetTime();

  for(int i=0;i<MAXENEMY;i++) {
    baddy[i].yPos  += -LEVEL;
    //cout << -LEVEL << endl;

    if(baddy[i].yPos <= -2.9) 
    {
      baddy[i].reset();
    }
  }
 
}

void drawBeam()
{
 
  glPushMatrix();
  glTranslatef(hero->getPos(),-4,0);
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.0f);
  glBindTexture(GL_TEXTURE_2D,beamTexture);
  
  double f=10,h=8.5,w=hero->right,wl=hero->left;
  
  glBegin(GL_QUADS);
  {
    glColor3f(1, 1,1);
    glTexCoord3f(0.0f, 0.0f,-f);glVertex3f(.3, h, -f);
    glTexCoord3f(0.0f, 1.0f,-f);glVertex3f(-.3, h, -f);
    glTexCoord3f(1.0f, 1.0f,-f);glVertex3f(-.3, -1, -f);
    glTexCoord3f(1.0f, 0.0f,-f);glVertex3f(.3, -1, -f);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_ALPHA_TEST);
  glPopMatrix();
  
}

void drawHit(int i=0)
{
 
  glPushMatrix();
  glTranslatef(baddy[i].getxPos(),baddy[i].getyPos(),0); 
  
    double e=1,f=15,d= 25;

  glBegin (GL_QUADS);
  {
    glVertex3f(-e, e, -f);
    glVertex3f(e, e, -f);
    glVertex3f(e, -e, -f);
    glVertex3f(-e, -e, -f);
  }
  glEnd();
  glPopMatrix();
  
}

void shoot(int i)
{
   //baddy[i].reset();
    //if(baddy[i].getyPos() < 7) 
    {
      if(hero->left > baddy[i].getxPos())
      {
        if(baddy[i].getxPos() > hero->right)
        {
          cout << "Hit:\n";
          cout<<"left: "<<hero->left<<" baddy: "<<baddy[i].getxPos()<<" right: "<< hero->right<< endl;
          cout << baddy[i].getyPos() << endl;
          baddy[i].reset();
        }
      }
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
	  
	  if(glfwGetKey('N') == GLFW_PRESS) //right movement
    {
      //printf("%f\n",moveX);
      //if(hero->getPos() < 0) 
      {  
      }
      //else
      {
        baddy[0].xPos+=(movTick);
      }
	  }
	  
	  if(glfwGetKey('M') == GLFW_PRESS) //right movement
    {
      //printf("%f\n",moveX);
     // if(hero->getPos() >= -6) 
      {  
      }
     // else
      {
        baddy[0].xPos-=(movTick);
      }
	  }
	    
}
  


void updateEnemy() 
{

  moveEn();
  //drawEn();
  for(int i = 0;i<MAXENEMY;i++) 
  {
    //drawHit(i);
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
  
  double rot = hero->getPos() * -90;

  glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
  glPushMatrix();
  glTranslatef(hero->getPos(),-4.5,0); 
  glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
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


void drawWall() {

  glPushMatrix();
  glTranslatef(0,-3,0);
  double h=5,w=.3,d=10;
  glBegin(GL_QUADS); 
  {
    glColor3f(0.15, 0.84,0 ); 
    glVertex3f(-h, w, -d);
    glVertex3f(h, w, -d);
    glVertex3f(h, -w, -d);
    glVertex3f(-h,-w, -d);
  }
  glEnd();
  glPopMatrix();

}

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


void screenInfo()
{
  int i=1;
  Rect r;
  r.left=10;
  r.bot=10;
  r.center=0;

}

void render()
{
  // clear the buffer
  glViewport(0, 0, 512,600);
  
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glOrtho(0, 0, 512,600,-1,1);
  
  screenInfo();
  
  drawBackground();
 
  //drawWall();
  updateEnemy();
  if(beamFlag==1)
  {
    drawBeam();
    usleep(5000);
    beamFlag=0;
  }
  drawPlayer();
  cout << "Hero is at x: "<< hero->getPos() << endl;
  cout << "Enemy is at x: "<< baddy[0].getxPos() << endl<<endl;

  float totrain = 12.3455;

	Rect r;
	r.left   = 2;
	r.bot    = 3;
	r.center = 0;
 // ggprint12(&r, 16, 0x00aaaa00, "total drops: %f",totrain);


  //cout << hero->xPos << endl;
  glfwSwapBuffers();
  
}

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
        
  }
  if(key == 'P' && action == GLFW_PRESS)
  {
    LEVEL += .005;printf("uppered level\n");
  }
  if(key == 'O' && action == GLFW_PRESS)
  {
    LEVEL -= .005; printf("lowered level\n");
  }
  if(key == 'U' && action == GLFW_PRESS)
  {
    if(HITBOX)
      HITBOX=0;
    else
      HITBOX=1;
  }
  
}


void init_opengl(void)
{
	
	glShadeModel(GL_SMOOTH);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);
	//
	glEnable(GL_TEXTURE_2D);
	backTexture = tex_readgl_bmp("backdrop.bmp",1);
	badTexture = tex_readgl_bmp("baddy.bmp",1);
	heroTexture = tex_readgl_bmp("hero.bmp",1);
	hboxTexture = tex_readgl_bmp("bBox.bmp",1);
	beamTexture = tex_readgl_bmp("beam.bmp",1);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	//printf("tex: %i %i\n",badTexture,backTexture);
}


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


void check_mouse(void)
{
	static int sx=0,sy=0;	
	int x,y;
	int i;
	//int cent[2];
	lbutton=0;
	rbutton=0;
	if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//left mouse button is pressed.
		lbutton=1;
	}
	if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		//right mouse button is pressed.
		rbutton=1;
	}
	glfwGetMousePos(&x, &y);
	//reverse the y position
	y = yres - y;
	if (x == sx && y == sy) return;
	sx=x;
	sy=y;	
	//
	//is the mouse over any buttons?
	//
	for (i=0; i<nbuttons; i++) {
		button[i].over=0;
		button[i].down=0;
	}
	for (i=0; i<nbuttons; i++) {
		if (x >= button[i].r.left &&
			x <= button[i].r.right &&
			y >= button[i].r.bot &&
			y <= button[i].r.top) {
			button[i].over=1;
			break;
		}
	}
}

void init_buttons(void)
{
  //initialize buttons...
	nbuttons=0;
	//size and position
	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 20;
	button[nbuttons].r.bot = 480;
	button[nbuttons].r.right = button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot + button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left + button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot + button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Creep");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.4f;
	button[nbuttons].color[1] = 0.4f;
	button[nbuttons].color[2] = 0.7f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x00ffffff;
	nbuttons++;
	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 20;
	button[nbuttons].r.bot = 400;
	button[nbuttons].r.right = button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot + button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left + button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot + button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "8 Creeps");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.4f;
	button[nbuttons].color[1] = 0.4f;
	button[nbuttons].color[2] = 0.7f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x00ffffff;
	nbuttons++;
	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 20;
	button[nbuttons].r.bot = 320;
	button[nbuttons].r.right = button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot + button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left + button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot + button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Reset");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.4f;
	button[nbuttons].color[1] = 0.4f;
	button[nbuttons].color[2] = 0.7f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x00ffffff;
	nbuttons++;
	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 20;
	button[nbuttons].r.bot = 160;
	button[nbuttons].r.right = button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot + button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left + button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot + button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Quit");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.3f;
	button[nbuttons].color[1] = 0.3f;
	button[nbuttons].color[2] = 0.6f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x00ffffff;
	nbuttons++;
}

