#include "Street.h"

void Street::draw(){
   //produce them iteratively to form the network
   //For now, let's make one street then work on generating the network
   //when we get back here

   glBegin(GL_QUADS);
   glVertex3f(0,0,0);
   glVertex3f(width,0,0);
   glVertex3f(width,0,blockLength);
   glVertex3f(0,0,blockLength);
   glEnd();

}

bool Street::checkIfIntersection(){
   /*to be implemented later*/
   return false;
}
