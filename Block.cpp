#include "Block.h"
#include "Building.h"
#include "Boot.h"
#include <cmath>
#include <iostream>
#include <vector>

void Block::createBox(float width, float height, float depth){
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
void Block::draw(GLenum mode){

  createBox(40,1,40);
  glEnable(GL_STENCIL_TEST);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  glTranslatef(-20.0f, 0.0f, -20.0f);
  glTranslatef(buildings[0].xBase,0.0f,buildings[0].zBase);
  buildings[0].draw(mode, ID*4+1);
  glTranslatef(-buildings[0].xBase,0.0f,-buildings[0].zBase);

 // Boot::buildingIndex[Boot::stencilIndex] = buildings[1];
  glTranslatef(buildings[1].xBase,0.0f,buildings[1].zBase);
  buildings[1].draw(mode, ID*4+2);
  glTranslatef(-buildings[1].xBase,0.0f,-buildings[1].zBase);

 // Boot::buildingIndex[Boot::stencilIndex] = buildings[2];
  glTranslatef(buildings[2].xBase,0.0f,buildings[2].zBase);
  buildings[2].draw(mode, ID*4+3);

  glTranslatef(-buildings[2].xBase,0.0f,-buildings[2].zBase);
 // Boot::buildingIndex[Boot::stencilIndex] = buildings[3];
  glTranslatef(buildings[3].xBase,0.0f,buildings[3].zBase);
  buildings[3].draw(mode, ID*4+4);
  glTranslatef(-buildings[3].xBase,0.0f,-buildings[3].zBase);
  glTranslatef(20.0f, 0.0f, 20.0f);
  glDisable(GL_STENCIL_TEST);
}
Block::Block(){

}
Block::Block(int x){
    ID = x;
    buildings[0] = Building(10.0f, 10.0f); // x, z, y base
    buildings[2] = Building(10.0f, 30.0f);
    buildings[1] = Building(30.0f, 10.0f);
    buildings[3] = Building(30.0f, 30.0f);
    int bi = x + 10;
    buildings[0].idNum = bi;
    buildings[2].idNum = bi + 10;
    buildings[1].idNum = bi + 20;
    buildings[3].idNum = bi + 30;
}
