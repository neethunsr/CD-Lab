#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.14159265
#define Ax 20.0
#define Ay 10.0
#define Bx 60.0
#define By 30.0
#define Cx 40.0
#define Cy 80.0

void myInit()
{
    // making background color black as first
    // 3 arguments all are 0.0
    glClearColor(0.0, 0.0, 0.0, 1.0);
    // making picture color green ( in RGB mode ) , as middle
    // argument is 1.0
    glColor3f(0.0, 1.0, 0.0);
    // breadth of picture boundary is 1 pixel
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // setting window dimension in X - and Y - direction
    gluOrtho2D(-150.0, 150.0, -150.0, 150.0);
}

int abs(int n)
{
    return ((n > 0) ? n : (n * (-1)));
}

void original()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(150.0f, 0.0f);
    glVertex2f(150.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.0f, -150.0f);
    glVertex2f(0.0f, 150.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.2, 0.3);
    glVertex3f(Ax, Ay, 0);
    glVertex3f(Bx, By, 0);
    glVertex3f(Cx, Cy, 0);
    glEnd();
    glFlush();
}

void rotate()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-150.0f, 0.0f);
    glVertex2f(150.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.0f, -150.0f);
    glVertex2f(0.0f, 150.0f);
    glEnd();
    // rotation
    float Ax1 = Bx + (Ax - Bx) * cos(-1 * PI / 2) - (Ay - By) * sin(-1 * PI / 2);
    float Ay1 = By + (Ax - Bx) * sin(-1 * PI / 2) - (Ay - By) * cos(-1 * PI / 2);
    float Bx1 = Bx + (Bx - Bx) * cos(-1 * PI / 2) - (By - By) * sin(-1 * PI / 2);
    float By1 = By + (Bx - Bx) * sin(-1 * PI / 2) - (By - By) * cos(-1 * PI / 2);
    float Cx1 = Bx + (Cx - Bx) * cos(-1 * PI / 2) - (Cy - By) * sin(-1 * PI / 2);
    float Cy1 = By + (Cx - Bx) * sin(-1 * PI / 2) - (Cy - By) * cos(-1 * PI / 2);
    glBegin(GL_TRIANGLES);
    glColor3f(0.2, 0.3, 0.1);
    glVertex3f(Ax1, Ay1, 0);
    glVertex3f(Bx1, By1, 0);
    glVertex3f(Cx1, Cy1, 0);
    glEnd();
    glFlush();
}

void scale()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-150.0f, 0.0f);
    glVertex2f(150.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.0f, -150.0f);
    glVertex2f(0.0f, 150.0f);
    glEnd();
    // scale
    float sx = 0.5, sy = 0.5;
    float Ax1 = Ax + (Ax - Ax) * sx;
    float Ay1 = Ay + (Ay - Ay) * sy;
    float Bx1 = Ax + (Bx - Ax) * sx;
    float By1 = Ay + (By - Ay) * sy;
    float Cx1 = Ax + (Cx - Ax) * sx;
    float Cy1 = Ay + (Cy - Ay) * sy;
    glBegin(GL_TRIANGLES);
    glColor3f(0.3, 0.1, 0.2);
    glVertex3f(Ax1, Ay1, 0);
    glVertex3f(Bx1, By1, 0);
    glVertex3f(Cx1, Cy1, 0);
    glEnd();
    glFlush();
}

void reflect()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-150.0f, 0.0f);
    glVertex2f(150.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.0f, -150.0f);
    glVertex2f(0.0f, 150.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.2, 0.3);
    glVertex3f(Ay, Ax, 0);
    glVertex3f(By, Bx, 0);
    glVertex3f(Cy, Cx, 0);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow(" original ");
    myInit();
    glutDisplayFunc(original);
    glutCreateWindow(" rotate ");
    myInit();
    glutDisplayFunc(rotate);
    glutCreateWindow(" scale ");
    myInit();
    glutDisplayFunc(scale);
    glutCreateWindow(" reflect ");
    myInit();
    glutDisplayFunc(reflect);
    glutMainLoop();
    return 0;
}
