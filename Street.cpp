#include "Street.h"

void Street::draw(){
    //center on robot
    glTranslatef(width/2,0,0);

    for(int j=0;j<citySize;j++){
        //draw one column straight to the end
        for(int i=0;i<citySize;i++){
        //draw one unit
        glBegin(GL_QUADS);
            glVertex3f(0,0,0);
            glVertex3f(-width,0,0);
            glVertex3f(-width,0,blockLength);
            glVertex3f(0,0,blockLength);
        glEnd();
        //Shift forward and draw again
        glTranslatef(0,0,blockLength);
        }
        //once done shift back and over to do it again
        glTranslatef(-blockLength,0,-(citySize*blockLength));
    }

    //Rotate , shift and draw it again
    glRotatef(90,0,1,0);
    glTranslatef(0,0,-width/2)
        for(int j=0;j<citySize;j++){
        //draw one column straight to the end
        for(int i=0;i<citySize;i++){
        //draw one unit
        glBegin(GL_QUADS);
            glVertex3f(0,0,0);
            glVertex3f(-width,0,0);
            glVertex3f(-width,0,blockLength);
            glVertex3f(0,0,blockLength);
        glEnd();
        //Shift forward and draw again
        glTranslatef(0,0,blockLength);
        }
        //once done shift back and over to do it again
        glTranslatef(-blockLength,0,-(citySize*blockLength));
    }

}

bool Street::checkIfIntersection(float xpos, float ypos){
   /*to be implemented later*/
   return false;
}
