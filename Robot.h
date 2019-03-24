#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>  // Useful for the following includes.
#include <cmath>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

class Robot
{
   // Everything has been left public for now to save time
  public:
   int head;  // direction the robot's head is facing: 0 normal 1 left 2 right
   int point[3]; // center point
   float centreToFeet;
   Robot();
   void createCircle(float radius, int x, int y);
   void createTriangle(float width, float height);
   void createRectangle(float width, float height);
   void createBox(float width, float height, float depth);
   void draw(float x, float y, float z);
};

#endif /*ROBOT_H_*/
