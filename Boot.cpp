/**
    CPSC 3710 - Project
    Boot.cpp
    Purpose: Boots game and runs the game loop.

    @author Matthew Davison
    @version 1.1 4/10/16
*/
#define PROGRAM_TITLE "Project"

#include "Boot.h"

  // Some global variables.
  // Window IDs, window width and height
  int Boot::Window_ID = 0;
  int Boot::Window_Width = 1000;
  int Boot::Window_Height = 600;
  int Boot::rightDown = 0;
  int Boot::leftDown = 0;
  int Boot::zcentre = 5;
  float Boot::eyePoint[3] = {0, 3, 4};
  int Boot::viewKey = GLUT_KEY_F4;

  // Global variable for our robot;
  Robot Boot::robot = Robot();
  Street Boot::network = Street();
  City Boot::city = City();
  //Block* Boot::blocks = new Block[4000];

  // Global variable for whether our game is paused or not
int Boot::paused = -1;
#define PAUSE_MESSAGE "PAUSED"

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
     rotateCameras();
     gluLookAt(robot.point[0] + Boot::eyePoint[0], robot.point[1] + Boot::eyePoint[1] , robot.point[2] + Boot::eyePoint[2], robot.point[0], robot.point[1]+1, robot.point[2], 0,1,0);


     // Need to manipulate the ModelView matrix to move our model around.
     glMatrixMode(GL_MODELVIEW);

     glPushMatrix();
     glLoadIdentity();
     robot.draw(robot.point[0],robot.point[1],robot.point[2]);
     glPopMatrix();

     //draw the street netwoek
     glLoadIdentity();
     glPushMatrix();
     glColor3f( 0.45f, 0.45f, 0.45f );
     glTranslatef(0.0f, -2.15f, 0.0f);
     network.draw();
     glPopMatrix();

     glLoadIdentity();
     city.draw();

     // Display pause screen if we're paused.
     if (paused == 1)
	         pauseGame();

     glutSwapBuffers();
     // Now let's do the motion calculations.

  }

  ////////////////////////////////////////////////////////////
  // Callback function called when game is paused.          //
  ////////////////////////////////////////////////////////////
  /**
  * Callback function called when game is paused.
  * Displays pause message
  * @return void
  */
