#include <GL/glut.h>
#include <cmath>
float angle = 135;
float inc = 1.0;
void initialize()
{
    glClearColor(1.0, 0.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
}
void plot(int a, int b)
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(a, b);
    glEnd();
}
void drawCircle(int h, int k, int r)
{
    int x = 0, y = r;
    float d = 3 - 2 * r;
    while (x <= y)
    {
        if (d <= 0)
        {
            d = d + 4 * x + 6;
            x++;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            x++;
            y--;
        }
        plot(x + h, y + k);
        plot(-x + h, -y + k);
        plot(y + h, x + k);
        plot(-y + h, -x + k);
        plot(-y + h, x + k);
        plot(y + h, -x + k);
        plot(-x + h, y + k);
        plot(x + h, -y + k);
    }
}
void timer(int value)
{
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(50, timer, 0); // Set the next timer
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    drawCircle(0, 100, 100);
    drawCircle(0, 100, 60);
    // Draw clock numbers
    glPointSize(5);
    glBegin(GL_POINTS);
    for (int i = 1; i <= 12; ++i)
    {
        float theta = (i * 30 * 3.14159) / 180.0;
        float x = 90 * sin(theta);
        float y = 90 * cos(theta);
        glVertex2f(x, y + 100);
    }
    glEnd();
    if (angle > 225)
    {
        angle = 225;
        inc = -inc;
    }
    if (angle < 135)
    {
        angle = 135;
        inc = -inc;
    }
    angle += inc;
    double radian = angle * 3.14 / 180;
    float y2 = 150 * cos((double)radian);
    float x2 = 150 * sin((double)radian);
    drawCircle(x2, y2, 30);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(x2, y2);
    glVertex2f(0, 100);
    glVertex2f(0, 150);
    glVertex2f(0, 100);
    glVertex2f(60, 145);
    glEnd();
    glFlush();
}
void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) exit(0);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Pendulum Clock");
    initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0); // Start the timer immediately
    glutMainLoop();
    return 0;
}