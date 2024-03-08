
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cmath>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif
#include <stdlib.h>
#include <iostream>
#include <cmath>

using namespace std;
GLint win_width = 500,
      win_hight = 500;
GLdouble PI = 3.14159265359;

float transValueX;
float transValueY;
float transValueZ;

//float near;
//float far;
float scaleValue;

float ghost1;
float ghost2;
float ghost3;
float ghost4;

bool start = true ;
bool HH = false ;
bool ABT = false;


//MOUSE CLICK

GLint flag;

bool Gem1_flag = false ;
bool Gem2_flag = false ;
bool Gem3_flag = false ;

bool key1_flag = false ;
bool key2_flag = false ;
bool key3_flag = false ;


// buffers
GLuint myTexture1;


char image1Path []="/Users/Moody/Documents/CG-lab/CG-project/floor-texture-2-.bmp"; // walls and floor

//------------------------------------------------
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(
                    x + (radius * cos(i *  twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_LINE_LOOP);
        for(i = 0; i <= lineAmount;i++) {
            glVertex2f(
                x + (radius * cos(i *  twicePi / lineAmount)),
                y + (radius* sin(i * twicePi / lineAmount))
            );
        }
    glEnd();
}

void drawFilledCirclehalf(GLfloat x, GLfloat y, GLfloat radius) {

    int i;
    int triangleAmount = 50; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = -1.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawHollowCircleHalf(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int lineAmount = 50; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 1.0f * PI;

    glBegin(GL_LINE_LOOP);
    for (i = 0; i <= lineAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / lineAmount)),
            y + (radius * sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}
//HH ess methods
void drawFilledCircleghost(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawFilledCirclehalfghost(GLfloat x, GLfloat y, GLfloat radius) {

    int i;
    int triangleAmount = 50; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = -1.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawFilledOval(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (0.2 * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawNetCircle(GLfloat x, GLfloat y, GLfloat radius){
    int i;
   // int lineAmount = 100;
    int lineAmount = 8; //# of triangles used to draw circle
    
    //GLfloat radius = 0.8f; //radius
   GLfloat twicePi = 2.0f*PI ;
    
    
    glBegin(GL_LINE_LOOP);
        for(i = 0; i <= lineAmount;i++) {
            glVertex2f(
                x + (radius * cos(i *  twicePi / lineAmount)),
                y + (radius* sin(i * twicePi / lineAmount))
            );
        }
    glEnd();
}

void drawStrokeText(const char* text, int length, int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    double* matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 600, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

//------------------------Exit Page------------------------
//------------------------Alli Baba's Treasuer------------------------
void caveBG()
{
    //cave
    glColor3f(0.45, 0.41, 0.36);
    drawFilledCircle(0.0,-0.5,1.4);
    
    glColor3f(0.50, 0.46, 0.41);
    drawFilledCircle(0.0,-0.5,1.2);
    
    glColor3f(0.55, 0.51, 0.46);
    drawFilledCircle(0.0,-0.5,1.0);
    
    //sky
    glColor3f(0.15, 0.17, 0.29);
    drawFilledCircle(0.0,-0.5,0.9);
    
    //moon
    glColor3f(0.89, 0.79, 0.4);
    drawFilledCircle(0.0,0.0,0.2);
    
    glColor3f(0.15, 0.17, 0.29);
    drawFilledCircle(-0.1,0.0,0.18);
   
    //cloude center
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(-0.3, 0.18 ,0.06);
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(-0.39, 0.2 ,0.09);
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(-0.48, 0.17 ,0.05);
    
    //cloude left yp
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(-0.07, -0.209 ,0.06);
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(-0.14, -0.18 ,0.09);
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(-0.23, -0.2099 ,0.05);
    
    //cloude down right
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(0.5, -0.32 ,0.06); //r
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(0.4, -0.29 ,0.09); //c
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(0.31, -0.32 ,0.05); //l
    
    //cloude down left
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(-0.5, -0.43 ,0.06); //r
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(-0.4, -0.43 ,0.09); //c
    glColor3f(0.9, 0.9, 0.9);
    drawFilledCircle(-0.31, -0.43 ,0.05); //l
    
    //side walls
    glColor3f(0.50, 0.46, 0.41);
    drawFilledCircle(-2.3,-0.9,1.7); //left
    
    glColor3f(0.50, 0.46, 0.41);
    drawFilledCircle(2.3,-0.7,1.7); //right
    
    //ground
   glRectf(-1.0, -1.0, 1.0, -0.7);

    //rock left back
    glColor3f(0.4, 0.36, 0.31);
    drawFilledCirclehalf(-1.0, -0.95, -0.8);
    //rock left front
    glColor3f(0.35, 0.31, 0.25);
    drawFilledCirclehalf(-0.5, -0.96, -0.4);
    //rock right back
    glColor3f(0.4, 0.36, 0.31);
    drawFilledCirclehalf(0.5, -0.8, -0.2);
    //rock right front
    glColor3f(0.35, 0.31, 0.25);
    drawFilledCirclehalf(0.3, -0.82, -0.1);
    
    }
void stones(){
    //back
    glColor3f(0.35, 0.31, 0.25);
    drawFilledCirclehalf(0.87, -0.88, -0.1);
    //front
    glColor3f(0.45, 0.41, 0.35);
    drawFilledCirclehalf(0.8, -0.88, -0.06);
}


void tourch(){
    // the lit - quads
        
        glBegin(GL_QUADS);
        glColor4f(0.99609375f, 0.64453125f, 0.0f,1.0f);
        glVertex2f(-0.1f,  0.3f);
        glVertex2f(-0.1f,  0.1f);//left edges
        
        glVertex2f( 0.1f,  0.1f);
        glVertex2f( 0.1f, 0.3f);//right edges
        
        glEnd();
 
        //dicoration
        glLineWidth(50.0f);
           glBegin(GL_LINES);
      //  glColor3f(0.43248f, 0.257238f, 0.15478f);
        glColor3f(0.4f, 0.35f, 0.3f);
           glVertex2f(0.12f, 0.1058f);
           glVertex2f(-0.12f,0.1058f);
        glEnd();
        
        // stick
        glBegin(GL_QUADS);
        glColor3f(0.43248f, 0.257238f, 0.15478f);
        glVertex2f(-0.1f, -0.7f);
        glVertex2f( 0.1f, -0.7f);//down edges
        
        glVertex2f( 0.1f,  0.1f);
        glVertex2f(-0.1f,  0.1f);// upper edges
        glEnd();
        
    //light effict
    glColor4f(0.99609375, 0.64453125, 0.2, 0.17);
    drawFilledCircle(-0.02, 0.3, 0.3);
       
}

void SpiderLeg(float xOffset, float yOffset, float angle) {
    glPushMatrix();
    glTranslatef(xOffset, yOffset, 0.0);
    glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate the leg

    glBegin(GL_QUADS); // THE LEG
    glVertex2f(-0.02, 0.0);
    glVertex2f(-0.02, -0.35);
    glVertex2f(0.02, -0.35);
    glVertex2f(0.02, 0.0);
    glEnd();

    glPopMatrix();
}


void Spider()
{
    // RIGHT SIDE
    // UPPER LEG
    glColor3f(0.14f, 0.14f, 0.14f);
    SpiderLeg(0.25, -0.1, 35.0);
    SpiderLeg(0.36, 0.05, 55.0);
    SpiderLeg(0.39, 0.2, 100.0);
    SpiderLeg(0.35, 0.36, 130.0);
    
    // LOWER LEG
    SpiderLeg(0.45, -0.365, -30.0);
    SpiderLeg(0.64, -0.14, -5.0);
    SpiderLeg(0.73, 0.28, 25.0);
    SpiderLeg(0.39, 0.836, 40.0);
    
    // LEFT SIDE
    // UPPER LEG
    SpiderLeg(-0.25, -0.1, -35.0);
    SpiderLeg(-0.36, 0.05, -55.0);
    SpiderLeg(-0.39, 0.2, -100.0);
    SpiderLeg(-0.35, 0.36, -130.0);
    
    // LOWER LEG
    SpiderLeg(-0.45, -0.365, 30.0);
    SpiderLeg(-0.64, -0.14, 5.0);
    SpiderLeg(-0.73, 0.28, -25.0);
    SpiderLeg(-0.39, 0.836, -40.0);
    
    glColor3f(0.14f, 0.14f, 0.14f);
    drawFilledCircle(0,0.2,.40);  // SPIDER BODY
    drawFilledCircle(0,-0.2,.25); // SPIDER FACE
    
    // SCLERA
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.08,-0.25,.06);  // LEFT
    drawFilledCircle(0.08,-0.25,.06);   // RIGHT
    
    // PUPIL
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.06,-0.25,.03);  // LEFT
    drawFilledCircle(0.1,-0.25,.03);    // RIGHT
    
    glLineWidth(1.0f);
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_LINE_LOOP); // R-center
    glVertex2f(0.0, 11.0);
    glVertex2f(0.0, 0.6);
    glEnd();
    
}

void Gem1()
{
    // THE CENTER SQUARE
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.2,0.2);
    glVertex2f(0.2,0.2);
    glVertex2f(0.2,-0.2);
    glVertex2f(-0.2,-0.2);
    glEnd();
    
    glColor3f(0.7f, 0.0f, 0.1f);
    
    // THE UPPER RECTANGULAR
    glBegin(GL_QUADS);
    glVertex2f(-0.2,0.4);
    glVertex2f(0.2,0.4);
    glVertex2f(0.2,0.2);
    glVertex2f(-0.2,0.2);
    glEnd();
    
    // THE RIGHT RECTANGULAR
    glBegin(GL_QUADS);
    glVertex2f(0.2,0.2);
    glVertex2f(0.4,0.2);
    glVertex2f(0.4,-0.2);
    glVertex2f(0.2,-0.2);
    glEnd();
    
    // THE LOWER RECTANGULAR
    glBegin(GL_QUADS);
    glVertex2f(-0.2,-0.2);
    glVertex2f(0.2,-0.2);
    glVertex2f(0.2,-0.4);
    glVertex2f(-0.2,-0.4);
    glEnd();
    
    // THE LEFT RECTANGULAR
    glBegin(GL_QUADS);
    glVertex2f(-0.4,0.2);
    glVertex2f(-0.2,0.2);
    glVertex2f(-0.2,-0.2);
    glVertex2f(-0.4,-0.2);
    glEnd();
    
    
    glColor3f(0.9f, 0.0f, 0.0f);
    
    // THE UPPER LEFT TRIANGLE
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2,0.4);
    glVertex2f(-0.2,0.2);
    glVertex2f(-0.4,0.2);
    glEnd();
    
    // THE UPPER RIGHT TRIANGLE
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2,0.4);
    glVertex2f(0.4,0.2);
    glVertex2f(0.2,0.2);
    glEnd();
    
    // THE LOWER RIGHT TRIANGLE
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2,-0.2);
    glVertex2f(0.4,-0.2);
    glVertex2f(0.2,-0.4);
    glEnd();
    
    // THE LOWER LEFT TRIANGLE
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.4,-0.2);
    glVertex2f(-0.2,-0.2);
    glVertex2f(-0.2,-0.4);
    glEnd();

}
//
void Gem1M()
{
    // THE CENTER SQUARE
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(-0.2,0.2);
    glVertex2f(0.2,0.2);
    glVertex2f(0.2,-0.2);
    glVertex2f(-0.2,-0.2);
    glEnd();
    
    glColor3f(0.6f, 0.4f, 0.2f);
    
    // THE UPPER RECTANGULAR
    glBegin(GL_QUADS);
    glVertex2f(-0.2,0.4);
    glVertex2f(0.2,0.4);
    glVertex2f(0.2,0.2);
    glVertex2f(-0.2,0.2);
    glEnd();
    
    // THE RIGHT RECTANGULAR
    glBegin(GL_QUADS);
    glVertex2f(0.2,0.2);
    glVertex2f(0.4,0.2);
    glVertex2f(0.4,-0.2);
    glVertex2f(0.2,-0.2);
    glEnd();
    
    // THE LOWER RECTANGULAR
    glBegin(GL_QUADS);
    glVertex2f(-0.2,-0.2);
    glVertex2f(0.2,-0.2);
    glVertex2f(0.2,-0.4);
    glVertex2f(-0.2,-0.4);
    glEnd();
    
    // THE LEFT RECTANGULAR
    glBegin(GL_QUADS);
    glVertex2f(-0.4,0.2);
    glVertex2f(-0.2,0.2);
    glVertex2f(-0.2,-0.2);
    glVertex2f(-0.4,-0.2);
    glEnd();
  
    glColor3f(0.6f, 0.4f, 0.2f);
    
    // THE UPPER LEFT TRIANGLE
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2,0.4);
    glVertex2f(-0.2,0.2);
    glVertex2f(-0.4,0.2);
    glEnd();
    
    // THE UPPER RIGHT TRIANGLE
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2,0.4);
    glVertex2f(0.4,0.2);
    glVertex2f(0.2,0.2);
    glEnd();
    
    // THE LOWER RIGHT TRIANGLE
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2,-0.2);
    glVertex2f(0.4,-0.2);
    glVertex2f(0.2,-0.4);
    glEnd();
    
    // THE LOWER LEFT TRIANGLE
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.4,-0.2);
    glVertex2f(-0.2,-0.2);
    glVertex2f(-0.2,-0.4);
    glEnd();
}

