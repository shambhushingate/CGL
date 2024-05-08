
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#define h 900
#define w 900
using namespace std;

int currentMenuItem = 0;
bool isDrawing = false;
float xx0, yy0, xx1, yy1;

// Function to set a pixel at given coordinates
void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2d(x, y);
    glEnd();
    glFlush();
}

// Initialize OpenGL settings
void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set clear color to white
    glMatrixMode(GL_PROJECTION);       // Set the projection matrix
    glLoadIdentity();
    gluOrtho2D(-w / 2, h / 2, -w / 2, h / 2);  // Set the orthographic projection
    glMatrixMode(GL_MODELVIEW);        // Set the modelview matrix
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);           // Set drawing color to white
    glPointSize(1.0);                   // Set point size to 1.0
}

// Function to handle menu selection
void menu(int index)
{
    currentMenuItem = index;
}

// Function to draw a line using Bresenham's algorithm
void drawLine(int x1, int y1, int x2, int y2, int type)
{
    int interchange, err;
    int i = 0, t = 0;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int x = x1;
    int y = y1;

    if (dy > dx)
    {
        interchange = 1;
        swap(dx, dy);
    }
    else
    {
        interchange = 0;
    }
    err = 2 * dy - dx;

    while (i <= dx)
    {
        switch (type)
        {
        case 1: // for Simple line
            glBegin(GL_POINTS);
            glPointSize(1.0);
            setPixel(x, y);
            glEnd();
            break;

        case 2: // for dotted line
            if (i % 20 == 0)
            {
                glBegin(GL_POINTS);
                glPointSize(5.0);
                setPixel(x, y);
                glEnd();
            }
            break;

        case 3: // for dashed line
            if (i % 15 == 0)
            {
                t = 1 - t;
            }
            if (t == 0)
            {
                glBegin(GL_POINTS);
                glPointSize(1.0);
                setPixel(x, y);
                glEnd();
            }
            break;

        case 4: // for solid line
            glBegin(GL_POINTS);
            glPointSize(10);
            setPixel(x, y);
            glEnd();
            break;
        }

        if (err >= 0)
        {
            if (interchange == 1)
                x += sx;
            else
                y += sy;
            err -= 2 * dx;
        }

        if (interchange == 1)
            y += sy;
        else
            x += sx;
        err += 2 * dy;
        i++;
    }
    glFlush();
}

// Function to draw a pattern
void drawPattern()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    drawLine(-200, -200, -200, 200, 1);
    drawLine(-200, 200, 200, 200, 1);
    drawLine(200, 200, 200, -200, 1);
    drawLine(200, -200, -200, -200, 1);

    drawLine(0, -200, -200, 0, 1);
    drawLine(-200, 0, 0, 200, 1);
    drawLine(0, 200, 200, 0, 1);
    drawLine(200, 0, 0, -200, 1);

    drawLine(-100, -100, -100, 100, 1);
    drawLine(-100, 100, 100, 100, 1);
    drawLine(100, 100, 100, -100, 1);
    drawLine(100, -100, -100, -100, 1);
    glFlush();
}

// Function to handle mouse clicks
void myMouse(int button, int state, int xx, int yy)
{
    if(state == GLUT_DOWN){
        if (button == GLUT_LEFT_BUTTON )
        {
            if(currentMenuItem==5) // to draw a pattern
            {
                drawPattern();
            }
            else // to draw a line
            {
                if (!isDrawing)
                {
                    xx0 = - (w / 2)+xx;
                    yy0 = (h / 2 )- yy;
                    isDrawing = true;
                }
                else
                {
                    xx1 = - (w / 2)+xx;
                    yy1 =(h / 2 )- yy;
                    drawLine(xx0, yy0, xx1, yy1, currentMenuItem);
                    isDrawing = false;
                }
            }
           
        }
        else if (button == GLUT_RIGHT_BUTTON)
        {
            // Create menu
            glutCreateMenu(menu);
            glutAddMenuEntry("Simple Line", 1);
            glutAddMenuEntry("Dotted Line", 2);
            glutAddMenuEntry("Dashed Line", 3);
            glutAddMenuEntry("Solid Line", 4);
            glutAddMenuEntry("Pattern", 5);
            glutAttachMenu(GLUT_RIGHT_BUTTON);
        }
    }
}

// Function to handle display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(400, 200);
    glutInitWindowSize(900, 900);

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Drawing Lines");

    glutMouseFunc(myMouse);
    myInit();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
