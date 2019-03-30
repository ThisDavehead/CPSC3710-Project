#include "Street.h"
///Draws the street network
///@author Jeff Deurloo
void Street::draw(){
    //center on robot
    //glTranslatef(width/2,0,0);

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
    glTranslatef(0,0,width/2);
}

/*!
 Function that check if the robot's position is a at an intersection
 @param xpos indicates the robot's position in the x-axis
 @param zpos indicates the robot's position in the y-axis
 @author Jeff Deurloo
*/
bool Street::checkIfIntersection(const float xpos, const float zpos){
     printf ("Point %f %f.\n", xpos, zpos);
    printf ("PointMod %f %f.\n", fmod(xpos,blockLength), fmod(zpos,blockLength));
    bool x = (abs(fmod(xpos,blockLength)) < 5 || abs(fmod(xpos,blockLength)) > blockLength-5) || (fmod(xpos,blockLength) > -5 && fmod(xpos,blockLength) < 5);
    bool z = (abs(fmod(zpos,blockLength)) < 5 || abs(fmod(zpos,blockLength)) > blockLength-5) || (fmod(zpos,blockLength) > -5 && fmod(zpos,blockLength) < 5);
    if(x && z)
        return true;
    else
return false;
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