void Gem2()
{
    //T HE M DIAMOND
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.9f, 0.02f);
    glVertex2f(0.0,0.4);
    glVertex2f(0.2,0.0);
    glVertex2f(0.0,-0.4);
    glVertex2f(-0.2,0.0);
    glEnd();
    
    // THE UPPER RIGHT QUAD
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(0.0,0.6);
    glVertex2f(0.3,0.0);
    glVertex2f(0.2,0.0);
    glVertex2f(0.0,0.4);
    glEnd();
    
    // THE LOWER RIGHT QUAD
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.7f, 0.0f);
    glVertex2f(0.2,0.0);
    glVertex2f(0.3,0.0);
    glVertex2f(0.0,-0.6);
    glVertex2f(0.0,-0.4);
    glEnd();
    
    // THE LOWER LEFT QUAD
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(-0.3,0.0);
    glVertex2f(-0.2,0.0);
    glVertex2f(0.0,-0.4);
    glVertex2f(0.0,-0.6);
    glEnd();
    
    // THE UPPER LEFT QUAD
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(0.0,0.6);
    glVertex2f(0.0,0.4);
    glVertex2f(-0.2,0.0);
    glVertex2f(-0.3,0.0);
    glEnd();
}
//
void Gem2M()
{
    //T HE M DIAMOND
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(0.0,0.4);
    glVertex2f(0.2,0.0);
    glVertex2f(0.0,-0.4);
    glVertex2f(-0.2,0.0);
    glEnd();
    
    // THE UPPER RIGHT QUAD
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(0.0,0.6);
    glVertex2f(0.3,0.0);
    glVertex2f(0.2,0.0);
    glVertex2f(0.0,0.4);
    glEnd();
    
    // THE LOWER RIGHT QUAD
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(0.2,0.0);
    glVertex2f(0.3,0.0);
    glVertex2f(0.0,-0.6);
    glVertex2f(0.0,-0.4);
    glEnd();
    
    // THE LOWER LEFT QUAD
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(-0.3,0.0);
    glVertex2f(-0.2,0.0);
    glVertex2f(0.0,-0.4);
    glVertex2f(0.0,-0.6);
    glEnd();
    
    // THE UPPER LEFT QUAD
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(0.0,0.6);
    glVertex2f(0.0,0.4);
    glVertex2f(-0.2,0.0);
    glVertex2f(-0.3,0.0);
    glEnd();
}

void Gem3()
{
    //THE UPPER LEFT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.8f, 1.0f);
    glVertex2f(-0.35,0.2);
    glVertex2f(0.0,0.2);
    glVertex2f(-0.2,0.0);
    glEnd();
    
    //THE UPPER RIGHT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.8f, 1.0f);
    glVertex2f(0.0,0.2);
    glVertex2f(0.35,0.2);
    glVertex2f(0.2,0.0);
    glEnd();
    
    // THE MID LEFT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.7f, 1.0f);
    glVertex2f(-0.35,0.2);
    glVertex2f(-0.2,0.0);
    glVertex2f(-0.5,0.0);
    glEnd();
    
    // THE MID MIDDLE TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.6f, 1.0f);
    glVertex2f(0.0,0.2);
    glVertex2f(0.2,0.0);
    glVertex2f(-0.2,0.0);
    glEnd();
    
    // THE MID RIGHT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.7f, 1.0f);
    glVertex2f(0.35,0.2);
    glVertex2f(0.5,0.0);
    glVertex2f(0.2,0.0);
    glEnd();
    
    // THE LOWER LEFT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.8f, 1.0f);
    glVertex2f(-0.5,0.0);
    glVertex2f(-0.2,0.0);
    glVertex2f(0.0,-0.6);
    glEnd();
    
    // THE LOWER MIDDLE TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.7f, 1.0f);
    glVertex2f(-0.2,0.0);
    glVertex2f(0.2,0.0);
    glVertex2f(0.0,-0.6);
    glEnd();
    
    // THE LOWER RIGHT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.6f, 1.0f);
    glVertex2f(0.2,0.0);
    glVertex2f(0.5,0.0);
    glVertex2f(0.0,-0.6);
    glEnd();
}
//
void Gem3M()
{
    //THE UPPER LEFT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(-0.35,0.2);
    glVertex2f(0.0,0.2);
    glVertex2f(-0.2,0.0);
    glEnd();
    
    //THE UPPER RIGHT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(0.0,0.2);
    glVertex2f(0.35,0.2);
    glVertex2f(0.2,0.0);
    glEnd();
    
    // THE MID LEFT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(-0.35,0.2);
    glVertex2f(-0.2,0.0);
    glVertex2f(-0.5,0.0);
    glEnd();
    
    // THE MID MIDDLE TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(0.0,0.2);
    glVertex2f(0.2,0.0);
    glVertex2f(-0.2,0.0);
    glEnd();
    
    // THE MID RIGHT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(0.35,0.2);
    glVertex2f(0.5,0.0);
    glVertex2f(0.2,0.0);
    glEnd();
    
    // THE LOWER LEFT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(-0.5,0.0);
    glVertex2f(-0.2,0.0);
    glVertex2f(0.0,-0.6);
    glEnd();
    
    // THE LOWER MIDDLE TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(-0.2,0.0);
    glVertex2f(0.2,0.0);
    glVertex2f(0.0,-0.6);
    glEnd();
    
    // THE LOWER RIGHT TRIANGLE
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(0.2,0.0);
    glVertex2f(0.5,0.0);
    glVertex2f(0.0,-0.6);
    glEnd();
}

