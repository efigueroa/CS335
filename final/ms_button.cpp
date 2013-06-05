//cs335 Spring 2013
//program: ms_button.c
//author:  gordon griesel
//purpose: midterm sampler
//
//This program contains functions you can use
//in your midterm and final project.
//
//Define a button
//Press and release the button
//
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <GL/glfw.h>
#include "fonts.h"
#include "log.h"
//macros
#define rnd() (double)rand()/(double)RAND_MAX
//prototypes
void init(void);
int init_glfw(void);
void init_opengl(void);
void physics(void);
void render(void);
void GLFWCALL mouse_click(int button, int action);
void checkkey(int k1, int k2);
void check_mouse(void);
int xres=640;
int yres=480;
//
int lbutton=0;
int rbutton=0;
//
typedef struct t_button {
	Rect r;
	char text[32];
	int over;
	int down;
	int click;
	float color[3];
	float dcolor[3];
	unsigned int text_color;
} Button;
Button button[1];
int nbuttons=0;
int play = 0;
int quit = 0;

int main(void)
{
	if (init_glfw()) {
		exit(EXIT_FAILURE);
	}
	extern void open_log_file(void);
//	open_log_file();
	init_opengl();
	init();
	initialize_fonts();
	srand((unsigned int)time(NULL));
	while(1) {
		check_mouse();
		physics();
		render();
		glfwSwapBuffers();
		if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) break;
		if (!glfwGetWindowParam(GLFW_OPENED)) break;
	}
	glfwTerminate();
	cleanup_fonts();
//	close_log_file();
	exit(EXIT_SUCCESS);
}

int init_glfw(void)
{
	if (!glfwInit()){
		printf("Failed to initialize GLFW\n");
		return 1;
	}
	//create a window
	if (!glfwOpenWindow(xres, yres, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
		glfwTerminate();
		return 1;
	}
	glfwSetWindowTitle("menu function");
	glfwSetWindowPos(0, 0);
	//make sure we see the escape key pressed
	glfwEnable(GLFW_STICKY_KEYS);
	glfwSetMouseButtonCallback(mouse_click);
	glfwSetKeyCallback((GLFWkeyfun)(checkkey));
	glfwEnable( GLFW_MOUSE_CURSOR );
	//enable vertical sync (on cards that support it)
	glfwSwapInterval(1);
	return 0;
}

void init_opengl(void)
{
	//OpenGL initialization
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_COLOR_MATERIAL);
	//
	//choose one of these
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	//
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void initButtons()
{
	//initialize buttons...
	nbuttons=0;
  play = 0;
  quit = 0;
	//size and position
  button[play].r.width = 200;
  button[play].r.width = 200;
	button[play].r.height = 100;
	button[play].r.left = xres/2 - button[play].r.width/2;
	button[play].r.bot = yres/2 - 50;
	button[play].r.right = button[play].r.left + button[play].r.width;
	button[play].r.top = button[play].r.bot + button[play].r.height;
	button[play].r.centerx = (button[play].r.left + button[play].r.right) / 2;
	button[play].r.centery = (button[play].r.bot + button[play].r.top) / 2;
	strcpy(button[play].text, "Play Game");
	button[play].down = 0;
	button[play].click = 0;
	button[play].color[0] = 0.4f;
	button[play].color[1] = 0.4f;
	button[play].color[2] = 0.7f;
	button[play].dcolor[0] = button[play].color[0] * 0.5f;
	button[play].dcolor[1] = button[play].color[1] * 0.5f;
	button[play].dcolor[2] = button[play].color[2] * 0.5f;
	button[play].text_color = 0x00ffffff;
	play++;
  button[nbuttons].r.width = 200;
	button[nbuttons].r.height = 200;
	button[nbuttons].r.left = xres/2 - button[nbuttons].r.width/2;
	button[nbuttons].r.bot = yres/2 - 50;
	button[nbuttons].r.right = button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot + button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left + button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot + button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Does it work?");
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
}

void checkkey(int k1, int k2)
{
	static int shift=0;
	if (shift) {}
	if (k2 == GLFW_PRESS) {
		//some key is being pressed now
		if (k1 == GLFW_KEY_LSHIFT || k1 == GLFW_KEY_RSHIFT) {
			//it is a shift key
			shift=1;
			return;
		}
	}
	if (k2 == GLFW_RELEASE) {
		if (k1 == GLFW_KEY_LSHIFT || k1 == GLFW_KEY_RSHIFT) {
			//the shift key was released
			shift=0;
		}
		//don't process any other keys on a release
		return;
	}
	if (k1 == 'C') {
		return;
	}
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
	if (x == sx && y == sy) {
		//mouse did not change position
		//since we were here last.
		return;
	}
	//save the new position
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

void GLFWCALL mouse_click(int ibutton, int action)
{
	int i;
	if (ibutton) {}
	if (action == GLFW_PRESS) {
		//printf("mouse_click()...\n");
		//glfwGetMousePos(&x, &y);
		//y = yres - y;
		for (i=0; i<nbuttons; i++) {
			if (button[i].over) {
				button[i].down = 1;
				button[i].click = 1;
			}
		}
	}
	if (action == GLFW_RELEASE) {
		//glfwGetMousePos(&x, &y);
		//y = yres - y;
		for (i=0; i<nbuttons; i++) {
			button[i].down = 0;
			button[i].click = 0;
		}
	}
}

void physics(void)
{
	//int i,j;
}

void render(void)
{
	int i;
	//int j;
	Rect r;
	//--------------------------------------------------------
	//set the viewing area on screen
	glViewport(0, 0, xres, yres);
	//clear color buffer
	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//init matrices
	glMatrixMode (GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//this sets to 2D mode (no perspective)
	glOrtho(0, xres, 0, yres, -1, 1);
	//glColor3f(0.8f, 0.6f, 0.2f);
	//
	//draw all buttons
	for (i=0; i<nbuttons; i++) {
		if (button[i].over) {
			glColor3f(1.0f, 0.0f, 0.0f);
			//draw a highlight around button
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
				glVertex2i(button[i].r.left-2,  button[i].r.bot-2);
				glVertex2i(button[i].r.left-2,  button[i].r.top+2);
				glVertex2i(button[i].r.right+2, button[i].r.top+2);
				glVertex2i(button[i].r.right+2, button[i].r.bot-2);
				glVertex2i(button[i].r.left-2,  button[i].r.bot-2);
			glEnd();
			glLineWidth(1);
		}
		if (button[i].down) {
			glColor3fv(button[i].dcolor);
		} else {
			glColor3fv(button[i].color);
		}
		glBegin(GL_QUADS);
			glVertex2i(button[i].r.left,  button[i].r.bot);
			glVertex2i(button[i].r.left,  button[i].r.top);
			glVertex2i(button[i].r.right, button[i].r.top);
			glVertex2i(button[i].r.right, button[i].r.bot);
		glEnd();
		r.left = button[i].r.centerx;
		r.bot  = button[i].r.centery-8;
		r.center = 1;
		if (button[i].down) {
			ggprint16(&r, 0, button[i].text_color, "Pressed!");
		} else {
			ggprint16(&r, 0, button[i].text_color, button[i].text);
		}
	}
}


