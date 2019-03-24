#ifndef BOOT_H
#define BOOT_H

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <string.h>  // For spring operations.
#include <cmath>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include "Robot.h"
#include "Block.h"
#include "Building.h"
#include "Street.h"

class Boot
{
  public:
    static int Window_ID;
    static int Window_Width;
    static int Window_Height;
    static int rightDown;
    static int leftDown;
    static int zcentre;
    static Robot robot;
    static float eyePoint[3];
    static void CallBackRenderScene(void);
    static void myCBKey(unsigned char key, int x, int y);
    static void mySpecialKey(int key, int x, int y);
    static void CallBackResizeScene(int Width, int Height);
    static void mouseFunctionality(int buttonNum, int btnState, int x, int y);
    static void MyInit(int Width, int Height);
    static void specKeyUp(int key, int x, int y);
};

#endif /*BOOT_H_*/
