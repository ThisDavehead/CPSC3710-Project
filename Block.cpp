#include "Block.h"
#include "Building.h"
#include <cmath>
#include <iostream>
#include <vector>

//Building* Block::buildings = new Building[4];

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

  buildings[0].draw();
  buildings[1].draw();
  buildings[2].draw();
  buildings[3].draw();

}
Block::Block(){
  time_t t;
  srand((unsigned) time(&t));
  float locations[4] = {-1.0f, -1.0f, -1.0f, -1.0f};
  locations[0] = (rand() % 4);
  buildings[0] = Building(5.0f, 5 * locations[0]); // x, z, y base

  locations[1] = (rand() % 4) + 4;
  buildings[1] = Building(15.0f, 5 * locations[1]);
  //buildings[1].xBase = 15.0f;
//  buildings[1].zBase = 5 * locations[1];

  locations[2] = (rand() % 4) + 8;
  buildings[2] = Building(25.0f, 5 * locations[2]);
  //buildings[2].xBase = 25.0f;
  //buildings[2].zBase = 5 * locations[2];

  locations[3] = (rand() % 4) + 12;
  buildings[3] = Building(35.0f, 5 * locations[3]);
  //buildings[3].xBase = 35.0f;
  //buildings[3].zBase = 5 * locations[3];
}
