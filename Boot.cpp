/**
    CPSC 3710 - Project
    Boot.cpp
    Purpose: Boots game and runs the game loop.

    @author Matthew Davison
    @version 1.1 4/10/16
*/
#define PROGRAM_TITLE "Project"

#include "Boot.h"
#include "Block.h"
#include "Building.h"
#include <cmath>

  // Some global variables.
  // Window IDs, window width and height
  int Boot::Window_ID = 0;
  int Boot::Window_Width = 1000;
  int Boot::Window_Height = 600;
  int Boot::rightDown = 0;
  int Boot::leftDown = 0;
  int Boot::zcentre = 5;
  float Boot::eyePoint[3] = {4, 4, 4};

  /*TODO Extract this into Robot class*/
  int robotHead = 0; // 0 normal 1 left 2 right
  int robotPoint[3] = {0, 0, 0}; // center point
  float robotCentreToFeet = -3.15f;
  /**
  */
  void createCircle(float radius, int x, int y){
    float x1,y1,x2,y2;
    float angle;
    x1 =x,y1=y;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x1,y1,0.0f);
    for (angle=1.0f;angle<3*3.14159;angle+=0.2)
    {
        x2 = x1+sin(angle)*radius;
        y2 = y1+cos(angle)*radius;
        glVertex3f(x2,y2, 0.0f);
    }
    glEnd();
    //thanks to https://www.codeproject.com/Questions/64657/how-to-draw-a-filled-circle-in-opengl
  }
  /**
  */
  void createTriangle(float width, float height){
    glBegin(GL_TRIANGLES);
      glVertex3f(0.0f, (height/2), 0.0f);
      glVertex3f((width/2), -(height/2), 0.0f);
      glVertex3f(-(width/2), -(height/2), 0.0f);
    glEnd();
  }
  void createRectangle(float width, float height){
    glBegin(GL_QUADS);
      glVertex3f((width/2), -(height/2), 0.0f);
      glVertex3f(-(width/2), -(height/2), 0.0f);
      glVertex3f(-(width/2), (height/2), 0.0f);
      glVertex3f((width/2), (height/2), 0.0f);
    glEnd();
  }
  /**
  */
  void createBox(float width, float height, float depth){
     glBegin(GL_QUADS);
        // Far face.
        glNormal3f( 0.0f, 0.0f, -(depth/2));

      glVertex3f(-(width/2), -(height/2.0f), -(depth/2));
      glVertex3f(-(width/2),  (height/2.0f), -(depth/2));
      glVertex3f((width/2),  (height/2.0f), -(depth/2));
      glVertex3f((width/2), -(height/2.0f), -(depth/2));

        // Right face.
        glNormal3f((width/2), 0.0f, 0.0f);

      glVertex3f((width/2), -(height/2.0f), -(depth/2));
      glVertex3f((width/2),  (height/2.0f), -(depth/2));
      glVertex3f((width/2),  (height/2.0f),  (depth/2));
      glVertex3f((width/2), -(height/2.0f),  (depth/2));

        // Front face; offset.
        glNormal3f( 0.0f, 0.0f, (depth/2));

      glVertex3f(-(width/2), -(height/2.0f),  (depth/2));
      glVertex3f((width/2), -(height/2.0f),  (depth/2));
      glVertex3f((width/2),  (height/2.0f),  (depth/2));
      glVertex3f(-(width/2),  (height/2.0f),  (depth/2));


        // Left Face; offset.
        glNormal3f(-(depth/2), 0.0f, 0.0f);

      glVertex3f(-(width/2), -(height/2.0f), -(depth/2));
      glVertex3f(-(width/2), -(height/2.0f),  (depth/2));
      glVertex3f(-(width/2),  (height/2.0f),  (depth/2));
      glVertex3f(-(width/2),  (height/2.0f), -(depth/2));


        // Top Face; offset.
        glNormal3f(0.0f,(depth/2), 0.0f);

      glVertex3f((width/2), (height/2.0f), -(depth/2));
      glVertex3f((width/2),  (height/2.0f),  (depth/2));
      glVertex3f(-(width/2), (height/2.0f),  (depth/2));
      glVertex3f(-(width/2),  (height/2.0f), -(depth/2));

        // Bottom Face; offset.
        glNormal3f(0.0f, -(depth/2), 0.0f);

      glVertex3f((width/2), -(height/2.0f), -(depth/2));
      glVertex3f((width/2),  -(height/2.0f),  (depth/2));
      glVertex3f(-(width/2), -(height/2.0f),  (depth/2));
      glVertex3f(-(width/2), -(height/2.0f), -(depth/2));

        // All polygons have been drawn.
    glEnd();
  }
  /**
  */
  void drawRobot(float robotX, float robotY, float robotZ){

    GLUquadricObj *neck = gluNewQuadric();
    GLUquadricObj *antenna = gluNewQuadric();


    glLoadIdentity();
    glTranslatef(robotX, 0.4f+robotY, robotZ);
    if(robotHead == 1){
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //Left head
    }else if(robotHead == 2){
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); //Right head
    }

    glColor3f( 0.3f, 0.3f, 0.3f );
    createBox(0.8f,0.8f,0.8f); //head center


    glTranslatef(-0.2f, 0.0f, 0.42f);
    glColor3f( 0.8f, 0.8f, 0.8f);
    createCircle(0.1f, 0.0f, 0.0f);
    glColor3f( 0.8f, 0.1f, 0.1f);
    glTranslatef(0.0f, 0.0f, 0.02f);
    createCircle(0.08f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -0.02f);
    glTranslatef(0.2f, 0.0f, -0.42f);
    glTranslatef(0.2f, 0.0f, 0.42f);
    glColor3f( 0.8f, 0.8f, 0.8f);
    createCircle(0.1f, 0.0f, 0.0f);
    glColor3f( 0.8f, 0.1f, 0.1f);
    glTranslatef(0.0f, 0.0f, 0.02f);
    createCircle(0.08f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -0.02f);
    glTranslatef(-0.2f, 0.0f, -0.42f);

    glTranslatef(0.0f, 0.6f, 0.0f); // to antena center
    glColor3f( 0.4f, 0.4f, 0.4f );
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(antenna,0.1f,0.1f,0.4f,15,15);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    glLoadIdentity();
    glTranslatef(robotX, 0.0f+robotY, robotZ);
    //glRotatef(180.0f, 0.0f, 1.0f, 0.0f);// Back Body
    glColor3f( 0.4f, 0.4f, 0.4f );
    /*  glTranslatef(0.0f, -0.15f, 0.0f); // to neck from antena center*/
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(neck,0.3f,0.3f,0.3f,15,15);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    glColor3f( 0.3f, 0.3f, 0.3f );
    glTranslatef(0.0f, -1.15f, 0.0f);
    createBox(1.0f,2.0f,1.0f);
    glTranslatef(0.0f, 0.0f, 0.52f);
    glColor3f( 0.6f, 0.6f, 0.6f );
    createRectangle(0.7f, 1.7f);
    glTranslatef(0.0f, 0.0f, -0.52f);
    glTranslatef(0.0f, 0.3f, -0.52f);
    createTriangle(0.5f, 0.5f);
    glTranslatef(0.0f, -0.6f, 0.0f);
    createTriangle(0.5f, 0.5f);

  }
  /////////////////////////////////////////////////////////
  // Routine which actually does the drawing             //
  /////////////////////////////////////////////////////////
  /**
  * Routine which actually does the drawing
  * @param void
  * @return void
  */
  void Boot::CallBackRenderScene(void){
     // For our strings.

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     glFrustum(-1.0, 1.0, -1.0, 1.0, 1, 60.0);
     gluLookAt(robotPoint[0] + Boot::eyePoint[0], robotPoint[1] + Boot::eyePoint[1] , robotPoint[2] + Boot::eyePoint[2], robotPoint[0], robotPoint[1]+1, robotPoint[2], 0,1,0);


     // Need to manipulate the ModelView matrix to move our model around.
     glMatrixMode(GL_MODELVIEW);
     //TODO extract the robot code to class and building draw to block class
     glPushMatrix();
     drawRobot(robotPoint[0],robotPoint[1],robotPoint[2]);
     glPopMatrix();

     glLoadIdentity();
     glPushMatrix();
     glColor3f( 0.2f, 0.3f, 0.2f);
     Building newBuild;
     glTranslatef(-10.0f, 10.0f, 10.0f);
     newBuild.draw();
     glPopMatrix();

     glLoadIdentity();
     glPushMatrix();
     glColor3f( 0.3f, 0.2f, 0.2f );
     Building newBuild1;
     glTranslatef(-10.0f, 10.0f, -8.0f);
     newBuild1.draw();
     glPopMatrix();

     glLoadIdentity();
     glPushMatrix();
     glColor3f( 0.2f, 0.2f, 0.3f );
     Building newBuild3;
     glTranslatef(15.0f, 10.0f, -8.0f);
     newBuild3.draw();
     glPopMatrix();

     glLoadIdentity();
     glPushMatrix();
     glColor3f( 0.2f, 0.3f, 0.3f);
     Building newBuild4;
     glTranslatef(15.0f, 10.0f, 8.0f);
     newBuild4.draw();
     glPopMatrix();

     glLoadIdentity();
     glPushMatrix();
     glColor3f( 0.2f, 0.2f, 0.2f );
     Block newBlock;
     glTranslatef(0.0f, -3.15, 0.0f);
     newBlock.draw();
     glPopMatrix();
     //Robot
     glutSwapBuffers();

     // Now let's do the motion calculations.
  }

  ////////////////////////////////////////////////////////////
  // Callback function called when a normal key is pressed. //
  ////////////////////////////////////////////////////////////
  /**
  * Callback function called when a normal key is pressed.
  * @param key Key that was pressed and released
  * @param x
  * @param y
  * @return void
  */
  void Boot::myCBKey(unsigned char key, int x, int y)
  {
     switch (key) {
        case 113: // q turn left on intersect

  	 break;
        case 97:  // a turn right on intersect

  	 break;
        case 122: // z push forward

     break;
         case 101:  // e
         glEnable(GL_DEPTH_TEST);
         glClearDepth(1.0);
         glDepthFunc(GL_LESS);
     break;
         case 100: break; // d
         glDisable(GL_DEPTH_TEST);
         glClearDepth(1.0);
         glDepthFunc(GL_LESS);
     default:
        printf ("KP: break; No action for %d.\n", key);
        break;
      }
  }
  /**
  * Callback function called when a special key is pressed.
  * @param key Key that was pressed and released
  * @param x
  * @param y
  * @return void
  */
  void Boot::mySpecialKey(int key, int x, int y){
    switch(key){
      case GLUT_KEY_F1:
      //forward head facing and default lookat
      robotHead = 0;
      Boot::eyePoint[0] = 0;
      Boot::eyePoint[1] = 3;
      Boot::eyePoint[2] = -4;
      break;
      case GLUT_KEY_F2:
      //right head facing
        robotHead = 2;
      break;
      case GLUT_KEY_F3:
      //left head facing
        robotHead = 1;
      break;
      case GLUT_KEY_F4:
      //default lookat
      Boot::eyePoint[0] = 0;
      Boot::eyePoint[1] = 3;
      Boot::eyePoint[2] = -4;
      break;
      case GLUT_KEY_F5:
      //behind on left of robot
      Boot::eyePoint[0] = 4;
      Boot::eyePoint[1] = 4;
      Boot::eyePoint[2] = -4;
      break;
      case GLUT_KEY_F6:
      //behind on right of robot
      Boot::eyePoint[0] = -4;
      Boot::eyePoint[1] = 4;
      Boot::eyePoint[2] = -4;
      break;
      case GLUT_KEY_F7:
      //front on righ of robot
      Boot::eyePoint[0] = -4;
      Boot::eyePoint[1] = 4;
      Boot::eyePoint[2] = 4;
      break;
      case GLUT_KEY_F8:
      //front on left of robot
      Boot::eyePoint[0] = 4;
      Boot::eyePoint[1] = 4;
      Boot::eyePoint[2] = 4;
      break;
      case GLUT_KEY_F9:
      //behind on left of robot
      Boot::eyePoint[0] = 8;
      Boot::eyePoint[1] = 8;
      Boot::eyePoint[2] = -8;
      break;
      case GLUT_KEY_F10:
      //behind on right of robot
      Boot::eyePoint[0] = -8;
      Boot::eyePoint[1] = 8;
      Boot::eyePoint[2] = -8;
      break;
      case GLUT_KEY_F11:
      //front on right of robot
      Boot::eyePoint[0] = -8;
      Boot::eyePoint[1] = 8;
      Boot::eyePoint[2] = 8;
      break;
      case GLUT_KEY_F12:
      //behind on left of robot
      Boot::eyePoint[0] = 8;
      Boot::eyePoint[1] = 8;
      Boot::eyePoint[2] = 8;
      break;
    }

  }
  ///////////////////////////////////////////////////////////////
  // Callback routine executed whenever the window is resized. //
  //////////////////////////////////////////////////////////////
  /**
  * Callback routine executed whenever the window is resized.
  * @param Width
  * @param Height
  * @return void
  */
  void Boot::CallBackResizeScene(int Width, int Height)
  {
     if (Height == 0)
        Height = 1;
     //creates viewport with specified width
     glViewport(0, 0, Width, Height);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(45.0f,((GLfloat)Width)/((GLfloat)Height),0.1f,100.0f);
     //set matix mode to modelview
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     Window_Width  = Width;
     Window_Height = Height;
  }
  /**
  * Callback routine for when a mouse button is pressed or released.
  * @param buttonNum
  * @param btnState
  * @param x
  * @param y
  * @return void
  */
  void Boot::mouseFunctionality(int buttonNum, int btnState, int x, int y) {
    //rightDown
    if(buttonNum == GLUT_RIGHT_BUTTON) {
      if(rightDown == 0 && btnState == GLUT_DOWN) {
        rightDown = 1;
        leftDown = 0;
      }
    }
    //leftDown
    if(buttonNum == GLUT_LEFT_BUTTON) {
      if(leftDown == 0 && btnState == GLUT_DOWN) {
        leftDown = 1;
        rightDown = 0;
      }
    }
    //rightUp
    if(buttonNum == GLUT_RIGHT_BUTTON) {
      if(rightDown == 1 && btnState == GLUT_UP) {
        rightDown = 0;
        leftDown = 0;
      }
    }
    //rightUp
    if(buttonNum == GLUT_LEFT_BUTTON) {
      if(leftDown == 1 && btnState == GLUT_UP) {
        rightDown = 0;
        leftDown = 0;
      }
    }
  }

