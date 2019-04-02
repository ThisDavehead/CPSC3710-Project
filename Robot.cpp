
#include "Robot.h"

Robot::Robot(){
   head = 0;
   for (int i = 0; i < 3; ++i)
      point[i] = 0;
   centreToFeet = -3.15f;
   antennaAngle = 0.0f;
}

void Robot::createCircle(float radius, int x, int y){
    float x1,y1,x2,y2;
    float angle;
    x1 =x,y1=y;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x1,y1,0.0f);
    for (angle=1.0f;angle<3*3.14159;angle+=0.2)
    {
        x2 = x1+sin(angle)*radius;
        y2 = y1+cos(angle)*radius;
        glVertex3f(x2,y2, 0.0f);
    }
    glEnd();
    //thanks to https://www.codeproject.com/Questions/64657/how-to-draw-a-filled-circle-in-opengl
  }
  /**
  */
void Robot::createTriangle(float width, float height){
    glBegin(GL_TRIANGLES);
      glVertex3f(0.0f, (height/2), 0.0f);
      glVertex3f((width/2), -(height/2), 0.0f);
      glVertex3f(-(width/2), -(height/2), 0.0f);
    glEnd();
  }
void Robot::createRectangle(float width, float height){
    glBegin(GL_QUADS);
      glVertex3f((width/2), -(height/2), 0.0f);
      glVertex3f(-(width/2), -(height/2), 0.0f);
      glVertex3f(-(width/2), (height/2), 0.0f);
      glVertex3f((width/2), (height/2), 0.0f);
    glEnd();
  }
  /**
  */
void Robot::createBox(float width, float height, float depth){
     glBegin(GL_QUADS);
        // Far face.
        glNormal3f( 0.0f, 0.0f, -1.0f);

      glVertex3f(-(width/2), -(height/2.0f), -(depth/2));
      glVertex3f(-(width/2),  (height/2.0f), -(depth/2));
      glVertex3f((width/2),  (height/2.0f), -(depth/2));
      glVertex3f((width/2), -(height/2.0f), -(depth/2));

        // Right face.
        glNormal3f(1.0f, 0.0f, 0.0f);

      glVertex3f((width/2), -(height/2.0f), -(depth/2));
      glVertex3f((width/2),  (height/2.0f), -(depth/2));
      glVertex3f((width/2),  (height/2.0f),  (depth/2));
      glVertex3f((width/2), -(height/2.0f),  (depth/2));

        // Front face; offset.
        glNormal3f( 0.0f, 0.0f, 1.0f);

      glVertex3f(-(width/2), -(height/2.0f),  (depth/2));
      glVertex3f((width/2), -(height/2.0f),  (depth/2));
      glVertex3f((width/2),  (height/2.0f),  (depth/2));
      glVertex3f(-(width/2),  (height/2.0f),  (depth/2));


        // Left Face; offset.
        glNormal3f(-1.0f, 0.0f, 0.0f);

      glVertex3f(-(width/2), -(height/2.0f), -(depth/2));
      glVertex3f(-(width/2), -(height/2.0f),  (depth/2));
      glVertex3f(-(width/2),  (height/2.0f),  (depth/2));
      glVertex3f(-(width/2),  (height/2.0f), -(depth/2));


        // Top Face; offset.
        glNormal3f(0.0f, 1.0f, 0.0f);

      glVertex3f((width/2), (height/2.0f), -(depth/2));
      glVertex3f((width/2),  (height/2.0f),  (depth/2));
      glVertex3f(-(width/2), (height/2.0f),  (depth/2));
      glVertex3f(-(width/2),  (height/2.0f), -(depth/2));

        // Bottom Face; offset.
        glNormal3f(0.0f, -1.0f, 0.0f);

      glVertex3f((width/2), -(height/2.0f), -(depth/2));
      glVertex3f((width/2),  -(height/2.0f),  (depth/2));
      glVertex3f(-(width/2), -(height/2.0f),  (depth/2));
      glVertex3f(-(width/2), -(height/2.0f), -(depth/2));

        // All polygons have been drawn.
    glEnd();
  }