void treasureChest() {

    //the body(bigger rect)
    glColor4f(0.4f, 0.2f, 0.0f, 1.0f); //0.4/0.2/0
    glRectf(0.5 ,0.2, -0.5 ,-0.2);

    //the cover(half circle)
    glColor4f(0.4f, 0.2f, 0.0f, 1.0f);
    drawFilledCirclehalf(0.0f,0.27f,-0.5);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    drawHollowCircleHalf(0.0f, 0.27f, 0.5);

    //wood lines for the cover(the half circle)starting at the bottom going up to the top
         glBegin(GL_LINES);

    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glVertex2f(0.46, 0.47);//first line
    glVertex2f(-0.45, 0.47);

    glVertex2f(0.38, 0.59);//second line
    glVertex2f(-0.38, 0.59);
  
    glVertex2f(0.26, 0.70);//third line
    glVertex2f(-0.26, 0.70);

           glEnd();

    //wood lines for the body, starting at the top going down to the bottom
        glBegin(GL_LINES);

     glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
     glVertex2f(0.5, 0.1);//first line
     glVertex2f(-0.5, 0.1);

     glVertex2f(0.5, 0.0);//second line
     glVertex2f(-0.5, 0.0);


     glVertex2f(0.5, -0.1);//third line
     glVertex2f(-0.5, -0.1);
        glEnd();
    
    //golden horizentl belt
    glColor4f(1.0f, 0.9f, 0.1f, 1.0f);
  
    glRectf(0.5, 0.35, -0.5, 0.2);
     
    //for the body rect frame (going under the belt, order of layers is important):
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);

    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glVertex2f(-0.5, 0.2);//top left
    glVertex2f(0.5, 0.2);//top right
    glVertex2f(0.5, -0.2);//bottom right
    glVertex2f(-0.5, -0.2);//bottom left
    glEnd();

    //frame for the horizental belt:
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.0f, 0.0f, 0.0f,1.0f);
    glVertex2f(-0.5, 0.35);//top left
    glVertex2f(0.5, 0.35);//top right
    glVertex2f(0.5, 0.2);//bottom right
    glVertex2f(-0.5, 0.2);//bottom left
    glEnd();

    //golden vertical belt
    glColor4f(1.0f, 0.9f, 0.1f, 1.0f);
    glRectf(0.07, 0.767, -0.07, 0.09);

    // vertical belt frame:
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glVertex2f(-0.07, 0.767);//top left
    glVertex2f(0.07, 0.767);//top right
    glVertex2f(0.07, 0.09);//bottom right
    glVertex2f(-0.07, 0.09);//bottom left
    glEnd();
    //lock golden circle
    glColor4f(1.0f, 0.9f, 0.1f, 1.0);
    drawFilledCircle(0.0f, 0.07f, 0.1f);

    //golden circle frame
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    drawHollowCircle(0.0f, 0.07f, 0.1f);

    //black key circle
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    drawFilledCircle(0.0f, 0.09f, 0.03f);

    //black key triangle
    glBegin(GL_TRIANGLES);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glVertex2f(0.0,0.09);
    glVertex2f(-0.02, 0.0);
    glVertex2f(0.02, 0.0);
    glEnd();
}

void coin(){
    
      glColor3f(1.0f, 0.84f, 0.0f);
      drawFilledCircle(0, 0, .25);
      glColor3f(1.0f, 0.7f, 0.1f);
      drawHollowCircle(0, 0, .20);
      glColor3f(1.0f, 0.7f, 0.1f);
      drawFilledCircle(0, 0, .20);
}

void lock(){
    glColor3f(0.6f, 0.4f, 0.2f);
    glRectf(-0.49, 0.9, 0.49, 0.7);
    
    glColor3f(0.8f, 0.7f, 0.3f);
    glRectf(-0.4, 0.9, 0.4, 0.7);
    
    //Gem1 scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.15, 0.15, 0.0);
    glTranslatef(-1.5, 5.3, 0.0);
    Gem1M();
    glPopMatrix();
    
    //Gem2 scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.15, 0.15, 0.0);
    glTranslatef(0.0, 5.3, 0.0);
    Gem2M();
    glPopMatrix();
    
    //Gem3 scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.15, 0.15, 0.0);
    glTranslatef(1.5, 5.48, 0.0);
    Gem3M();
    glPopMatrix();
}

void winMsgAB() {
    
    glColor3f(0.0f, 0.0f, 0.0f);
    std::string text;
    text = "GOOD JOOB FINDIG THE GEMS BEFORE THE PIRATES!";
    drawStrokeText(text.data(), static_cast<int>(text.size()), 50, 295);

}


//------------------------Alli Baba's Treasuer Display------------------------
void alliBabaDisplay()
{
    glClearColor(0.32, 0.29, 0.26, 0.1); // Set background for allibaba's
    glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glEnable(GL_BLEND);
    
    caveBG();
    
    //tourch-R scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.3, 0.3, 0.0);
    glTranslatef(1.5, -2.0, 0.0);
    tourch();
    glPopMatrix();
 
    //Gem1 scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.08, 0.08, 0.0);
    glTranslatef(-11.4, -1.4, 0.0);
    Gem1();
    glPopMatrix();
    
    //Gem2 scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.1, 0.1, 0.0);
    glTranslatef(9.0, -8.0, 0.0);
    Gem2();
    glPopMatrix();
    
    stones();
    
    //Gem3 scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.1, 0.1, 0.0);
    glTranslatef(-9.2, -9.0, 0.0);
    Gem3();
    glPopMatrix();
    
    //tourch-L scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.3, 0.3, 0.0);
    glTranslatef(-3.0, -2.5, 0.0);
    tourch();
    glPopMatrix();
    
    //Spider-L scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.1, 0.1, 0.0);
    glTranslatef(-9.0, -1.0, 0.0);
    Spider();
    glPopMatrix();
    
    //Spider-R scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.06, 0.06, 0.0);
    glTranslatef(13.0, -4.5, 0.0);
    Spider();
    glPopMatrix();

    // treasureChest scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.5, 0.5, 0.0);
    glTranslatef(0.1, -1.8, 0.0);
    treasureChest();
    glPopMatrix();

    // coin scale and translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.2, 0.18, 0.0);
    glTranslatef(1.7, -5.3, 0.0);
    coin();
    glPopMatrix();
    //
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.2, 0.18, 0.0);
    glTranslatef(1.4, -5.6, 0.0);
    coin();
    glPopMatrix();
    //
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.2, 0.18, 0.0);
    glTranslatef(1.7, -5.5, 0.0);
    coin();
    glPopMatrix();
    //
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.2, 0.18, 0.0);
    glTranslatef(2.1, -5.5, 0.0);
    coin();
    glPopMatrix();
    //
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.2, 0.18, 0.0);
    glTranslatef(2.4, -5.6, 0.0);
    coin();
    glPopMatrix();

    lock();
    
    ///////////////////////////////////////////////////////////////////////////////////
    //FoundKeys matrix Gem 1
    if (Gem1_flag) {
            glPushMatrix();
            glScalef(0.15, 0.15, 0.0);
            glTranslatef(-1.5, 5.3, 0.0);
            Gem1();
            glPopMatrix();
        }
    
    //FoundKeys matrix Gem 2
    if (Gem2_flag) {
           glPushMatrix();
           glScalef(0.15, 0.15, 0.0);
           glTranslatef(0.0, 5.3, 0.0);
           Gem2();
           glPopMatrix();
       }
    
    //FoundKeys matrix Gem 3
    if (Gem3_flag) { //FoundKeys matrix key 3
           glPushMatrix();
           glScalef(0.15, 0.15, 0.0);
           glTranslatef(1.5, 5.48, 0.0);
           Gem3();
           glPopMatrix();
       }
    
    //print text
    if (Gem1_flag && Gem2_flag && Gem3_flag){
           glPushMatrix();
           glColor4f(0.9f, 0.9f, 0.9f, 0.9);
           glRectf(0.80, 0.1, -0.87, -0.1);
           winMsgAB();
           glPopMatrix();
       }
    ///////////////////////////////////////////////////////////////////////////////////

    glFlush();
    glutSwapBuffers();
}

//------------------------Hunted House------------------------
void  Key1()
{
    //smaller blade
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.80f, 0.030f);//top left
    glVertex2f(-0.55f, 0.030f);//top right
    glVertex2f(-0.55f, -0.060f);//bottom right
    glVertex2f(-0.80f, -0.060f);//bottom left
    glEnd();

    //smaller blade frame
    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.80f, 0.030f);//top left
    glVertex2f(-0.55f, 0.030f);//top right
    glVertex2f(-0.55f, -0.060f);//bottom right
    glVertex2f(-0.80f, -0.060f);//bottom left

    glEnd();


    //the blade
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.85f, 0.030f);//top left
    glVertex2f(-0.15f, 0.030f);//top right
    glVertex2f(-0.15f, -0.030f);//bottom right
    glVertex2f(-0.85f, -0.030f);//bottom left
    glEnd();

    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.85f, 0.030f);//top left
    glVertex2f(-0.15f, 0.030f);//top right
    glVertex2f(-0.15f, -0.030f);//bottom right
    glVertex2f(-0.85f, -0.030f);//bottom left

    glEnd();
    
    //bitting cuts (1) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.65f, -0.060f);//top left
    glVertex2f(-0.60f, -0.060); //top right
    glVertex2f(-0.60f, -0.17f);//bottom right
    glVertex2f(-0.65f, -0.17f);//bottom left
    glEnd();

    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.65f, -0.060f);//top left
    glVertex2f(-0.60f, -0.060); //top right
    glVertex2f(-0.60f, -0.17f);//bottom right
    glVertex2f(-0.65f, -0.17f);//bottom left

    glEnd();


    //bitting cuts (2) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.75f, -0.060f);//top left
    glVertex2f(-0.70f, -0.060); //top right
    glVertex2f(-0.70f, -0.17f);//bottom right
    glVertex2f(-0.75f, -0.17f);//bottom left
    glEnd();

    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.75f, -0.060f);//top left
    glVertex2f(-0.70f, -0.060); //top right
    glVertex2f(-0.70f, -0.17f);//bottom right
    glVertex2f(-0.75f, -0.17f);//bottom left

    glEnd();

    //the key head

    glColor4f(0.4f, 0.4f, 0.4f, 1.0f); //outer circle frame
    drawFilledCircle(0.0f, 0.0f, 0.22f);

    glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //outer circle
    drawFilledCircle(0.0f, 0.0f, 0.2f);




    glColor4f(0.6f, 0.6f, 0.6f, 1.f);//inner circle frame
    drawFilledCircle(0.0f, 0.0f, 0.16);

    glColor4f(1.0f, 1.0f, 1.0f, 1.f);//inner circle
    drawFilledCircle(0.0f, 0.0f, 0.14f);

}


