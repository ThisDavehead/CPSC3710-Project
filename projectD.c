// CPSC 3710 Project
// By David Adams, Jeffrey Deurloo

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

// Window ID, window width and height.
int Window_ID;
int Window_Width = 600;
int Window_Height = 600;

// Global variable for city blocks numbers, widths, and depths, so we can all
// understand each other's code.
static const int XBlockNum = 20; // The number of city blocks along x-axis
static const int ZBlockNum = 20; // The number of city blocks along z-axis
static const int XBlockSize = 20; // Width of each city block, including half the street. We'll say each street is 4 wide. So each city block has 16 units to work with.
static const int ZBlockSize = 20; // Depth of city block, including 4 unit allowance for each half of street.

// Global variable for keeping track of left mouse button clicks.
int LeftMouse;

// Global variables to keep track of the x and z location of the robot
// as well as the LookAt, the z-coordinate of which is initialized to zRobot + 5.0
///////// Note: As the robot becomes able to turn, the camera must follow.
//////// Addendum: Unless we choose to rotate the world and always just move the Robot in the same direction
//////// along the z-axis
float XRobot = 0.0f;
float ZRobot = 0.0f;

// Global variable to keep track of the direction the robot is facing.
// When the head is being drawn, its rotation can be derived from this,
// depending on the input.
float Y_Rot = 0.0f;
float AntennaRot = 0.0f;

// Globabl variable to keep track of pausing.
int Pause = -1;

// pauseCheck Function
// Checks whether the game is paused or not.
// If it is, signify that somehow.
void pauseCheck()
{
}


// buttonCheck Function
// Checks the values of the global left mouse click variable.
// Note that this function is only needed if we want to implement
// a drag-and-click feature where we can mow buildings down en-masse.
void buttonCheck()
{
   if (LeftMouse)
   {
   }
}


// display Function
// Draws the scene
void display()
{

   // Need to manipulate the ModelView matrix
   glMatrixMode(GL_MODELVIEW);

   // Reset everything
   glLoadIdentity();

   // Check for button inputs
   buttonCheck();
   
   // Clear the color and depth buffers.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Draw the robot.
   glPushMatrix();
   glTranslatef(-XRobot, -1, -ZRobot);
   glColor4f(0.2f, 0.1f, 0.9f, 0.7f);
   glutSolidCube(2);
   glTranslatef(XRobot, 1, ZRobot);
   glPopMatrix();

   // None of the city-drawing stuff works yet. Sorry.
   // Draw the 20 x 20 city blocks with various buildings. I don't know how to do this.
   // Rotate the matrix back to origin so we can draw the robot normally and move it in the same direction.
   glRotatef(Y_Rot, 0.0f, 1.0f, 0.0f);
   // Draw the streets parallel to z axis.
   for (int i = (0 - XBlockNum/2)*XBlockSize; i < (XBlockNum / 2) *XBlockSize; i += XBlockSize)
   {
      // draw the center lines
      for (int j = (0 - ZBlockNum/2)*ZBlockSize; j < (ZBlockNum/2)*ZBlockSize; j += 5)
      {
	 glPushMatrix();
	 glColor4f(0.9f, 0.9f, 0.1f, 1.0f);
	 glBegin(GL_LINES);
	 glVertex3f(i*1.0f, 0.1f, j-1.0f);
	 glVertex3f(i*1.0f, 0.1f, j+1.0f);
	 glEnd();
	 glPopMatrix();
      }
      // draw the asphalt
      glPushMatrix();
      glColor4f(0.7f, 0.7f, 0.9f, 1.0f);
      glBegin(GL_QUADS);
      glVertex3f(i-2.0f, 0.0f, (0 - (ZBlockNum/2) * ZBlockSize) * 1.0f);
      glVertex3f(i+2.0f, 0.0f, (0 - (ZBlockNum/2) * ZBlockSize) * 1.0f);
      glVertex3f(i+2.0f, 0.0f, ((ZBlockNum/2) * ZBlockSize) * 1.0f);
      glVertex3f(i-2.0f, 0.0f, ((ZBlockNum/2) * ZBlockSize) * 1.0f);
      glEnd();
      glPopMatrix();
   }

   // Rotate the world according to the Robot's orientation, rather than rotating the robot.
   glRotatef(-Y_Rot, 0.0f, 1.0f, 0.0f);
   
   glLoadIdentity();

   // The new configuration of drawn things is shown
   glutSwapBuffers();
}