void Robot::draw(float x, float y, float z){
    GLUquadricObj *neck = gluNewQuadric();
    GLUquadricObj *antenna = gluNewQuadric();


    glTranslatef(x, 0.4f+y, z);
    glRotatef(90.0f*facing, 0, 1.0, 0);
    if(head == 0){
       glRotatef(0.0f, 0.0f, 1.0f, 0.0f); //Centre head
    }
    else if(head == 1){
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //Left head
    }else if(head == 2){
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); //Right head
    }
    else{
       glRotatef(0.0f, 0.0f, 1.0f, 0.0f); //Centre default, shouldn't happen
    }

    glColor3f( 0.3f, 0.3f, 0.3f );
    createBox(0.8f,0.8f,0.8f); //head center


    glTranslatef(-0.2f, 0.0f, 0.42f);
    glColor3f( 0.8f, 0.8f, 0.8f);
    createCircle(0.1f, 0.0f, 0.0f);
    glColor3f( 0.8f, 0.1f, 0.1f);
    glTranslatef(0.0f, 0.0f, 0.02f);
    createCircle(0.08f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -0.02f);
    glTranslatef(0.2f, 0.0f, -0.42f);
    glTranslatef(0.2f, 0.0f, 0.42f);
    glColor3f( 0.8f, 0.8f, 0.8f);
    createCircle(0.1f, 0.0f, 0.0f);
    glColor3f( 0.8f, 0.1f, 0.1f);
    glTranslatef(0.0f, 0.0f, 0.02f);
    createCircle(0.08f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -0.02f);
    glTranslatef(-0.2f, 0.0f, -0.42f);

    glTranslatef(0.0f, 0.6f, 0.0f); // to antena center
    glColor3f( 0.4f, 0.4f, 0.4f );
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(antenna,0.1f,0.1f,0.4f,15,15);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.1f, 0.0f);
    glRotatef(antennaAngle, 0.0f, 1.0f, 0.0f);
    glColor3f( 0.7f, 0.7f, 0.7f );
    createBox(0.2f,0.2f,0.2f);
    glRotatef(-antennaAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -0.1f, 0.0f);

    glTranslatef(0, y-1.0f, 0);
    //glRotatef(180.0f, 0.0f, 1.0f, 0.0f);// Back Body
    glColor3f( 0.6f, 0.6f, 0.6f );
    /*  glTranslatef(0.0f, -0.15f, 0.0f); // to neck from antena center*/
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(neck,0.3f,0.3f,0.3f,15,15);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    glColor3f( 0.3f, 0.3f, 0.3f );
    glTranslatef(0.0f, -1.15f, 0.0f);
    createBox(1.0f,2.0f,1.0f);
    glTranslatef(0.0f, 0.0f, 0.52f);
    glColor3f( 0.6f, 0.6f, 0.6f );
    createRectangle(0.7f, 1.7f);
    glTranslatef(0.0f, 0.0f, -0.52f);
    glTranslatef(0.0f, 0.3f, -0.52f);
    createTriangle(0.5f, 0.5f);
    glTranslatef(0.0f, -0.6f, 0.0f);
    createTriangle(0.5f, 0.5f);

    glRotatef(-90.0f*facing, 0, 1.0, 0);
}

void Robot::move(){
    if(facing == 0.0f && point[2] < 999){
      point[2] += 1;
    } else if(facing == 1.0f && point[0] < 4){
      point[0] += 1;
    } else if(facing == -1.0f && point[0] > -999){
      point[0] -= 1;
    } else if((facing == 2.0f || facing == -2.0f) && point[2] > -4){
      point[2] -= 1;
    }
    antennaAngle += 10.0f;
    if(antennaAngle > 360.0f){
      antennaAngle = 0.0f;
    }
}

void Robot::right(){
  facing -= 1.0f;
  if(facing < -2.0f){
    facing = -(float)(((int)facing) % 2);
  }
}
void Robot::left(){
  facing += 1.0f;
  if(facing > 2.0f){
    facing = -(float)(((int)facing) % 2);
  }
}