void Key1_Lock() {

    //smaller blade
    glBegin(GL_QUADS);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.80f, 0.030f);//top left
    glVertex2f(-0.55f, 0.030f);//top right
    glVertex2f(-0.55f, -0.060f);//bottom right
    glVertex2f(-0.80f, -0.060f);//bottom left
    glEnd();

    //smaller blade frame
    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.80f, 0.030f);//top left
    glVertex2f(-0.55f, 0.030f);//top right
    glVertex2f(-0.55f, -0.060f);//bottom right
    glVertex2f(-0.80f, -0.060f);//bottom left

    glEnd();


    //the blade
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.85f, 0.030f);//top left
    glVertex2f(-0.15f, 0.030f);//top right
    glVertex2f(-0.15f, -0.030f);//bottom right
    glVertex2f(-0.85f, -0.030f);//bottom left
    glEnd();

    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.85f, 0.030f);//top left
    glVertex2f(-0.15f, 0.030f);//top right
    glVertex2f(-0.15f, -0.030f);//bottom right
    glVertex2f(-0.85f, -0.030f);//bottom left

    glEnd();

    //bitting cuts (1) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.65f, -0.060f);//top left
    glVertex2f(-0.60f, -0.060); //top right
    glVertex2f(-0.60f, -0.17f);//bottom right
    glVertex2f(-0.65f, -0.17f);//bottom left
    glEnd();

    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.65f, -0.060f);//top left
    glVertex2f(-0.60f, -0.060); //top right
    glVertex2f(-0.60f, -0.17f);//bottom right
    glVertex2f(-0.65f, -0.17f);//bottom left

    glEnd();


    //bitting cuts (2) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.75f, -0.060f);//top left
    glVertex2f(-0.70f, -0.060); //top right
    glVertex2f(-0.70f, -0.17f);//bottom right
    glVertex2f(-0.75f, -0.17f);//bottom left
    glEnd();

    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.75f, -0.060f);//top left
    glVertex2f(-0.70f, -0.060); //top right
    glVertex2f(-0.70f, -0.17f);//bottom right
    glVertex2f(-0.75f, -0.17f);//bottom left

    glEnd();

    //the key head


    glColor4f(0.2f, 0.2f, 0.2f, 1.0f); //outer circle frame
    drawFilledCircle(0.0f, 0.0f, 0.22f);

    glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //outer circle
    drawFilledCircle(0.0f, 0.0f, 0.2f);




    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);//inner circle frame
    drawFilledCircle(0.0f, 0.0f, 0.16);

    glColor4f(0.2f, 0.2f, 0.2f, 1.0f); //inner circle
    drawFilledCircle(0.0f, 0.0f, 0.14f);


}

void key2()
{

    //bitting cuts (1) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.60f, -0.060f);//top left
    glVertex2f(-0.57f, -0.060); //top right
    glVertex2f(-0.57f, -0.17f);//bottom right
    glVertex2f(-0.60f, -0.17f);//bottom left
    glEnd();


    //bitting cuts frame (1)
    glLineWidth(3.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.60f, -0.060f);//top left
    glVertex2f(-0.57f, -0.060); //top right
    glVertex2f(-0.57f, -0.17f);//bottom right
    glVertex2f(-0.60f, -0.17f);//bottom left

    glEnd();

    //bitting cuts (2) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.62f, -0.060f);//top left
    glVertex2f(-0.65f, -0.060); //top right
    glVertex2f(-0.65f, -0.17f);//bottom right
    glVertex2f(-0.62f, -0.17f);//bottom left
    glEnd();

    //bitting cuts frame (2)
    glLineWidth(3.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.62f, -0.060f);//top left
    glVertex2f(-0.65f, -0.060); //top right
    glVertex2f(-0.65f, -0.17f);//bottom right
    glVertex2f(-0.62f, -0.17f);//bottom left

    glEnd();

    //bitting cuts (3) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.70f, -0.060f);//top left
    glVertex2f(-0.67f, -0.060); //top right
    glVertex2f(-0.67f, -0.17f);//bottom right
    glVertex2f(-0.70f, -0.17f);//bottom left
    glEnd();


    //bitting cuts frame (3)
    glLineWidth(3.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.70f, -0.060f);//top left
    glVertex2f(-0.67f, -0.060); //top right
    glVertex2f(-0.67f, -0.17f);//bottom right
    glVertex2f(-0.70f, -0.17f);//bottom left

    glEnd();


    //bitting cuts (4) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.75f, -0.060f);//top left
    glVertex2f(-0.72f, -0.060); //top right
    glVertex2f(-0.72f, -0.17f);//bottom right
    glVertex2f(-0.75f, -0.17f);//bottom left
    glEnd();

    //bitting cuts frame (4)
    glLineWidth(3.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.75f, -0.060f);//top left
    glVertex2f(-0.72f, -0.060); //top right
    glVertex2f(-0.72f, -0.17f);//bottom right
    glVertex2f(-0.75f, -0.17f);//bottom left
    glEnd();

    //smaller blade
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.77f, 0.030f);//top left
    glVertex2f(-0.55f, 0.030f);//top right
    glVertex2f(-0.55f, -0.1f);//bottom right
    glVertex2f(-0.77f, -0.1f);//bottom left
    glEnd();


    //smaller blade frame
    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.77f, 0.030f);//top left
    glVertex2f(-0.55f, 0.030f);//top right
    glVertex2f(-0.55f, -0.109f);//bottom right
    glVertex2f(-0.77f, -0.109f);//bottom left

    glEnd();




    //the blade:

    glBegin(GL_QUADS);
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    glVertex2f(-0.8f, 0.035f);//top left
    glVertex2f(0.2f, 0.035f);//top right
    glVertex2f(0.2f, -0.035f);//bottom right
    glVertex2f(-0.8f, -0.035f);//bottom left
    glEnd();

    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.8f, 0.035f);//top left
    glVertex2f(0.2f, 0.035f);//top right
    glVertex2f(0.2f, -0.035f);//bottom right
    glVertex2f(-0.8f, -0.035f);//bottom left

    glEnd();

    //the neck:
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.1f, 0.07f);//top left
    glVertex2f(-0.05f, 0.07f);//top right
    glVertex2f(-0.05f, -0.07f);//bottom right
    glVertex2f(-0.1f, -0.07f);//bottom left
    glEnd();



    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.1f, 0.07f);//top left
    glVertex2f(-0.05f, 0.07f);//top right
    glVertex2f(-0.05f, -0.07f);//bottom right
    glVertex2f(-0.1f, -0.07f);//bottom left

    glEnd();

    //3 intersected circles (the key head):



     //top circle frame
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    drawFilledCircle(0.2f, 0.11f, 0.16f);

    //top circle
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    drawFilledCircle(0.2f, 0.1f, 0.15f);



    //middle circle frame
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    drawFilledCircle(0.41f, 0.0f, 0.16f);


    //middle circle
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    drawFilledCircle(0.4f, 0.0f, 0.15f);


    //bottom circle frame
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    drawFilledCircle(0.19f, -0.11f, 0.16f);

    //bottom circle
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    drawFilledCircle(0.2f, -0.1f, 0.15f);

}


