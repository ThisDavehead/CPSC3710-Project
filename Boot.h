#ifndef BOOT_H
#define BOOT_H

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <string.h>  // For string operations.
#include <cmath>
#include <vector>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include "Robot.h"
#include "Block.h"
#include "Building.h"
#include "Street.h"
#include "City.h"

class Boot
{
  public:
    static int Window_ID;
    static int Window_Width;
    static int Window_Height;
    static int rightDown;
    static int leftDown;
    static int zcentre;
    static int viewKey;
    static int paused;
    static Robot robot;
    static Street network;
    static City city;
    static float eyePoint[3];
    static void rotateCameras();
    static void CallBackRenderScene(void);
    static void pauseGame();
    static void myCBKey(unsigned char key, int x, int y);
    static void mySpecialKey(int key, int x, int y);
    static void CallBackResizeScene(int Width, int Height);
    static void mouseFunctionality(int buttonNum, int btnState, int x, int y);
    static void MyInit(int Width, int Height);
    static void specKeyUp(int key, int x, int y);
    static void processHits (GLint hits, GLuint buffer[]);

};

#endif /*BOOT_H_*/
