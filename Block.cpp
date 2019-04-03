#include "Block.h"
#include "Building.h"
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
void Block::draw(){
  createBox(40,1,40);
  glTranslatef(-20.0f, 0.0f, -20.0f);
  glTranslatef(buildings[0].xBase,0.0f,buildings[0].zBase);
  buildings[0].draw();
  glTranslatef(-buildings[0].xBase,0.0f,-buildings[0].zBase);

  glTranslatef(buildings[1].xBase,0.0f,buildings[1].zBase);
  buildings[1].draw();
  glTranslatef(-buildings[1].xBase,0.0f,-buildings[1].zBase);

  glTranslatef(buildings[2].xBase,0.0f,buildings[2].zBase);
  buildings[2].draw();
  glTranslatef(-buildings[2].xBase,0.0f,-buildings[2].zBase);

  glTranslatef(buildings[3].xBase,0.0f,buildings[3].zBase);
  buildings[3].draw();
  glTranslatef(-buildings[3].xBase,0.0f,-buildings[3].zBase);
  glTranslatef(20.0f, 0.0f, 20.0f);

}
Block::Block(){

}
Block::Block(int x){
  if(x == 2){
    buildings[0] = Building(10.0f,10.0f); // x, z, y base
    buildings[2] = Building(10.0f, 30.0f);
    buildings[1] = Building(30.0f, 10.0f);
    buildings[3] = Building(30.0f, 5.0f);
  }else{
    buildings[0] = Building(10.0f, 10.0f); // x, z, y base
    buildings[2] = Building(10.0f, 30.0f);
    buildings[1] = Building(30.0f, 10.0f);
    buildings[3] = Building(30.0f, 30.0f);
  }
}
/*void Block::init(){
  buildings[0] = Building(10.0f,10.0f); // x, z, y base
  buildings[2] = Building(10.0f, 30.0f);
  buildings[1] = Building(30.0f, 10.0f);
  buildings[3] = Building(30.0f, 30.0f);
}*/
  //time_t t;
  //srand((unsigned) time(&t));
  //float locations[4] = {-1.0f, -1.0f, -1.0f, -1.0f};
  //locations[0] = (rand() % 4);
  //buildings[0] = Building(10.0f,5 + 10 * locations[0]);
  //locations[1] = (rand() % 4) + 4;

  //buildings[1].xBase = 15.0f;
//  buildings[1].zBase = 5 * locations[1];

  //locations[2] = (rand() % 4) + 8;

  //buildings[2].xBase = 25.0f;
  //buildings[2].zBase = 5 * locations[2];

  //locations[3] = (rand() % 4) + 12;

  //buildings[3].xBase = 35.0f;
  //buildings[3].zBase = 5 * locations[3];
