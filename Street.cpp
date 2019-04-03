#include "Street.h"
#include "Building.h"
#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <iostream>
#include <cstdlib>
///Draws the street network
///@author Jeff Deurloo
void Street::draw(){
  //center on robot
    //glTranslatef(width/2,0,0);
    glTranslatef(width/2,0,-width/2);
    for(int j=0;j<citySize+1;j++){
        //draw one column straight to the end

        //draw one unit
       glColor3f(0.45,0.45,0.45);
       glBegin(GL_QUADS);
       glVertex3f(0,0,0);
       glVertex3f(-width,0,0);
       glVertex3f(-width,0,citySize*blockLength);
       glVertex3f(0,0,citySize*blockLength);
       glEnd();

       //draw the lines in the center of the road
       glColor3f(1.0,1.0,0.1);
       for (int i = 0; i < citySize * blockLength + 1; i += 4){
	  if (i % 8 == 0) // skip every second iteration so it's not a solid line
	  {
	     glBegin(GL_QUADS);
	     glVertex3f(-width/2-0.25, 0.1, i+0.0);
	     glVertex3f(-width/2+0.25, 0.1, i+0.0);
	     glVertex3f(-width/2+0.25, 0.1, i+4.0);
	     glVertex3f(-width/2-0.25, 0.1, i+4.0);
	     glEnd();
	  }
       }

        //Shift forward and draw again
        //glTranslatef(0,0,blockLength);

        //once done shift back and over to do it again
        glTranslatef(-blockLength,0,0);
    }
    glTranslatef(blockLength,0,0);
    //Rotate , shift and draw it again
    //glTranslatef(-width/2,0,0);
    glRotatef(90,0,1,0);
    //glTranslatef(0,0,width/2);
    for(int j=0;j<citySize+1;j++){
       //draw one column straight to the end
       //draw one unit
       glColor3f(0.45,0.45,0.45);
       glBegin(GL_QUADS);
       glVertex3f(0,0,0);
       glVertex3f(-width,0,0);
       glVertex3f(-width,0,citySize*blockLength);
       glVertex3f(0,0,citySize*blockLength);
       glEnd();
       //Shift forward and draw again

       glColor3f(1.0,1.0,0.1);
       for (int i = 0; i < citySize * blockLength + 1; i += 4){
	  if (i % 8 == 0) // skip every second iteration so it's not a solid line
	  {
	     glBegin(GL_QUADS);
	     glVertex3f(-width/2-0.25, 0.1, i+0.0);
	     glVertex3f(-width/2+0.25, 0.1, i+0.0);
	     glVertex3f(-width/2+0.25, 0.1, i-4.0);
	     glVertex3f(-width/2-0.25, 0.1, i-4.0);
	     glEnd();
	  }
       }

       //once done shift back and over to do it again
       glTranslatef(-blockLength,0,0);
    }
    glTranslatef(blockLength,0,0);
    glTranslatef(0, 0, -width);
    glColor3f(0.45,0.45,0.45);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(-width,0,0);
    glVertex3f(-width,0,width);
    glVertex3f(0,0,width);
    glEnd();

}
/*void Street::draw(){
  //center on robot
    //glTranslatef(width/2,0,0);
    glTranslatef(width/2,0,-width/2);
    for(int j=0;j<citySize+1;j++){
        //draw one column straight to the end

        //draw one unit
        glBegin(GL_QUADS);
            glVertex3f(0,0,0);
            glVertex3f(-width,0,0);
            glVertex3f(-width,0,citySize*blockLength);
            glVertex3f(0,0,citySize*blockLength);
        glEnd();
        //Shift forward and draw again
        //glTranslatef(0,0,blockLength);

        //once done shift back and over to do it again
        glTranslatef(-blockLength,0,0);
    }
    glTranslatef(blockLength,0,0);
    //Rotate , shift and draw it again
    //glTranslatef(-width/2,0,0);
    glRotatef(90,0,1,0);
    //glTranslatef(0,0,width/2);
        for(int j=0;j<citySize+1;j++){
        //draw one column straight to the end
        //draw one unit
        glBegin(GL_QUADS);
            glVertex3f(0,0,0);
            glVertex3f(-width,0,0);
            glVertex3f(-width,0,citySize*blockLength);
            glVertex3f(0,0,citySize*blockLength);
        glEnd();
        //Shift forward and draw again

        //once done shift back and over to do it again
        glTranslatef(-blockLength,0,0);
    }
    glTranslatef(blockLength,0,0);
    glTranslatef(0, 0, -width);
    glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(-width,0,0);
        glVertex3f(-width,0,width);
        glVertex3f(0,0,width);
    glEnd();

}*/

/*!
 Function that check if the robot's position is a at an intersection
 @param xpos indicates the robot's position in the x-axis
 @param zpos indicates the robot's position in the y-axis
 @author Jeff Deurloo
*/
bool Street::checkIfIntersection(const float xpos, const float zpos){
    //printf ("Point %f %f.\n", xpos, zpos);
    //printf ("PointMod %f %f.\n", fmod(xpos,blockLength), fmod(zpos,blockLength));
    bool x = fmod(xpos, 44.0f) == 0;
    bool z = fmod(zpos, 44.0f) == 0;
    return (x && z);
}

const float Street::getBlockLength(){
    return blockLength;
}

const float Street::getWidth(){
    return width;
}

const int Street::getSize(){
    return citySize;
}
