/*
4. Program to implement the Cohen-Sutherland line-clipping algorithm.
   Allows specification of input line, clipping window, and viewport.
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

typedef int Outcode;

const int INSIDE = 0;
const int LEFT   = 1;
const int RIGHT  = 2;
const int BOTTOM = 4;
const int TOP    = 8;

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;

void init() {
    glClearColor(1, 2, 3, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

Outcode Computecode(double x, double y) {
    Outcode code = INSIDE;
    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;
    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;
    return code;
}

void CohenSutherlandline(double x0, double y0, double x1, double y1) {
    bool accept = false;
    Outcode outcode0 = Computecode(x0, y0);
    Outcode outcode1 = Computecode(x1, y1);
    double x, y;

    while (true) {
        if (!(outcode0 | outcode1)) {  // Both endpoints inside
            accept = true;
            break;
        } else if (outcode0 & outcode1) {  // Both endpoints share outside zone
            break;
        } else {
            Outcode outcodeout = outcode0 ? outcode0 : outcode1;

            if (outcodeout & TOP) {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            } else if (outcodeout & BOTTOM) {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            } else if (outcodeout & RIGHT) {
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            } else if (outcodeout & LEFT) {
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }

            if (outcodeout == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = Computecode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = Computecode(x1, y1);
            }
        }
    }

    if (accept) {
        // Draw clipping window
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(4 * xmin, 4 * ymin);
            glVertex2f(4 * xmax, 4 * ymin);
            glVertex2f(4 * xmax, 4 * ymax);
            glVertex2f(4 * xmin, 4 * ymax);
        glEnd();

        // Draw clipped line
        glBegin(GL_LINES);
            glVertex2f(4 * x0, 4 * y0);
            glVertex2f(4 * x1, 4 * y1);
        glEnd();
    }
}

void display() {
    double x0 = 60, y0 = 20, x1 = 80, y1 = 120;

    // Draw original clipping window
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();

    // Draw original line
    glBegin(GL_LINES);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
    glEnd();

    // Draw clipped line using Cohen-Sutherland
    CohenSutherlandline(x0, y0, x1, y1);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Cohen-Sutherland Line Clipping Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
