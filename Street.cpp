#include "Street.h"

void Street::draw(){
    //Draw a single unit of street
    glTranslatef(width/2,0,0);
    glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(-width,0,0);
        glVertex3f(-width,0,blockLength);
        glVertex3f(0,0,blockLength);
    glEnd();

}

bool Street::checkIfIntersection(){
   /*to be implemented later*/
   return false;
}
