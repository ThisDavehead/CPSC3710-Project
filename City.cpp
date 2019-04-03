#include "City.h"
#include <cmath>
#include <iostream>
#include <vector>

void City::draw(){
  glPushMatrix();
  glTranslatef(-22.0f, -2.50f, 22.0f);
  for (int i = 0; i < 20; i++) {
     if(i != 0){
       glLoadIdentity();
       glTranslatef(-22.0f, -2.50f, 22.0f);
       glTranslatef(0.0f, 0.0f, 44.0f*i);
     }
     for (int j = 0; j < 20; j++) {
       if(j != 0){
         glTranslatef(-44.0f, 0.0f, 0.0f);
       }
       glColor3f( 0.45f, 0.7f, 0.45f );
       blocks[i*20+j].draw();
     }
   }
   glPopMatrix();
}
City::City(){
  for (int x = 0; x < 4000; x++){
    blocks[x] = Block(x);
  }
}
