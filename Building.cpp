#include "Building.h"
#include <cmath>

Building::Building(float x, float z)
   :xBase(x),zBase(z)
{

   time_t t;
   int random_numbers[5];
   int count =0;


   srand((unsigned) time(&t));

   while(count < 5) {
      int randNum =rand(); //Generate a random number
      bool found =false; //assume the random number hasnt been generated

      //make sure the random number hasnt already been generated
      for (int i = 0; i < 5; i++) {
	 if((random_numbers[i] % 3) == (randNum % 3)) {
	    found =true;
	    break; //once we have located the number we dont need to continue checking
	 }

	 //we have a new random number
	 if(!found) {
	    random_numbers[i] = randNum;
	    count++;
	 }
      }
   }

    // randomize building's height from 10 to 30
   height = abs(fmod(random_numbers[3], 21.0)) + 10.0;

   // width 5-8
   width = abs(fmod(random_numbers[0], 4.0)) + 5.0;

   // depth always 5-8
   depth = abs(fmod(random_numbers[2], 4.0)) + 5.0;

   //type 0-2, set health accordingly
   type = abs(int(random_numbers[1])) % 3;

      //shape 0-2
   shape = abs(int(random_numbers[4])) % 3;

   // set health according to type
   switch (type)
   {
      // Non-destroyable building
      case 0: health = -1;
	 break;
	 // Strong building
      case 1: health = 3;
	 break;
	 // Easily-destroyable building
      case 2: health = 1;
	 break;
	 // default case, should never happen
      default:
	 health = 1;
	 break;
   }

}

void Building::attack(){
   if(health > 0)
      --health;
}

void Building::createBox(float width, float height, float depth){
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

void Building::createSilo(float radius, float height, int x, int y){
   GLUquadricObj *silo;
   silo = gluNewQuadric();
   glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
   gluCylinder(silo,radius,radius,y,15,15);
   glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
   glColor3f(0.0f,0.0f,1.0f);
   /*float x1,y1,x2,y2;
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
   glEnd();*/
}

void Building::createPyramid(float width, float height, float depth)
{
     glBegin(GL_TRIANGLES);
      // Far face.
    glNormal3f( 0.0f, 0.0f, -(depth/2));

    glVertex3f(-(width/2), -(height/2.0f), -(depth/2));
    glVertex3f(0.0f,  (height/2.0f), 0.0f);
    glVertex3f((width/2),  -(height/2.0f), -(depth/2));

      // Right face.
    glNormal3f((width/2), 0.0f, 0.0f);

    glVertex3f((width/2), -(height/2.0f), -(depth/2));
    glVertex3f(0.0f,  (height/2.0f), 0.0f);
    glVertex3f((width/2), -(height/2.0f),  (depth/2));

      // Front face; offset.
    glNormal3f( 0.0f, 0.0f, (depth/2));

    glVertex3f(-(width/2), -(height/2.0f),  (depth/2));
    glVertex3f(0.0f,  (height/2.0f), 0.0f);
    glVertex3f((width/2), -(height/2.0f),  (depth/2));


      // Left Face; offset.
    glNormal3f(-(depth/2), 0.0f, 0.0f);

    glVertex3f(-(width/2), -(height/2.0f), -(depth/2));
    glVertex3f(0.0f,  (height/2.0f), 0.0f);
    glVertex3f(-(width/2), -(height/2.0f),  (depth/2));

    glEnd();

    glBegin(GL_QUADS);
      // Bottom Face; offset.
    glNormal3f(0.0f, -(depth/2), 0.0f);

    glVertex3f((width/2), -(height/2.0f), -(depth/2));
    glVertex3f((width/2),  -(height/2.0f),  (depth/2));
    glVertex3f(-(width/2), -(height/2.0f),  (depth/2));
    glVertex3f(-(width/2), -(height/2.0f), -(depth/2));

      // All polygons have been drawn.
  glEnd();
}

void Building::draw(){
   switch (health){
      case 3:
	 glColor3f(0.0,1.0,0.0);
	 break;
      case 2:
	 glColor3f(1.0,1.0,0.0);
	 break;
      case 1:
	 glColor3f(1.0,0.0,0.0);
	 break;
      case 0:
	 glColor3f(0.0,0.0,1.0);
	 break;
      case -1:
	 glColor3f(0.5,0.5,0.5);
	 break;
      default:
	 glColor3f(1.0,1.0,1.0);
	 break;
   }
   if (health != 0)
   {
      glTranslatef(0.0f, height/2.0f, 0.0f);
      switch (shape)
      {
	 case 0:
	    createBox(width,height,depth);
	    break;
	 case 1:
	    createSilo(width/2,height,0.0,height);
	    break;
	 case 2:
	    createPyramid(width,height,depth);
	    break;
	 default:
	    glColor3f(1.0f,0.0f,1.0f);
	    createBox(width,height,depth);
	    break;
      }
      glTranslatef(0.0f, -(height/2.0f), 0.0f);
   }
}