void key2_Lock(){

    //bitting cuts (1) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.60f, -0.060f);//top left
    glVertex2f(-0.57f, -0.060); //top right
    glVertex2f(-0.57f, -0.17f);//bottom right
    glVertex2f(-0.60f, -0.17f);//bottom left
    glEnd();


    //bitting cuts frame (1)
    glLineWidth(3.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.60f, -0.060f);//top left
    glVertex2f(-0.57f, -0.060); //top right
    glVertex2f(-0.57f, -0.17f);//bottom right
    glVertex2f(-0.60f, -0.17f);//bottom left

    glEnd();

    //bitting cuts (2) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.62f, -0.060f);//top left
    glVertex2f(-0.65f, -0.060); //top right
    glVertex2f(-0.65f, -0.17f);//bottom right
    glVertex2f(-0.62f, -0.17f);//bottom left
    glEnd();

    //bitting cuts frame (2)
    glLineWidth(3.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.62f, -0.060f);//top left
    glVertex2f(-0.65f, -0.060); //top right
    glVertex2f(-0.65f, -0.17f);//bottom right
    glVertex2f(-0.62f, -0.17f);//bottom left

    glEnd();

    //bitting cuts (3) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.70f, -0.060f);//top left
    glVertex2f(-0.67f, -0.060); //top right
    glVertex2f(-0.67f, -0.17f);//bottom right
    glVertex2f(-0.70f, -0.17f);//bottom left
    glEnd();


    //bitting cuts frame (3)
    glLineWidth(3.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.70f, -0.060f);//top left
    glVertex2f(-0.67f, -0.060); //top right
    glVertex2f(-0.67f, -0.17f);//bottom right
    glVertex2f(-0.70f, -0.17f);//bottom left

    glEnd();


    //bitting cuts (4) from the right:
    glBegin(GL_QUADS);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.75f, -0.060f);//top left
    glVertex2f(-0.72f, -0.060); //top right
    glVertex2f(-0.72f, -0.17f);//bottom right
    glVertex2f(-0.75f, -0.17f);//bottom left
    glEnd();

    //bitting cuts frame (4)
    glLineWidth(3.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.75f, -0.060f);//top left
    glVertex2f(-0.72f, -0.060); //top right
    glVertex2f(-0.72f, -0.17f);//bottom right
    glVertex2f(-0.75f, -0.17f);//bottom left
    glEnd();

    //smaller blade
    glBegin(GL_QUADS);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.55f, 0.030f);//top right
    glVertex2f(-0.55f, -0.1f);//bottom right
    glVertex2f(-0.77f, -0.1f);//bottom left
    glEnd();


    //smaller blade frame
    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.77f, 0.030f);//top left
    glVertex2f(-0.55f, 0.030f);//top right
    glVertex2f(-0.55f, -0.109f);//bottom right
    glVertex2f(-0.77f, -0.109f);//bottom left

    glEnd();




    //the blade:

    glBegin(GL_QUADS);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.8f, 0.035f);//top left
    glVertex2f(0.2f, 0.035f);//top right
    glVertex2f(0.2f, -0.035f);//bottom right
    glVertex2f(-0.8f, -0.035f);//bottom left
    glEnd();

    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.8f, 0.035f);//top left
    glVertex2f(0.2f, 0.035f);//top right
    glVertex2f(0.2f, -0.035f);//bottom right
    glVertex2f(-0.8f, -0.035f);//bottom left


    glEnd();



    //the neck:
    glBegin(GL_QUADS);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.1f, 0.07f);//top left
    glVertex2f(-0.05f, 0.07f);//top right
    glVertex2f(-0.05f, -0.07f);//bottom right
    glVertex2f(-0.1f, -0.07f);//bottom left
    glEnd();



    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.1f, 0.07f);//top left
    glVertex2f(-0.05f, 0.07f);//top right
    glVertex2f(-0.05f, -0.07f);//bottom right
    glVertex2f(-0.1f, -0.07f);//bottom left

    glEnd();

    //3 intersected circles (the key head):
     //top circle frame
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    drawFilledCircle(0.2f, 0.11f, 0.16f);

    //top circle
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledCircle(0.2f, 0.1f, 0.15f);



    //middle circle frame
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    drawFilledCircle(0.41f, 0.0f, 0.16f);


    //middle circle
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledCircle(0.4f, 0.0f, 0.15f);


    //bottom circle frame
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    drawFilledCircle(0.19f, -0.11f, 0.16f);

    //bottom circle
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledCircle(0.2f, -0.1f, 0.15f);


}
void key3() {

    //the head

    //bigger oval frame
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    drawFilledOval(0.30, 0.1f, 0.32f);//0.2 //OVAL

    //the head(bigger oval)
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    drawFilledOval(0.3f, 0.1f, 0.3f);//0.2 //OVAL



    //smaller circle frame
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    drawFilledCircle(0.52, 0.1f, 0.052f);

    //smaller circle
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    drawFilledCircle(0.51, 0.1f, 0.050f);


    //top circle frame
    glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
    drawFilledCircle(0.30f, 0.192f, 0.15f);

    //bottom circle frame
    glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
    drawFilledCircle(0.30f, 0.028f, 0.15f);

    //top circle(head)
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.30f, 0.19f, 0.14f);




    //bottom circle (head)
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.30f, 0.030f, 0.14f);



    //bitting cuts frame
    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.7f, 0.4f);//top left
    glVertex2f(-0.45, 0.4); //top right
    glVertex2f(-0.45, 0.06);//bottom right
    glVertex2f(-0.7f, 0.06f);//bottom left


    glEnd();
    //the blade

    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    glRectf(0.109, 0.14, -0.8f, 0.06f);

    //blade frame
    glLineWidth(4.);
    glBegin(GL_LINE_LOOP);

    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.8f, 0.14f);//top left
    glVertex2f(0.109, 0.14); //top right
    glVertex2f(0.109, 0.06);//bottom right
    glVertex2f(-0.8f, 0.06f);//bottom left
    glEnd();


    //the neck
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    glRectf(0.12, 0.18, 0.002f, 0.015f);



    //necl frame
    glLineWidth(4.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(0.002f, 0.18f);//top left
    glVertex2f(0.12, 0.18); //top right
    glVertex2f(0.12, 0.015);//bottom right
    glVertex2f(0.002f, 0.015f);//bottom left
    glEnd();
    
    //bitting cuts
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    glRectf(-0.45, 0.4, -0.7f, 0.09);
    
    //right circle
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.575f, 0.31f, 0.08f);

    //left circle
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.575f, 0.21f, 0.08f);


    //right rect
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    glRectf(-0.40, 0.45, -0.45, 0.4);

    //right rect frame
    glLineWidth(4.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.45, 0.45f);//top left
    glVertex2f(-0.40, 0.45); //top right
    glVertex2f(-0.40, 0.4);//bottom right
    glVertex2f(-0.45, 0.4);//bottom left
    glEnd();


    //left rect
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    glRectf(-0.7, 0.45, -0.75, 0.4);

    //left rect frame
    glLineWidth(4.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(-0.75f, 0.45f);//top left
    glVertex2f(-0.7, 0.45); //top right
    glVertex2f(-0.7, 0.4);//bottom right
    glVertex2f(-0.75, 0.4);//bottom left


    glEnd();

}

void key3_Lock() {

    //the head

  //bigger oval frame
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    drawFilledOval(0.30, 0.1f, 0.32f);//0.2 //OVAL

    //the head(bigger oval)
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledOval(0.3f, 0.1f, 0.3f);//0.2 //OVAL



    //smaller circle frame
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    drawFilledCircle(0.52, 0.1f, 0.052f);

    //smaller circle
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledCircle(0.51, 0.1f, 0.050f);


    //top circle frame
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledCircle(0.30f, 0.192f, 0.15f);

    //bottom circle frame
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledCircle(0.30f, 0.028f, 0.15f);

    //top circle(head)
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledCircle(0.30f, 0.19f, 0.14f);




    //bottom circle (head)
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledCircle(0.30f, 0.030f, 0.14f);



    //bitting cuts frame
    glLineWidth(5.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.7f, 0.4f);//top left
    glVertex2f(-0.45, 0.4); //top right
    glVertex2f(-0.45, 0.06);//bottom right
    glVertex2f(-0.7f, 0.06f);//bottom left


    glEnd();
    //the blade

    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glRectf(0.109, 0.14, -0.8f, 0.06f);

    //blade frame
    glLineWidth(4.);
    glBegin(GL_LINE_LOOP);

    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.8f, 0.14f);//top left
    glVertex2f(0.109, 0.14); //top right
    glVertex2f(0.109, 0.06);//bottom right
    glVertex2f(-0.8f, 0.06f);//bottom left
    glEnd();


    //the neck
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glRectf(0.12, 0.18, 0.002f, 0.015f);



    //necl frame
    glLineWidth(4.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(0.002f, 0.18f);//top left
    glVertex2f(0.12, 0.18); //top right
    glVertex2f(0.12, 0.015);//bottom right
    glVertex2f(0.002f, 0.015f);//bottom left


    glEnd();


    //bitting cuts
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glRectf(-0.45, 0.4, -0.7f, 0.09);

    //right circle
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledCircle(-0.45f, 0.27f, 0.05f);

    //left circle
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    drawFilledCircle(-0.7f, 0.27f, 0.05f);

    //right rect
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glRectf(-0.40, 0.45, -0.45, 0.4);

    //right rect frame
    glLineWidth(4.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.45, 0.45f);//top left
    glVertex2f(-0.40, 0.45); //top right
    glVertex2f(-0.40, 0.4);//bottom right
    glVertex2f(-0.45, 0.4);//bottom left


    glEnd();


    //left rect
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glRectf(-0.7, 0.45, -0.75, 0.4);

    //left rect frame
    glLineWidth(4.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.75f, 0.45f);//top left
    glVertex2f(-0.7, 0.45); //top right
    glVertex2f(-0.7, 0.4);//bottom right
    glVertex2f(-0.75, 0.4);//bottom left


    glEnd();

}
void FoundKeys() {
  //  glRectf(0.4, -0.7, -0.4f, -9.05f);

    glBegin(GL_QUADS);
    glColor4f(0.7, 0.7f, 0.7f, 1.0f);
    glVertex2f(-0.4f, -0.7f);//top left

    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(0.4, -0.7); //top right

    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(0.4, -0.98f);//bottom right

    glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
    glVertex2f(-0.4f, -0.98f);//bottom left
    glEnd();
    
    glLineWidth(4.);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glVertex2f(-0.4f,-0.7f);//top left
    glVertex2f(0.4, -0.7); //top right
    glVertex2f(0.4, -0.98);//bottom right
    glVertex2f(- 0.4f, -0.98f);//bottom left


    glEnd();


}

