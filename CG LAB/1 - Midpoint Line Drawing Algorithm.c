/*
1. Program to implement Midpoint Line Algorithm.
   The line coordinates should be specified by the user.
*/

#include <GL/glut.h>
#include <stdio.h>

int x00, y00, x01, y01;

void init() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500, 500, -500, 500);
}

void writepixel(int x, int y) {
    glPointSize(5);
    glBegin(GL_POINTS);
        glColor3f(0, 0, 0);
        glVertex2f(x, y);
    glEnd();
    glFlush();
}

void display() {
    int x, y;
    float dx = x01 - x00;
    float dy = y01 - y00;
    float d = 2 * dy - dx;
    float incrE = 2 * dy;
    float incrNE = 2 * (dy - dx);

    x = x00;
    y = y00;

    writepixel(x, y);

    while (x < x01) {
        if (d <= 0) {
            d += incrE;
            x++;
        } else {
            d += incrNE;
            x++;
            y++;
        }
        writepixel(x, y);
    }
}

int main(int argc, char *argv[]) {
    printf("Enter the values:\n");
    printf("x0 = "); scanf("%d", &x00);
    printf("y0 = "); scanf("%d", &y00);
    printf("x1 = "); scanf("%d", &x01);
    printf("y1 = "); scanf("%d", &y01);

    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Midpoint Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
