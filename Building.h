#ifndef BUILDING_H
#define BUILDING_H

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <string.h>  // For spring operations.
#include <ctime>
#include <cmath>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

class Building
{
  public:
   float xBase;
   float zBase;
   float width;
   float height;
   float depth;
   int health;
   int type;
   int shape;
   Building(float x=0, float z=0);
   void attack();
   void createBox(float width, float height, float depth);
   void createSilo(float radius, float height, int x, int y);
   void createPyramid(float width, float height, float depth);
   
   void draw();
};

#endif /*BUILDING_H_*/
