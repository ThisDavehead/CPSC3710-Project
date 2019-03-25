#ifndef STREET_H
#define STREET_H

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <string.h>  // For spring operations.
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <cmath>

class Street{
  public:
   void draw();
   bool checkIfIntersection(const float xpos, float pos);
   const float getBlockLength();
   const float getWidth();
   const int getSize();
  private:
   static const float width = 10.0;
   static const int citySize = 20;
   static const float blockLength = 50.0;
};

#endif
