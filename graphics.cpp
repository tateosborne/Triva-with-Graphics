#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include "Quiz.h"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

enum screens {
    welcome,
    quizScreens,
    summary
};
enum quiz {
    quiz1,
    quiz2
};
enum question {
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten
};

GLdouble width, height;
int wd;
const int MAX_POINTS = 10;
int points = 0;
screens currentScreen = welcome;

const color white(1, 1, 1);
const color black(0, 0, 0);
const color lightGrey(150/255.0, 150/255.0, 150/255.0);
const color darkGrey(128/255.0, 128/255.0, 128/255.0);

Quiz q;
Rect title(black, {400, 250}, {100, 25}, "~ THE QUIZ WHIZ ~");
Rect directions(black, {400, 350}, {100, 25}, "Choose Quiz or Quiz 2");
Rect quizOneChoice(lightGrey, {250, 500}, {200, 100}, "Quiz 1");
Rect quizTwoChoice(lightGrey, {550, 500}, {200, 100}, "Quiz 2");

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
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        title.drawText();
        directions.drawText();
        quizOneChoice.drawText();
        quizTwoChoice.drawText();
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {

    if (currentScreen == welcome &&
        x < 150 && x > 350 && y < 450 && y > 550) {
        quizOneChoice.setColor(darkGrey);
    }

    if (currentScreen == welcome &&
        x < 450 && x > 650 && y < 450 && y > 550) {
        quizOneChoice.setColor(darkGrey);
    }

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

    wd = glutCreateWindow("THE QUIZ WHIZ");

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