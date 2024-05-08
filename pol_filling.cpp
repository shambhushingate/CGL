#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include<iostream>
using namespace std;

float oldColor[3] = {1.0, 1.0, 1.0};
float newColor[3] = {1.0, 0.0, 0.0};
float boundaryColor[3] = {0.0, 0.0, 0.0};
int xi;
int yi;

void Init()
{
    glClearColor(1.0,1.0,1.0,0);
    glColor3f(0.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

float* getPixelColor(int x, int y)
{
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void flood(int x, int y, float oldColor[3], float newColor[3])
{
    float* color = getPixelColor(x, y);
    if(color[0] == newColor[0] && color[1] == newColor[1] && color[2] == newColor[2])
    {
        return;
    }

    if (color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2])
    {
        glBegin(GL_POINTS);
        glColor3f(newColor[0], newColor[1], newColor[2]);
        glVertex2i(x,y);
        glEnd();
        glFlush();

        flood(x + 1, y, oldColor, newColor);
        flood(x - 1, y, oldColor, newColor);
        flood(x, y + 1, oldColor, newColor);
        flood(x, y - 1, oldColor, newColor);
        return;
    }
    return;
}

void boundaryFill(int x, int y, float bColor[3], float fillColor[3]){
    float* color = getPixelColor(x, y);

    if((color[0] != bColor[0] || color[1] != bColor[1] || color[2] != bColor[2]) && (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])){
        glBegin(GL_POINTS);
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        boundaryFill(x + 1, y, bColor, fillColor);
        boundaryFill(x - 1, y, bColor, fillColor);
        boundaryFill(x, y + 1, bColor, fillColor);
        boundaryFill(x, y - 1, bColor, fillColor);
        glFlush();
    }
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);
    glVertex2f(100, 100);
    glVertex2f(100, 200);
    glVertex2f(200, 200);
    glVertex2f(200, 100);
    glEnd();
    //boundaryFill(150, 150, boundaryColor, newColor);

    //flood(101, 101, oldColor, newColor);

    glFlush();
}

void menu(int n){
    switch(n){
        case 1: flood(xi, yi, oldColor, newColor);
                break;
        case 2: boundaryFill(xi, yi, boundaryColor, newColor);
                break;
    }

}


void mouse(int btn, int state, int x, int y){
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        xi = x;
        yi = 500 - y;
    }else if(btn == GLUT_RIGHT_BUTTON){
        glutCreateMenu(menu);
        glutAddMenuEntry("1. Flood Fill", 1);
        glutAddMenuEntry("2. Boundary Fill", 2);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Flood fill");
    glutDisplayFunc(display);

    glutMouseFunc(mouse);

    Init();
    glutMainLoop();
}