void lockMatrix () {
    
    //FoundKeys matrix key 1
    glPushMatrix();
    glScalef(0.2, 0.2, 1.0);
    glTranslatef(-.1, -3.9, 0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    Key1_Lock();
    glPopMatrix();
    
    
    //FoundKeys matrix key 2
    glPushMatrix();
    glScalef(0.18, 0.18, 1.0);
    glTranslatef(-1.5, -4.5, 0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    key2_Lock();
    glPopMatrix();
    
    //FoundKeys matrix key 3
    glPushMatrix();
    glScalef(0.18, 0.18, 1.0);
    glTranslatef(1.5, -4.5 ,0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    key3_Lock();
    glPopMatrix();
    
    glEnd();
}
    void HiddinMatrix()
    {
        //key 1 matrix
        
        glPushMatrix();
        glScalef(.15, .15, 1.0);
        glTranslatef(-3.0, -2., 0.0);
        glRotatef(-45.0, 0.0, 0.0, 1.0);
        Key1();
        glPopMatrix();

       
        //key2 matrix
        glPushMatrix();
        glScalef(.15, .15, 1.0);
        glTranslatef(5.5, -5.0, 0.0);
        glRotatef(75.0, 0.0, 0.0, 1.0);
        key2();
        glPopMatrix();
        
        //key3 matrix
        glPushMatrix();
        glScalef(.15, .15, 1.0);
        glTranslatef(-5., -6.0, 0.0);
        glRotatef(-120.0, 0.0, 0.0, 1.0);
        key3();
        glPopMatrix();
        glEnd();
    

}
void Bckg1 ()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //  colors
    glColor4f(.1484375f, .27734375f, 0.44921875f,1.0f);
    drawFilledCircle(0,0.3,0.4);
    glColor4f(.1640625f, .31640625f, 0.50390625f,0.5f);
    drawFilledCircle(0,0.3,0.9);

    // bloody moon
     //base color
    glColor4f(0.4f, 0.4f,0.4f,1.0f);
    drawFilledCircle(-0.3,0.7,0.1);
    //red
    glColor4f(1.0f, 0.0f, 0.0f,0.5f);
    drawFilledCircle(-0.3, 0.7, 0.1);
    

//    //cloude down right
//        glColor4f(0.0f, 0.0f, 0.0f,1.0f);
    glColor4f(0.6f, 0.6f, 0.6f,1.0f);

        drawFilledCircle(0.5, 0.32 ,0.06); //r
        drawFilledCircle(0.4, 0.35 ,0.09); //c
        drawFilledCircle(0.31, 0.32 ,0.05); //l
   
    //top-cinter right
//    glColor4f(0.75f, 0.75f, 0.75f,1.0f);
    
    glColor4f(0.6f, 0.6f, 0.6f,1.0f);

    drawFilledCircle(0.3, 0.55 ,0.06); //r
    drawFilledCircle(0.2, 0.58 ,0.09); //c
    drawFilledCircle(0.1, 0.55 ,0.05); //l

//left
//    glColor4f(0.75f, 0.75f, 0.75f,1.0f);
    glColor4f(0.6f, 0.6f, 0.6f,1.0f);
    drawFilledCircle(-0.2, 0.32 ,0.06); //r
    drawFilledCircle(-0.3, 0.35 ,0.09); //c
    drawFilledCircle(-0.11, 0.32 ,0.05); //l
    
// center
//    glColor4f(0.75f, 0.75f, 0.75f,1.0f);
    glColor4f(0.6f, 0.6f, 0.6f,1.0f);
    drawFilledCircle(-0.09, 0.12 ,0.06); //r
    drawFilledCircle(0.006, 0.15 ,0.09); //c
    drawFilledCircle(0.11, 0.12 ,0.05); //l

    // down right
//    glColor4f(0.75f, 0.75f, 0.75f,1.0f);
    glColor4f(0.6f, 0.6f, 0.6f,1.0f);
    drawFilledCircle(0.2, 0.01 ,0.06); //r
    drawFilledCircle(0.3, 0.03 ,0.09); //c
    drawFilledCircle(0.11, 0.01 ,0.05); //l
    
    //down left
//    glColor4f(0.75f, 0.75f, 0.75f,1.0f);
    glColor4f(0.6f, 0.6f, 0.6f,1.0f);
    drawFilledCircle(-0.3, -0.1 ,0.06); //r
    drawFilledCircle(-0.35, -0.07 ,0.09); //c
    drawFilledCircle(-0.21, -0.1 ,0.05); //l

    glEnd();
    
    glDisable(GL_BLEND);
    
}

void window ()
{
    //Hollo square
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.4f,  0.8f);//top left edg
    glVertex2f(-0.3f, -0.2f);//down left edges
    
    glVertex2f( 0.3f, - 0.2f);//down  right edg
    glVertex2f( 0.4f, 0.8f);// top right edges
    glEnd();
    
    // window lines
    //main line
    glLineWidth(30.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, -0.2f); // down edge
    glVertex2f(0.0f,0.8f); // top edge
    glEnd();
    
    
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    
    //line 1 - right
    glVertex2f(0.18f, -0.2f); // down edge
    glVertex2f(0.2f,0.8f); // top edge
    
    //lin2 - left
    glVertex2f(-0.18f, -0.2f); // down edge
    glVertex2f(-0.2f,0.8f); // top edge
    
    // horizintal lines
    
    glVertex2f(0.335f, 0.07f); // right  edge
    glVertex2f(-0.335f,0.07f); // left edge
    
    glVertex2f(0.35f, 0.2f); // right  edge
    glVertex2f(-0.35f,0.2f); // left edge
    
    
    glVertex2f(0.35f, 0.358f); // right  edge
    glVertex2f(-0.35f,0.358f); // left edge
    
    glVertex2f(0.358f, 0.5f); // right  edge
    glVertex2f(-0.358f,0.5f); // left edge
    //glColor3f(0.4f, 0.35f, 0.3f);
    glVertex2f(0.38f, 0.68f); // right  edge
    glVertex2f(-0.38f,0.68f); // left edge
    
    glEnd();
}

void floor() {
    
      glEnable(GL_TEXTURE_2D);
      glBindTexture( GL_TEXTURE_2D, myTexture1 );
      glColor4f(1.0f, 1.0f, 1.0, 1.0f);
      glBegin(GL_QUADS);
 
    glTexCoord2f(0.0, 0.0); glVertex2f(-1.30f, -1.30f);    //down left edges
    glTexCoord2f(3.0, 0.0); glVertex2f(1.30f, -1.30f);    //down  right edg
    glTexCoord2f(3.0, 3.0); glVertex2f(0.7f, -0.2f);   // top right edges
    glTexCoord2f(0.0, 3.0); glVertex2f(-0.7f, -0.2f);  //top left edg

    glEnd();
    glDisable(GL_TEXTURE_2D);


}

void wall() {
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, myTexture1 );
    
    glColor4f(0.5f, 0.5f, 0.5, 1.0f);
    glBegin(GL_QUADS);//right wall
    glVertex2f(0.7f, 1.30f); glTexCoord2f(3.0, 0.0); //top left edg
    glVertex2f(0.7f, -0.2f); glTexCoord2f(0.0, 0.0);   //down left edges
      
      glVertex2f(1.30f, -1.35f); glTexCoord2f(0.0, 3.0);    //down  right edg
      glVertex2f(1.30f, 1.30f); glTexCoord2f(3.0, 3.0);   // top right edges
      
    
    glEnd();
    
    glBegin(GL_QUADS);//middle wall, to the window's right
//    glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
//    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glVertex2f(0.42f, 1.30f); glTexCoord2f(3.0, 0.0); //top left edg
    glVertex2f(0.3, -0.2); glTexCoord2f(0.0, 0.0);   //down left edges
    
    glVertex2f(0.7f, -0.2f); glTexCoord2f(0.0, 3.0);  //down  right edg
    glVertex2f(0.7f, 1.30f); glTexCoord2f(3.0, 3.0);   // top right edges
    
    glEnd();
    
    
    glBegin(GL_QUADS);//middle wall, to the window's left
//    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
//    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);

    glVertex2f(-0.7f, 1.30f); glTexCoord2f(3.0, 0.0);    //top left edg
    glVertex2f( - 0.8f, -0.3f); glTexCoord2f(0.0, 0.0); //down left edges
    
    glVertex2f(-0.3f, -0.2f); glTexCoord2f(0.0, 3.0);   //down  right edg
    glVertex2f(-0.43f, 1.30f); glTexCoord2f(3.0, 3.0);   // top right edges
    
    
    glEnd();
    
    
    glBegin(GL_QUADS);//left wall
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
//    glColor4f(0.3f, 0.3f, 0.3, 1.0f);
    glVertex2f(-1.30f, 1.30f); glTexCoord2f(3.0, 0.0);    //top left edg
    glVertex2f(-1.30f, -1.35f); glTexCoord2f(0.0, 0.0); //down left edges
    
    glVertex2f(-0.7f, -0.2f); glTexCoord2f(0.0, 3.0);   //down  right edg
    glVertex2f(-0.7f, 1.30f); glTexCoord2f(3.0, 3.0);    // top right edges
    /*
    
    glVertex2f(0.7f, -0.2f); glTexCoord2f(0.0, 1.0);   //down  right edg
    glVertex2f(-0.7f, -0.2f); glTexCoord2f(1.0, 1.0);    // top right edges
    
    */
    glEnd();
    
    
    glBegin(GL_QUADS);//middle wall above the window
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
//    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);

//    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex2f(-0.43f, 1.30f); glTexCoord2f(3.0, 0.0); //top left edg //
    glVertex2f(-0.41f, 0.8f); glTexCoord2f(0.0, 0.0);   //down left edges//
    
    glVertex2f(0.40f, 0.8f); glTexCoord2f(0.0, 3.0);    //down  right edg//
    glVertex2f(0.43f, 1.30f); glTexCoord2f(3.0, 3.0);   // top right edges
    
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //walls lines
    glLineWidth(3.0f);
    glBegin(GL_LINES);
   
    glColor4f(0.05f, 0.05f, 0.05f, 1.0f);
    glLineWidth(3.0f);
    glVertex2f(0.7f, 1.30f);//wall line - right
    glVertex2f(0.7f, -0.2f);

    glVertex2f(0.7f, -0.2f);//floor line - right
    glVertex2f(1.25f, -1.25f);

    glVertex2f(-0.7f, 1.30);//wall line - left
    glVertex2f( - 0.7f, -0.2f);

    glVertex2f(-0.7f, -0.2f);//floor line - left
    glVertex2f(-1.25f, -1.25f);

    
    glVertex2f(-0.7f, -0.2f);//floor line - below the window
    glVertex2f(0.7f, -0.2f);
    

    glEnd();
  

}

