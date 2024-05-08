#include <iostream>
#include <GL/glut.h>
#include <cmath>
#define h 900
#define w 900
using namespace std;

int currentMenuItem = 0;
bool isDrawing = false;
float xx0, yy0, xx1, yy1;

// Initialize OpenGL settings
void myInit()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set clear color to black
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

// Function to draw a line using DDA algorithm
void drawLine(float xx0, float yy0, float xx1, float yy1, int type)
{
    float k;
    int s=0,i=1;
    
    float dx = abs(xx1 - xx0);
    float dy = abs(yy1 - yy0);
   
    if(dx>dy)
    {
        k=dx;
    }
    else
    {
        k=dy;
    }
    
    dx = (xx1 - xx0)/ k;
    dy = (yy1 - yy0)/ k;

    float xx = xx0;
    float yy = yy0;
   
    glBegin(GL_POINTS);  // Begin drawing points
    glPointSize(1.0);    // Set point size to 1.0
    glVertex2d(round(xx), round(yy));  // Draw the first point
    glEnd();             // End drawing points
   
    while(i<=k)
    {
        switch(type)
        {
            case 1:  // For simple line
                glBegin(GL_POINTS);
                glPointSize(1.0); 
                glVertex2d(xx, yy);
                glEnd();
                break;
            case 2:  // For dotted line
                glBegin(GL_POINTS);
                glPointSize(1.0); 
                if(i%5==0)
                {
                    glVertex2d(xx, yy);
                }
                glEnd();
                break;
            case 3:  // For dashed line
                if(i%5==0)
                {
                    s=1-s;
                }
                
                if(s==0){
                    glBegin(GL_POINTS);
                     glPointSize(1.0); 
                     glVertex2d(xx, yy);
                     glEnd();
                }
                break;
            case 4:  // For solid line
                glBegin(GL_POINTS);
                glPointSize(5.0); 
                glVertex2d(xx, yy);
                glEnd();
                break;
            }   
            xx += dx;
            yy+= dy;
            i++;
    }
    glFlush();  // Flush the drawing commands
}

// Function to draw a boat
void drawBoat()
{
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

    glColor3f(1.0, 1.0, 1.0);  // Set color to white for boat

    // Draw boat body
    drawLine(-100, -100, 100, -100, 1);
    drawLine(100, -100, 200, 0, 1);
    drawLine(200, 0, -200, 0, 1);
    drawLine(-200, 0, -100, -100, 1);

    // Draw mast
    drawLine(-150, 0, -150, 150, 1);

    // Draw sail
    drawLine(-150, 100, -150, 150, 1);
    drawLine(-150, 150, -50, 130, 1);
    drawLine(-150, 100, -50, 130, 1);

    glFlush();  // Flush the drawing commands
}

// Function to handle mouse clicks
void myMouse(int button, int state, int xx, int yy)
{
    if(state == GLUT_DOWN){
        if (button == GLUT_LEFT_BUTTON )
        {
            if(currentMenuItem==5)  // If boat is selected
            {
                drawBoat();  // Draw the boat
            }
            else
            {
                if (!isDrawing)
                {
                    xx0 = -(h/2)+xx;
                    yy0 =  (h/2)-yy;
                    isDrawing = true;
                }
                else
                {
                    xx1 = -(h/2)+xx;
                    yy1 = (h/2)-yy;
                    drawLine(xx0, yy0, xx1, yy1, currentMenuItem);
                    isDrawing = false;
                }
            }
           
        }
        else if (button == GLUT_RIGHT_BUTTON)
        {
            glutCreateMenu(menu);  // Create menu
            glutAddMenuEntry("Simple Line", 1);
            glutAddMenuEntry("Dotted Line", 2);
            glutAddMenuEntry("Dashed Line", 3);
            glutAddMenuEntry("Solid Line", 4);
            glutAddMenuEntry("Boat", 5);
            glutAttachMenu(GLUT_RIGHT_BUTTON);  // Attach menu to right mouse button
        }
    }
}

// Function to handle display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
    glFlush();                      // Flush the drawing commands
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitWindowPosition(400, 200);  // Set the window position
    glutInitWindowSize(900, 900);      // Set the window size

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  // Set the display mode
    glutCreateWindow("Drawing Lines");             // Create the window

    glutMouseFunc(myMouse);  // Register the mouse function
    myInit();                // Initialize OpenGL settings
    glutDisplayFunc(display);  // Register the display function

    glutMainLoop();  

    return 0;
}
