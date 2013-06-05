/* CS 335 Final
 * Eduardo Figueroa
 * Team: Where'd Everyone Go?
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glfw.h>
#include <time.h>
#include <cstdlib>
#include "functions.h"
#include "enemy.cpp"
#include "player.h"

GLuint loadBMP(const char *imagepath);

float moveX = 0;

float movTick = .1;
const int window_width = 512,
          window_height = 600;
const int MAXENEMY = 5;
double oldTime;

int main()
{

  srand(time(NULL));

  oldTime = glfwGetTime();
  
  init(window_height, window_width);
  
  while(1)
  {
    keyHandler();
    glfwPollEvents();
    render();
    glfwSwapBuffers();
  }

}

