#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include "Quiz.h"
#include <iostream>
#include <cmath>

using namespace std;

enum screens {
    welcome,
    quizScreens,
    summary
};

GLdouble width, height;
int wd;
const int MAX_POINTS = 10;
const color white(1, 1, 1);
const color black(0, 0, 0);
screens currentScreen = welcome;

Rect title(black, {400, 250}, {100, 25}, "THE QUIZ WHIZ");

void init() {
    width = 800;
    height = 800;
    srand(time(nullptr));

}

void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
    if (currentScreen == welcome) {
        title.drawText();
    }

    else if (currentScreen == quizScreens) {

    }

    else if (currentScreen == summary) {
        Rect end(black, {400, 250}, {100, 25}, "You scored" + points + "out of " + maxPoints);
        end.drawText();
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}

void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv); // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner

    wd = glutCreateWindow("QUIZ");

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}