void spiderNet()
{
    // circles around the web
    glLineWidth(1.5f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawNetCircle(0, 0, .0);
    drawNetCircle(0, 0, .1);
    drawNetCircle(0, 0, .2);
    drawNetCircle(0, 0, .3);
    // drawHollowCircle(0,0,.4);
    drawNetCircle(0, 0, .5);
    //drawHollowCircle(0,0,.6);
    drawNetCircle(0, 0, .7);
    //   drawHollowCircle(0,0,.8);
    drawNetCircle(0, 0, .9);

    glEnd();
    // ai for repeating lines
    glBegin(GL_LINES);
    glLineWidth(1.5f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 20) {
        float angle = i * M_PI / 180.0; // it can be M_PI or only PI
        glVertex2f(0.0f, 0.0f);
        glVertex2f(cos(angle), sin(angle));
    }
    glEnd();


}

void spiderLine() {
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glLineWidth(.01);
    glBegin(GL_LINES);

    glColor4f(0.75f, 0.75f, 0.75f, 0.5f);
    glVertex2f(-0.75, 0.6);//top left
    glVertex2f(-0.75, -0.9);//bottom

    glDisable(GL_BLEND);
    glEnd();
}


void SpiderMatrix()
{
    //spider matrix
    glPushMatrix();
    glScalef(.15, .15, 1.0);
    glTranslatef(-5., -6.0, 0.0);
    glRotatef(-120.0, 0.0, 0.0, 1.0);
    Spider();
    glPopMatrix();

    //spider matrix 2
    glPushMatrix();
    glScalef(.05, .05, 1.0);
    glTranslatef(6.2, 9.0, 0.0);
 
    Spider();
    glPopMatrix();

    //spider matrix 3
    glPushMatrix();
    glScalef(.05, .05, 1.0);
    glTranslatef(-12.2, 10.0, 0.0);
    Spider();
    glPopMatrix();
    
    //spider matrix 4
        glPushMatrix();
        glScalef(.15, .15, 1.0);
        glTranslatef(2.5, -2.5, 0.0);
        Spider();
        glPopMatrix();

    
    //Spider net matrix - left
    glPushMatrix();
    glScalef(.2, .2, 1.0);
    glTranslatef(-3.7, 3.5, 0.0);
    spiderNet();
    glPopMatrix();
    
    
    //Spider net 2 matrix - right
        glPushMatrix();
        glScalef(.12, .12, 1.0);
        glTranslatef(6.5, 6.0, 0.0);
        spiderNet();
        glPopMatrix();
    
    
    glEnd();
}
void mop()
{
    //stick
    glLineWidth(10.0f);
    glColor3f(0.6, 0.4, 0.2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2, -0.4);
    glVertex2f(-0.2, 0.4);
    glEnd();
    //mop
    glColor3f(0.9, 0.9, 0.9);
    glRectf(-0.42, 0.6, 0.03, 0.4);
    //mop shading
    glLineWidth(4.0f);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINE_LOOP); // R
    glVertex2f(0.01, 0.45);
    glVertex2f(0.01, 0.6);
    glEnd();
    
    glLineWidth(4.0f);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINE_LOOP); // R
    glVertex2f(-0.03, 0.45);
    glVertex2f(-0.03, 0.6);
    glEnd();
    
    glLineWidth(4.0f);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINE_LOOP); // R
    glVertex2f(-0.07, 0.45);
    glVertex2f(-0.07, 0.6);
    glEnd();
    
    glLineWidth(4.0f);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINE_LOOP); // R
    glVertex2f(-0.12, 0.45);
    glVertex2f(-0.12, 0.6);
    glEnd();
    
    glLineWidth(4.0f);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINE_LOOP); // R
    glVertex2f(-0.166, 0.45);
    glVertex2f(-0.166, 0.6);
    glEnd();
    
    glLineWidth(4.0f);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINE_LOOP); // R
    glVertex2f(-0.22, 0.45);
    glVertex2f(-0.22, 0.6);
    glEnd();
    
    glLineWidth(4.0f);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINE_LOOP); // R
    glVertex2f(-0.27, 0.45);
    glVertex2f(-0.27, 0.6);
    glEnd();
    
    glLineWidth(4.0f);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINE_LOOP); // R
    glVertex2f(-0.32, 0.45);
    glVertex2f(-0.32, 0.6);
    glEnd();
    
    glLineWidth(4.0f);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINE_LOOP); // R
    glVertex2f(-0.37, 0.45);
    glVertex2f(-0.37, 0.6);
    glEnd();
    
    glLineWidth(3.0f);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINE_LOOP); // R
    glVertex2f(-0.415, 0.45);
    glVertex2f(-0.415, 0.6);
    glEnd();

    
    //mop holder
    glColor3f(0.6, 0.4, 0.2);
    glRectf(-0.42, 0.4, 0.03, 0.45);
    
}

void MopMatrix(){
    glPushMatrix();
    glScalef(0.7, 0.7, 1.0);
    glTranslatef(-1.1, 0.0, 0.0);
    glRotatef(-165, 0.0, 0.0,1.0);
    mop();
    glPopMatrix();
    
}

void ghost() {
    
    //triangles
    glBegin(GL_TRIANGLES);
    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(0.3, -0.5f);
    glVertex2f(0.2f, -0.3f);
    glEnd();

}

void ghostDraw() {

    //the body
    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    glPushMatrix();
    glRotatef(-180, 0, 0, 1);
    glScalef(0.6, 2.0, 1.0);
    drawFilledCirclehalfghost(0, 0, 0.25);
    glPopMatrix();

    //first triagle right
    glPushMatrix();
    glScalef(-0.5, -0.5, -0.5);
    glTranslatef(-0.402, 0.5, 0);
    ghost();
    glPopMatrix();


    //second triangle right
    glPushMatrix();
    glScalef(-0.5, -0.5, -0.5);
    glTranslatef(-0.202, 0.5, 0);
    ghost();
    glPopMatrix();

    //trhird triangle left
    glPushMatrix();
    glScalef(-0.5, -0.5, -0.5);
    glTranslatef(-0.0, 0.5, 0);
    ghost();
    glPopMatrix();

    //ghost eyes
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircleghost(0.04, 0.3, 0.04);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircleghost(-0.05, 0.3, 0.04);
    glEnd();
}

void winMsgBckgHH(){

    glColor4f(0.9f, 0.9f, 0.9f, 0.9);
    glRectf(0.80, 0.1, -0.87, -0.1);

    glLineWidth(2.0);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINE_LOOP);

    glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
    glVertex2f(-0.87f, 0.1);//top left
    glVertex2f(0.80, 0.1);//top right //
    glVertex2f(0.80, -0.1);//bottom right
    glVertex2f(-0.87, -0.1);//bottom left//

    glEnd();

    glDisable(GL_LINE_STIPPLE);

}

void winMsgHH(){

    glColor3f(1.0f, 0.0f, 0.0f);
    std::string text;
    text = "YOU FOUND ALL THE KEYS!! HURRY UP AND ESCAPE!!";
    drawStrokeText(text.data(), static_cast<int>(text.size()),45, 300);

}

