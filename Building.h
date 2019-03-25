#ifndef BUILDING_H
#define BUILDING_H

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <string.h>  // For spring operations.
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

class Building
{
  public:
   int health;
   void attack();
    void draw();
    void createBox(float width, float height, float depth);
};

#endif /*BUILDING_H_*/
