#include<iostream>
#include<stdlib.h>
#include<GL/glut.h>
using namespace std;

GLfloat points[4][2];
int k = 0;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0, 0, 0);
    glPointSize(4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void draw_line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    glColor3f(1.0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}

void midpoint_subdivision(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4){

    GLfloat xAB = (x1 + x2) / 2;
    GLfloat yAB = (y1 + y2) / 2;
    GLfloat xBC = (x2 + x3) / 2;
    GLfloat yBC = (y2 + y3) / 2;
    GLfloat xCD = (x3 + x4) / 2;
    GLfloat yCD = (y3 + y4) / 2;

    GLfloat xABC = (xAB + xBC) / 2;
    GLfloat yABC = (yAB + yBC) / 2;
    GLfloat xBCD = (xBC + xCD) / 2; 
    GLfloat yBCD = (yBC + yCD) / 2;

    GLfloat xABCD = (xABC + xBCD) / 2;
    GLfloat yABCD = (yABC + yBCD) / 2;

    if((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) > 4 || (x3- x2) * (x3 - x2) + (y3 - y2) * (y3 - y2) > 4 || (x4 - x3) * (x4 - x3) + (y4 - y3) * (y4 - y3) > 4) {
        midpoint_subdivision(x1, y1, xAB, yAB, xABC, yABC, xABCD, yABCD);
        midpoint_subdivision(xABCD, yABCD, xBCD, yBCD, xCD, yCD, x4, y4);
    }else {
        draw_line(x1, y1, xABCD, yABCD);
        draw_line(xABCD, yABCD, x4, y4);
    }
}

void mouse(int btn,int state,int x,int y){
    if(state==GLUT_DOWN){
        if(btn==GLUT_LEFT_BUTTON){

            points[k][0]=(float)(x);
            points[k][1]=(float)(500-y);
            glBegin(GL_POINTS);
            glVertex2f(points[k][0],points[k][1]);
            glEnd();
            glFlush();
            k++;

        }
        if(k==4){
            draw_line(points[0][0],points[0][1],points[1][0],points[1][1]);
            draw_line(points[1][0],points[1][1],points[2][0],points[2][1]);
            draw_line(points[2][0],points[2][1],points[3][0],points[3][1]);
            midpoint_subdivision(points[0][0],points[0][1],points[1][0],points[1][1],points[2][0],points[2][1],points[3][0],points[3][1]);

        }

    }

}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bazier Curve");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    init();
    glutMainLoop();
}