//------------------------Hunted House Display------------------------
void huntedHouseDisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(.12109375f, .23046875f, 0.3671875f,1.0f); // set background color
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

        //speed
        ghost1+=0.003;// works
        ghost2+= 0.005;//
        ghost4+=0.001; // dawn up

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        Bckg1();
        window();
        wall();
        floor();
        spiderLine();
        //scaling and translating methods
        FoundKeys() ;
        HiddinMatrix();
        lockMatrix();
        SpiderMatrix();
        MopMatrix();
        
    ///////////////////////////////////////////////////////////////////////////////////
    
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        //ghostDraw Matrix1 -:

            glPushMatrix();
            glScalef(0.7, 0.7, 1.0);
            glTranslatef(ghost2, 0.9, 0);
            ghostDraw();
            glPopMatrix();
        if (ghost2>1.5){
            //to where
            ghost2=-2.0; }
        //ghostDraw  Matrix 2 - it works perfectly :

        glPushMatrix();
        glScalef(0.7, 0.7, 1.0);
        glTranslatef(ghost1, -0.001, 0);
        ghostDraw();
        glPopMatrix();
        if (ghost1>1.5){
            //to where
            ghost1=-2.0;}
            
         //ghostDraw  Matrix 3 - hiddin key :
         
            // ghost3
            glPushMatrix();
            glScalef(0.7, 0.7, 1.0);
            glTranslatef(1.25, -1.5, 0);
            ghostDraw();
            glPopMatrix();
    
            //ghostDraw  Matrix 4 on y axis :
            glPushMatrix();
            glScalef(0.7, 0.7, 1.0);
            glTranslatef(-0.09, ghost4, 0);
            ghostDraw();
            glPopMatrix();
        if (ghost4>1.5){
            ghost4-=2.0;}
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    ///////////////////////////////////////////////////////////////////////////////////
    //FoundKeys matrix key 1
            if (key1_flag) {

                 glPushMatrix();
                 glScalef(0.18, 0.18, 1.0);
                 glTranslatef(-1.5, -4.5, 0);
                 glRotatef(90.0, 0.0, 0.0, 1.0);
                 key2();
                 glPopMatrix();
             }

    //FoundKeys matrix key 2
             if (key2_flag) {

                 glPushMatrix();
                 glScalef(0.2, 0.2, 1.0);
                 glTranslatef(-.1, -3.9, 0);
                 glRotatef(90.0, 0.0, 0.0, 1.0);
                 Key1();
                 glPopMatrix();
             }

    //FoundKeys matrix key 3
             if (key3_flag) {
                 
                 glPushMatrix();
                 glScalef(0.18, 0.18, 1.0);
                 glTranslatef(1.5, -4.5, 0);
                 glRotatef(90.0, 0.0, 0.0, 1.0);
                 key3();
                 glPopMatrix();
             }
    
    //print text
             if ( key1_flag && key2_flag && key3_flag) {
                 glPushMatrix();
                 winMsgBckgHH();
                 winMsgHH();
                 glPopMatrix();
                 
             }
    
    glEnd();
    glFlush();
    glutSwapBuffers();
}
//---------------------start Page---------------------------
void startPage(){
    
    glColor3f(0.3, 0.3, 0.3);
    glRectf(-10.0, -10.0, 10.0, 10.0);
    
    glColor3f(0.9, 0.6, 0.2);
    glRectf(-0.5, 0.3, 0.5, 0.45);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    std::string text;
    text = " Welccom to the game ";
    drawStrokeText(text.data(), static_cast<int>(text.size()), 190, 410);
    
    text = " TO UNLOCK ALLI BABA'S TRESUER ENTER: 1";
    drawStrokeText(text.data(), static_cast<int>(text.size()), 90, 340);
    
    text = "TO ESCAPE THE HUNTED HOUSE ENTER: 2";
    drawStrokeText(text.data(), static_cast<int>(text.size()), 100, 310);
    
    text = "TO EXIT ENTER: Q / q";
    drawStrokeText(text.data(), static_cast<int>(text.size()), 200, 280);
    
    //Spider-L scale and translation
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glScalef(0.1, 0.1, 0.0);
        glTranslatef(-9.0, -1.0, 0.0);
        Spider();
        glPopMatrix();
    
    //Spider-L scale and translation
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glScalef(0.1, 0.1, 0.0);
        glTranslatef(7.5, 0.4, 0.0);
        Spider();
        glPopMatrix();
    
    //chest
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.5, 0.5, 0.0);
    glTranslatef(0.1, -1.8, 0.0);
    treasureChest();
    glPopMatrix();
    
    // coin scale and translation
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glScalef(0.2, 0.18, 0.0);
        glTranslatef(1.7, -5.3, 0.0);
        coin();
        glPopMatrix();
        //
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glScalef(0.2, 0.18, 0.0);
        glTranslatef(1.4, -5.6, 0.0);
        coin();
        glPopMatrix();
        //
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glScalef(0.2, 0.18, 0.0);
        glTranslatef(1.7, -5.5, 0.0);
        coin();
        glPopMatrix();
        //
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glScalef(0.2, 0.18, 0.0);
        glTranslatef(2.1, -5.5, 0.0);
        coin();
        glPopMatrix();
        //
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glScalef(0.2, 0.18, 0.0);
        glTranslatef(2.4, -5.6, 0.0);
        coin();
        glPopMatrix();
    
    glPushMatrix();
               glScalef(0.7, 0.7, 1.0);
               glTranslatef(1.25, 0.5, 0);
               ghostDraw();
               glPopMatrix();
               //ghostDraw  Matrix 4 on y axis :
               glPushMatrix();
               glScalef(0.7, 0.7, 1.0);
               glTranslatef(-0.4,-0.7, 0);
               ghostDraw();
               glPopMatrix();
         
           glDisable(GL_BLEND);
           glEnd();
}

//------------------------------------------------

//---------------------Reading files--------------------------\\


    //http://stackoverflow.com/questions/12518111/how-to-load-a-bmp-on-glut-to-use-it-as-a-texture
    GLuint LoadTexture( const char * filename, int width, int height )
    {
        GLuint texture;
        unsigned char * data;
        FILE * file;
        
        //The following code will read in our RAW file
        file = fopen( filename, "rb" );
        
        if ( file == NULL )
        {
            cout<<"Unable to open the image file"<<endl<<"Program will exit :("<<endl;
            exit(0);
            return 0;
        }
        
        data = (unsigned char *)malloc( width * height * 3 );
        fread( data, width * height * 3, 1, file );
        
        fclose( file );
        
        
        // reorder the image colors to RGB not BGR
        for(int i = 0; i < width * height ; ++i)
        {
            int index = i*3;
            unsigned char B,R;
            B = data[index];
            R = data[index+2];
            
            data[index] = R;
            data[index+2] = B;
            
        }
        
 //---------------------Loading textures ---------------------------------\\
        
       
        glGenTextures( 1, &texture );            //generate the texture with the loaded data
        glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it's array
        
        //changing the texture view
        
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //set texture  environment parameters
        
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        /////////////////////////////////////////
        
        free( data ); //free the texture array
        
        if (glGetError()!=GL_NO_ERROR)
            printf("GLError in genTexture()\n");
        
        return texture; //return whether it was successfull
    }
    

//---------------------Actions---------------------------


//------------------CLICK INTERACTION-------------------//

static
void mouse(int button, int state, int x, int y)
{
    int new_y = win_hight - y;

    if (button == GLUT_LEFT_BUTTON) {

        if (state == GLUT_UP) {
            
            ////////////////////////////////////////////////////////////////////
            ///GEMS
           
                if ((x > 12) && (x < 31) && (new_y < 230) && (new_y > 212)) {
                    Gem1_flag = true;
                    }

        
                if ((x > 472) && (x < 482) && (new_y < 65) && (new_y > 46)) {
                    Gem2_flag = true;}

                if ((x > 7) && (x < 27) && (new_y < 29) && (new_y > 13)) {
                    Gem3_flag = true;
                }

            ////////////////////////////////////////////////////////////////////
            ///KEYS

                if ((x > 445) && (x < 467) && (new_y < 87) && (new_y > 55)) {
                key1_flag = true;
                }


                if ((x > 101) && (x < 139) && (new_y < 201) && (new_y > 173)) {
                    key2_flag = true;
                }

            
                if ((x > 43) && (x < 93) && (new_y < 42) && (new_y > 15)) {
                    key3_flag = true;
                   
                }
        }
    }
}


static
void key(unsigned char keyPressed, int x, int y) // key handling
{
    switch (keyPressed)
    {
        case 'q':
                case 'Q':
                    exit(0);
                    break;

        case '1' :
//            huntedHouseDisplay();
            ABT = true;
            break;

        case '2' :
//            alliBabaDisplay();
            HH = true ;
        break;
            
                default: //user manual
                    fprintf( stderr, "\nKeyboard commands:\n\n"

                            "q, <esc>    - Quit\n" );
                    break;
    }
}

static void play( void )
{
    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glEnable(GL_BLEND);
    
   if (start == true )
   {
       startPage();
    }

    if (ABT == true ){
        
        alliBabaDisplay();
    }
        
    else if (HH == true )
    {
        huntedHouseDisplay();
    }
        
    glDisable(GL_BLEND);
    glFlush();
    glutSwapBuffers();
}

void reshapeFun(GLint newWidth, GLint newHight)
{
    glViewport(0, 0, newWidth, newHight);
    win_width = newWidth;
    win_hight = newHight;
}
        
void init (){
        
        transValueX = 0.0;
        transValueY = 0.0;
        transValueZ = 2.0;
        //------- Texture 1- wall  ---------
        myTexture1 = LoadTexture(image1Path,626,626);
        
        if(myTexture1 ==-1)
        {
            cout<<"Error in loading the texture"<<endl;
        }
        else
            cout<<"The xtexture value is: "<<myTexture1<<endl;
        
    }

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);   //  Specify the display Mode â€“ RGB, RGBA or color //  Index, single or double Buffer
    glutInitWindowSize(win_width, win_hight);       // Set the window's initial width & height
    glutInitWindowPosition(50, 50);                 // Position the window's initial top-left corner
    glutCreateWindow("The Computer Geeks");    // Create a window with the given title

    init ();
    ghost1 = -1.0;
    ghost2 =  1.0 ;
    ghost4 = -1.0;
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);                        // Register display callback handler for window re-paint
    glutReshapeFunc(reshapeFun);
    glutIdleFunc( play );
    glutMouseFunc ( mouse );
    glutKeyboardFunc ( key );
    
    glutMainLoop();                   // Enter the infinitely event-processing loop
    return 0;
}
