#include<iostream>
#include<GL/gl.h>
#include<GL/glu.h>
#include<cmath>
#include<GL/glut.h>

using namespace std;

void init()
{
   glClearColor(1.0, 1.0, 1.0, 0.0);                       			 // Set clear color to white
    glMatrixMode(GL_PROJECTION);                            			// Set matrix mode to projection
    glLoadIdentity();                                       
    glPointSize(4);                                         				// Set point size to 4
    glColor3f(0.0, 0.0, 0.0);                               				// Set color to black
    gluOrtho2D(0, 640, 0, 480);                             			// Set up 2D orthographic viewing region
}


void display()
{
    glColor3f(1, 1, 1);						// Set color to black
     glPointSize(2);  						//Set point size to 2
    glBegin(GL_LINES);  					// defining line segments
   
        glVertex2i(150,150);							
        glVertex2i(150,250);
    
        glVertex2i(150,150);
        glVertex2i(450,150);
    
        glVertex2i(250,150);
        glVertex2i(250,250);
    
        glVertex2i(250,250);
        glVertex2i(150,250);
    
        glVertex2i(150,250);
        glVertex2i(200,325);
    
        glVertex2i(250,250);
        glVertex2i(200,325);
        
        glVertex2i(200,325);
        glVertex2i(400,325);
    
        glVertex2i(250,250);
        glVertex2i(450,250);
    
        glVertex2i(400,325);
        glVertex2i(450,250);
    
        glVertex2i(450,250);
        glVertex2i(450,150);
    
    glEnd();  							// End defining line segments
    glFlush();  						// Force execution of OpenGL commands
}

int main(int charc, char ** charv)
{
    glutInit(&charc, charv);  					// Initialize GLUT library
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  			// Set display mode
    glutInitWindowPosition(400,100);  				// Set initial window position
    glutInitWindowSize(1000,1000);  				// Set initial window size
    glutCreateWindow("SS home");  				// Create window title
  
    init();  												
    glutDisplayFunc(display);  					// Set display callback function
    
    glutMainLoop();  						// Enter GLUT event processing loop
    return 0;  
}