//Indicates an action to be taken when a special key is released
  void Boot::specKeyUp(int key, int x, int y){
    switch (key) {
      case GLUT_KEY_F2:
      robotHead=0;
      break;
      case GLUT_KEY_F3:
      robotHead=0;
      break;
    }
}
  ////////////////////////////////////////////////////////
  //   Setup your program before passing the control    //
  //   to the main OpenGL event loop.                   //
  ////////////////////////////////////////////////////////
  /**
  * Setup your program before passing the control to the main OpenGL event loop.
  * @param Width
  * @param Height
  * @return void
  */
  void Boot::MyInit(int Width, int Height)
  {
     // Color to clear color buffer to.
     glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

     // Depth to clear depth buffer to; type of test.
     glEnable(GL_DEPTH_TEST);
     glClearDepth(1.0);
     glDepthFunc(GL_LESS);

     // Enables Smooth Color Shading; try GL_FLAT for (lack of) fun.
     glShadeModel(GL_SMOOTH);
     Window_Width = 1000;
     Window_Height = 600;
     rightDown = 0;
     leftDown = 0;
     zcentre = 5;

     // Load up the correct perspective matrix; using a callback directly.
     Boot::CallBackResizeScene(Width,Height);
  }

  ///////////////////////////////////////////////////
  // main() function.                              //
  //   There are general steps in making           //
  //   an OpenGL application.                      //
  //   Inits OpenGL.                               //
  //   Calls our own init function                 //
  //   then passes control onto OpenGL.            //
  ///////////////////////////////////////////////////
  int main(int argc, char **argv)
  {
    //InitOpenGL
     glutInit(&argc, argv);

     // To see OpenGL drawing, take out the GLUT_DOUBLE request.
     glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

     // The following is for window creation.
     // Set Window size
     glutInitWindowSize(Boot::Window_Width, Boot::Window_Height);
     // Create and Open a window with its title.
     Boot::Window_ID = glutCreateWindow(PROGRAM_TITLE);

     // Register and install the callback function to do the drawing.
     glutDisplayFunc(&Boot::CallBackRenderScene);

     // If there's nothing to do, draw.
     glutIdleFunc(&Boot::CallBackRenderScene);

     // It's a good idea to know when our window's resized.
     glutReshapeFunc(&Boot::CallBackResizeScene);

     // Register and install the callback function for
     // Some keys and special keys.
     glutSpecialFunc(&Boot::mySpecialKey);

     glutKeyboardFunc(&Boot::myCBKey);
     //mousefunction
     glutMouseFunc(&Boot::mouseFunctionality);

     glutSpecialUpFunc(&Boot::specKeyUp);
     // OK, OpenGL's ready to go.  Let's call our own init function.
     Boot::MyInit(Boot::Window_Width, Boot::Window_Height);

     // Print out a bit of help dialog.
     printf("\n%s\n\n", PROGRAM_TITLE);
     printf("Print out some helpful information here.\n");
     printf("When you program, you can also use\n");
     printf("printf to do debugging.\n\n");

     // Above functions represents those you will do to set up your
     // application program.
     // Now pass off control to OpenGL.
     glutMainLoop();
     // Never returns.
     return 1;
  }
