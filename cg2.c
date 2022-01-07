#include <stdio.h>
#include <GL/glut.h>

// Defining region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
const int Ax = 10, Ay = 10;
const int Bx = 80, By = 10;
const int Cx = 80, Cy = 70;
const int Dx = 10, Dy = 70;

// Defining x_max , y_max and x_min , y_min for
// clipping rectangle . Since diagonal points are
// enough to define a rectangle

const int x_max = 80;
const int y_max = 70;
const int x_min = 10;
const int y_min = 10;

// Function to compute region code for a point (x , y )
int computeCode(double x, double y)
{
    // initialized as being inside
    int code = INSIDE;
    if (x < x_min) // to the left of rectangle
        code = LEFT;
    else if (x > x_max) // to the right of rectangle
        code = RIGHT;
    if (y < y_min) // below the rectangle
        code = BOTTOM;
    else if (y > y_max) // above the rectangle
        code = TOP;
    return code;
}
void myInit(void)
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

float p1, q1, p2, q2;

void beforeClip()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-150.0f, 0.0f);
    glVertex2f(150.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0f, -150.0f);
    glVertex2f(0.0f, 150.0f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.2, 0.3);
    glVertex2i(Ax, Ay);
    glVertex2i(Bx, By);
    glVertex2i(Cx, Cy);
    glVertex2i(Dx, Dy);
    glEnd();
    // all lines
    p1 = 40.0;
    q1 = 10.0;
    p2 = 60.0;
    q2 = 90.0;
    glBegin(GL_LINES);
    glColor3f(0.3, 0.2, 0.7);
    glVertex2f(p1, q1);
    glVertex2f(p2, q2);
    glEnd();
    p1 = 70.0;
    q1 = -20.0;
    p2 = 100.0;
    q2 = 30.0;
    glBegin(GL_LINES);
    glColor3f(0.3, 0.2, 0.7);
    glVertex2f(p1, q1);
    glVertex2f(p2, q2);
    glEnd();
    p1 = 30.0;
    q1 = 40.0;
    p2 = -30.0;
    q2 = -10.0;
    glBegin(GL_LINES);
    glColor3f(0.3, 0.2, 0.7);
    glVertex2f(p1, q1);
    glVertex2f(p2, q2);
    glEnd();
    glFlush();
}

int funcAccept(int accept, int code1, int code2)
{
    while (1)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            // If both endpoints lie within rectangle
            accept = 1;
            break;
        }
        else if (code1 & code2)
        {
            // If both endpoints are outside rectangle ,
            // in same region
            break;
        }
        else
        {
            // Some segment of line lies within the
            // rectangle
            int code_out;
            double x, y;
            // At least one endpoint is outside the
            // rectangle , pick it .
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;
            // Find intersection point ;
            // using formulas y = q1 + slope * ( x - p1 ) ,
            // x = p1 + (1 / slope ) * ( y - q1 )
            if (code_out & TOP)
            {
                // point is above the clip rectangle
                x = p1 + (p2 - p1) * (y_max - q1) / (q2 - q1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                // point is below the rectangle
                x = p1 + (p2 - p1) * (y_min - q1) / (q2 - q1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                // point is to the right of rectangle
                y = q1 + (q2 - q1) * (x_max - p1) / (p2 - p1);
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                // point is to the left of rectangle
                y = q1 + (q2 - q1) * (x_min - p1) / (p2 - p1);
                x = x_min;
            }
            // Now intersection point x , y is found
            // We replace point outside rectangle
            // by intersection point
            if (code_out == code1)
            {
                p1 = x;
                q1 = y;
                code1 = computeCode(p1, q1);
            }
            else
            {
                p2 = x;
                q2 = y;
                code2 = computeCode(p2, q2);
            }
        }
    }
    return accept;
}
void cohenSutherlandClip()
{
    int code1, code2, accept;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-150.0f, 0.0f);
    glVertex2f(150.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0f, -150.0f);
    glVertex2f(0.0f, 150.0f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.2, 0.3);
    glVertex2i(Ax, Ay);
    glVertex2i(Bx, By);
    glVertex2i(Cx, Cy);
    glVertex2i(Dx, Dy);
    glEnd();
    p1 = 40.0;
    q1 = 10.0;
    p2 = 60.0;
    q2 = 90.0;
    // Compute region codes for P1 , P2
    code1 = computeCode(p1, q1);
    code2 = computeCode(p2, q2);
    // Initialize line as outside the rectangular window
    accept = 0;
    accept = funcAccept(accept, code1, code2);
    if (accept)
    {
        glBegin(GL_LINES);
        glColor3f(0.3, 0.2, 0.7);
        glVertex2f(p1, q1);
        glVertex2f(p2, q2);
        glEnd();
    }
    p1 = 70.0;
    q1 = -20.0;
    p2 = 100.0;
    q2 = 30.0;
    // Compute region codes for P1 , P2
    code1 = computeCode(p1, q1);
    code2 = computeCode(p2, q2);
    // Initialize line as outside the rectangular window
    accept = 0;
    accept = funcAccept(accept, code1, code2);
    if (accept)
    {
        glBegin(GL_LINES);
        glColor3f(0.3, 0.2, 0.7);
        glVertex2f(p1, q1);
        glVertex2f(p2, q2);
        glEnd();
    }
    // Compute region codes for P1 , P2
    p1 = 30.0;
    q1 = 40.0;
    p2 = -30.0;
    q2 = -10.0;
    code1 = computeCode(p1, q1);
    code2 = computeCode(p2, q2);
    // Initialize line as outside the rectangular window
    accept = 0;
    accept = funcAccept(accept, code1, code2);
    if (accept)
    {
        glBegin(GL_LINES);
        glColor3f(0.3, 0.2, 0.7);
        glVertex2f(p1, q1);
        glVertex2f(p2, q2);
        glEnd();
    }
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    p1 = 40.0;
    q1 = 10.0;
    p2 = 60.0;
    q2 = 90.0;
    glutCreateWindow(" Before Clipping ");
    myInit();
    glutDisplayFunc(beforeClip);
    glutCreateWindow(" After Clipping ");
    myInit();
    glutDisplayFunc(cohenSutherlandClip);
    glutMainLoop();
    return 0;
}