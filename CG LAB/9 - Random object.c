/*
9. Program to create a random object and to implement mouse interactions
*/
#include <GL/glut.h>
#include <stdio.h>

void init() {
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mouse and Keyboard Operations");
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500, 500, 0);
}

void drawPoint(int x, int y) {
    glColor3f(1, 0, 0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void drawLine(int x, int y) {
    glColor3f(0, 0, 1);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(x - 25, y);
    glVertex2f(x + 25, y);
    glEnd();
    glFlush();
}

void drawTriangle(int x, int y) {
    glColor3f(1, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y - 10);
    glVertex2f(x - 10, y + 10);
    glVertex2f(x + 10, y + 10);
    glEnd();
    glFlush();
}

void drawSquare(int x, int y) {
    glColor3f(0, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x - 10, y + 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 10, y - 10);
    glEnd();
    glFlush();
}

void drawPentagon(int x, int y) {
    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y - 15);
    glVertex2f(x - 10, y - 5);
    glVertex2f(x - 10, y + 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 10, y - 5);
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        drawPoint(x, y);
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        drawLine(x, y);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 't' || key == 'T')
        drawTriangle(x, y);
    if (key == 's' || key == 'S')
        drawSquare(x, y);
    if (key == 'p' || key == 'P')
        drawPentagon(x, y);
}

void display() {
    glFlush();
}

int main(int argc, char *argv[]) {
    printf("Mouse Functions :\n\tLEFT CLICK - Point\n\tRIGHT CLICK - Line\n");
    printf("Keyboard Functions :\n\tT or t - Triangle\n\tS or s - Square\n\tP or p - Pentagon\n");

    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