// myMouse Function
// Defines what happens when a mouse button is clicked.
// As defined below, a left click will set the left button state to down.
void myMouse(int button, int state, int x, int y)
{
   switch (button)
   {
      case GLUT_LEFT_BUTTON:
	 LeftMouse = (state == GLUT_DOWN);
	 break;
   default:
      break;
    }
}


// myKey Function
// Defines what happens what certain keys are pressed.
void myKey(unsigned char key, int x, int y)
{
   switch(key)
   {
	   // p key. Switches the pause value between 1 and -1.
	case 112:
		   Pause = Pause * -1;
		break;

		// r key. Returns robot to origin.
	case 114:
		XRobot = 0;
		ZRobot = 0;
		Y_Rot = 0;
	  break;

	// z key. Moves the robot forward. This will depend on which way it's facing.
	// This is almost certainly wrong right now. But it can serve as a placeholder.
	case 122:
		if (Y_Rot / 90 == 0)
		  ZRobot -= 1.0f;
		 else if (Y_Rot / 90 == 1)
		  XRobot += 1.0f;
		 else if (Y_Rot / 90 == 2)
		  ZRobot += 1.0f;
		 else
		  XRobot -= 1.0f;
	 break;
      default:
	 break;
   }
}


// myResize function
// Callback function  for resizing of window
void myResize(int Width, int Height)
{
   // Check for invalid height
   if (Height == 0)
      Height = 1;

   glViewport(0, 0, Width, Height);

   // Define projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(-10.0f,10.0f,-10.0f,10.0f,ZRobot-50.0f,ZRobot+50.0f);


   // Now define the LookAt perspective
   //
   /***/// This needs to change to reflect the direction the Robot is facing.
   //
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0.0f, 1.0f, ZRobot+5.0f, 0.0f, 0.0f, ZRobot, 0.0f, 1.0f, 0.0f);
   

   Window_Width  = Width;
   Window_Height = Height;
}

// myInit Function
// Initializes the window to desired specifications
void myInit(int Width, int Height) 
{
   // Clear color set to black
   glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

   // Set depth to clear buffer to
   glClearDepth(1.0);
   glDepthFunc(GL_LESS); 

   // Using smooth color shading because it allows for maximum fun
   glShadeModel(GL_SMOOTH);

   // Make sure the right-sized perspective matrix is used
   myResize(Width,Height);
}


// main() function.
// Initializes OpenGL.
// Calls custom initialization function.
// Passes control onto OpenGL.
int main(int argc, char **argv)
{
   
   glutInit(&argc, argv);
   
   // To see OpenGL drawing, take out the GLUT_DOUBLE request.
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   // Set window size
   glutInitWindowSize(Window_Width, Window_Height);

   // Enable depth testing
   glEnable(GL_DEPTH_TEST);

   // Enable backface culling
   glEnable(GL_CULL_FACE);
   
   // Create and open a window with program title
   Window_ID = glutCreateWindow("CPSC 3710 Project - Demolish-Bot");

   // Now OpenGL is ready for the program to be initialized
   myInit(Window_Width, Window_Height);
   
   // Establish the function which will be drawing
   glutDisplayFunc(&display);

   // Draw the scene when idle
   glutIdleFunc(&display);

   // Keep track of resizing
   glutReshapeFunc(&myResize);

   // Install function for key presses
   glutKeyboardFunc(&myKey);
   
   // Install function for mouse-clicking
   glutMouseFunc(&myMouse);

   // Now OpenGL takes over.
   glutMainLoop();
   return 1;  // This shouldn't happen.
}