void Boot::pauseGame(){
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glDisable(GL_DEPTH_TEST);
   glLoadIdentity();
   glOrtho(0,Window_Width,0,Window_Height,-1.0,1.0);
   // Draw textbox for pause message
   glBegin(GL_QUADS);
   glColor4f(1.0,1.0,1.0,1.0);
   glVertex2f(Window_Width*0.2, Window_Height/2-24);
   glVertex2f(Window_Width - Window_Width*0.2, Window_Height/2-24);
   glVertex2f(Window_Width - Window_Width*0.2, Window_Height/2+24);
   glVertex2f(Window_Width*0.2, Window_Height/2+24);
   glEnd();
   // Print Pause message
   glColor4f(0.1, 0.1, 0.1, 1.0);
   char buf[16];
   char* str;
   str = buf;
   int i,len=strlen(str);
   sprintf(buf, PAUSE_MESSAGE);
   glRasterPos2f(Window_Width/2.0 - Window_Width*0.05, Window_Height/2.0 - Window_Height*0.015);
   for (i = 0; i < len; ++i)
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str++);
   // To ease, simply translate up.
   glTranslatef(6.0f, Window_Height - 14, 0.0f);
   glEnable(GL_DEPTH_TEST);
   glPopMatrix();
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

   // We start with GL_DECAL mode.
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
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
	case 112: // p pauses or unpauses the game
	   paused *= -1;
	   break;
        case 113: // q turn left on intersect
	   if(paused == -1 && network.checkIfIntersection(robot.point[0],robot.point[2])){
	      robot.left();
	      rotateCameras();
	   }
	   break;
	case 114:  // r reset
	   if (paused == -1){
	      robot.point[0] = 0;
	      robot.point[2] = 0;
	   }
	   break;
        case 97:  // a turn right on intersect
          if(paused == -1 && network.checkIfIntersection(robot.point[0],robot.point[2])){
            robot.right();
            rotateCameras();
          }
  	 break;
        case 122: // z push forward
	   if (paused == -1)
	      robot.move();
        printf ("x: %d z: %d\n", robot.point[0], robot.point[2]);
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
  void Boot::rotateCameras(){
     if (paused == -1){
    bool change=true;
	float neweyePoint[3] = {0, 0, 0};
	switch(viewKey){
	   case GLUT_KEY_F1:
	      //forward head facing and default lookat
	      //robot.head = 0;
	      neweyePoint[0] = 0;
	      neweyePoint[1] = 3;
	      neweyePoint[2] = -4;
	      change=true;
	      break;
	   case GLUT_KEY_F4:
	      //default lookat
	      neweyePoint[0] = 0;
	      neweyePoint[1] = 3;
	      neweyePoint[2] = -4;
	      change=true;
	      break;
	   case GLUT_KEY_F5:
	      //behind on left of robot
	      neweyePoint[0] = 4;
	      neweyePoint[1] = 4;
	      neweyePoint[2] = -4;
	      change=true;
	      break;
	   case GLUT_KEY_F6:
	      //behind on right of robot
	      neweyePoint[0] = -4;
	      neweyePoint[1] = 4;
	      neweyePoint[2] = -4;
	      change=true;
	      break;
	   case GLUT_KEY_F7:
	      //front on righ of robot
	      neweyePoint[0] = -4;
	      neweyePoint[1] = 4;
	      neweyePoint[2] = 4;
	      change=true;
	      break;
	   case GLUT_KEY_F8:
	      //front on left of robot
	      neweyePoint[0] = 4;
	      neweyePoint[1] = 4;
	      neweyePoint[2] = 4;
	      change=true;
	      break;
	   case GLUT_KEY_F9:
	      //behind on left of robot
	      neweyePoint[0] = 8;
	      neweyePoint[1] = 8;
	      neweyePoint[2] = -8;
	      change=true;
	      break;
	   case GLUT_KEY_F10:
	      //behind on right of robot
	      neweyePoint[0] = -8;
	      neweyePoint[1] = 8;
	      neweyePoint[2] = -8;
	      change=true;
	      break;
	   case GLUT_KEY_F11:
	      //front on right of robot
	      neweyePoint[0] = -8;
	      neweyePoint[1] = 8;
	      neweyePoint[2] = 8;
	      change=true;
	      break;
	   case GLUT_KEY_F12:
	      //behind on left of robot
	      neweyePoint[0] = 8;
	      neweyePoint[1] = 8;
	      neweyePoint[2] = 8;
	      change=true;
	      break;
	   default:
	       change=false;
	      break;
	}
	if(change){
        if(robot.facing == -1.0f){ //right
           Boot::eyePoint[0] = -neweyePoint[2];
           Boot::eyePoint[2] = neweyePoint[0];
        }else if(robot.facing == 1.0f){ //left
           Boot::eyePoint[0] = neweyePoint[2];
           Boot::eyePoint[2] = neweyePoint[0];
        }else if(robot.facing == 0.0f){ //front
           Boot::eyePoint[0] = neweyePoint[0];
           Boot::eyePoint[2] = neweyePoint[2];
        }if(robot.facing == -2.0f || robot.facing == 2.0f){ //back
           Boot::eyePoint[0] = neweyePoint[0];
           Boot::eyePoint[2] = -neweyePoint[2];
        }
	}
     }
  }
void Boot::mySpecialKey(int key, int x, int y){
   if (paused == -1){
    switch(key){
    case GLUT_KEY_F1:
        robot.head = 0;
        viewKey=key;
        break;
        case GLUT_KEY_F2:
	      //right head facing
	      robot.head = 2;
	      break;
	   case GLUT_KEY_F3:
	      //left head facing
	      robot.head = 1;
    break;
       default:
          viewKey = key;
          break;
   };
     if(viewKey!=GLUT_KEY_F2&&viewKey!=GLUT_KEY_F3)
     Boot::rotateCameras();
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
     gluPerspective(45.0f,((GLfloat)Width)/((GLfloat)Height),0.1f,10000.0f);
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
      robot.head=0;
      break;
      case GLUT_KEY_F3:
      robot.head=0;
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
    time_t t;
    srand((unsigned) time(&t));
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

     glutSpecialUpFunc(&Boot::specKeyUp);

     glutKeyboardFunc(&Boot::myCBKey);
     //mousefunction
     glutMouseFunc(&Boot::mouseFunctionality);
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
