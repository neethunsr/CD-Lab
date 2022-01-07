#include <stdio.h>
#include <GL/glut.h>

const int MAX_POINTS = 20;
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
    gluOrtho2D(-300.0, 300.0, -300.0, 300.0);
}

// Returns x - value of point of intersection of two
// lines

int x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
    int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    return num / den;
}

// Returns y - value of point of intersection of
// two lines

int y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int num = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
    int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    return num / den;
}
int poly_size = 3;
int poly_points[20][2] = {{-10, -10}, {170, 90}, {5, 60}};
int clipper_size = 4;
int clipper_points[][2] = {{10, 10}, {10, 70}, {80, 70}, {80, 10}};

void clip(int x1, int y1, int x2, int y2)
{
    int new_points[MAX_POINTS][2], new_poly_size = 0;
    // ( ix , iy ) ,( kx , ky ) are the co - ordinate values of
    // the points
    // printf (" clip called \ n ") ;
    for (int i = 0; i < poly_size; i++)
    {
        // printf ("% d \ n " , new_poly_size ) ;
        // i and k form a line in polygon
        int k = (i + 1) % poly_size;
        int ix = poly_points[i][0], iy = poly_points[i][1];
        int kx = poly_points[k][0], ky = poly_points[k][1];
        // Calculating position of first point
        // w . r . t . clipper line
        int i_pos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);
        // Calculating position of second point
        // w . r . t . clipper line
        int k_pos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);
        // Case 1 : When both points are inside
        if (i_pos < 0 && k_pos < 0)
        {
            // Only second point is added
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        }
        // Case 2: When only first point is outside
        else if (i_pos >= 0 && k_pos < 0)
        {
            // Point of intersection with edge
            // and the second point is added
            new_points[new_poly_size][0] = x_intersect(x1,
                                                       y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1,
                                                       y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        }
        // Case 3: When only second point is outside
        else if (i_pos < 0 && k_pos >= 0)
        {
            // Only point of intersection with edge is added
            new_points[new_poly_size][0] = x_intersect(x1,
                                                       y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1,
                                                       y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
        }
        // Case 4: When both points are outside
        else
        {
            // No points are added
        }
    }
    // Copying new points into original array
    // and changing the no . of vertices
    poly_size = new_poly_size;
    for (int i = 0; i < poly_size; i++)
    {
        poly_points[i][0] = new_points[i][0];
        poly_points[i][1] = new_points[i][1];
    }
}
void original()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-300.0f, 0.0f);
    glVertex2f(300.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0f, -300.0f);
    glVertex2f(0.0f, 300.0f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.5, 0.4);
    for (int i = 0; i < poly_size; i++)
    {
        glVertex2i(poly_points[i][0], poly_points[i][1]);
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.2, 0.1);
    glVertex2i(clipper_points[0][0], clipper_points[0][1]);
    glVertex2i(clipper_points[1][0], clipper_points[1][1]);
    glVertex2i(clipper_points[2][0], clipper_points[2][1]);
    glVertex2i(clipper_points[3][0], clipper_points[3][1]);
    glEnd();
    glFlush();
}
// Implements S u t h e r l a n d Hodgman algorithm
void suthHodgClip()
{
    for (int i = 0; i < clipper_size; i++)
    {
        int k = (i + 1) % clipper_size;
        // We pass the current array of vertices , it ’s size
        // and the end points of the selected clipper line
        clip(clipper_points[i][0], clipper_points[i][1],
             clipper_points[k][0], clipper_points[k][1]);
    }
    // printf (" here % d " , poly_size ) ;
    // for ( int i =0; i < poly_size ; i ++)
    // {
    // printf ("% d ,% d \ n " , poly_points [ i ][0] , poly_points [ i
    //][1]) ;
    // }
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-300.0f, 0.0f);
    glVertex2f(300.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0f, -300.0f);
    glVertex2f(0.0f, 300.0f);
    glEnd();
    // i and k are two consecutive index
    // Printing vertices of clipped polygon
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.5, 0.4);
    for (int i = 0; i < poly_size; i++)
    {
        glVertex2i(poly_points[i][0], poly_points[i][1]);
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.2, 0.1);
    glVertex2i(clipper_points[0][0], clipper_points[0][1]);
    glVertex2i(clipper_points[1][0], clipper_points[1][1]);
    glVertex2i(clipper_points[2][0], clipper_points[2][1]);
    glVertex2i(clipper_points[3][0], clipper_points[3][1]);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow(" Before Clipping ");
    myInit();
    glutDisplayFunc(original);
    glutCreateWindow(" After Clipping ");
    myInit();
    glutDisplayFunc(suthHodgClip);
    glutMainLoop();
    // suthHodgClip () ;
    return 0;
}