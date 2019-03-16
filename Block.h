#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <string.h>  // For spring operations.
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

class Block
{
  public:
    void draw();
    void createBox(float width, float height, float depth);
};

#endif /*BUILDING_H_*/