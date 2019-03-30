#include "Block.h"
#include "Building.h"
#include <cmath>

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
}
Block::Block(){
  time_t t;
  srand((unsigned) time(&t));
  float locations[4] = {-1.0f, -1.0f, -1.0f, -1.0f};
  locations[0] = (rand() % 4);
  buildings.push_back(new Building(5.0f, 5 * locations[0])); // x, z, y base
  locations[1] = (rand() % 4) + 4;
  buildings.push_back(new Building(15.0f, 5 * locations[1]));
  locations[2] = (rand() % 4) + 8;
  buildings.push_back(new Building(25.0f, 5 * locations[2]));
  locations[3] = (rand() % 4) + 12;
  buildings.push_back(new Building(35.0f, 5 * locations[3]));
}
