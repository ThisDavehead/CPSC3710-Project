#ifndef CITY_H
#define CITY_H

#include "Block.h"
#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <vector>
#include <string.h>  // For spring operations.
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

class City
{
  public:
    void draw();
    City();
    Block blocks[4000];
};

#endif /*BUILDING_H_*/
