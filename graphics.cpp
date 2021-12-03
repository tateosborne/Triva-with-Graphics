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

GLdouble width, height;
int wd;
const int MAX_POINTS = 10;
int points = 0;
screens currentScreen = welcome;

const color white(1, 1, 1);
const color black(0, 0, 0);

Quiz q;
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
        q.takeQuiz("QuizData1.txt", cout, cin);

        ifstream inFile("../scene.txt");
        inFile >> noskipws;
        int xCoord = 50, yCoord = 50;
        char letter;
        bool draw;
        while (inFile >> letter) {
            draw = true;
            switch(letter) {
                case 'r': glColor3f(0.8, 0, 0); break;
                case 'g': glColor3f(0, 0.8,0); break;
                case 'b': glColor3f(0, 0, 1); break;
                case 'y': glColor3f(1, 1, 0); break;
                case 'm': glColor3f(1, 0, 1); break;
                case 'o': glColor3f(0.9, 0.3, 0); break;
                case 'k': glColor3f(0, 0, 0); break;
                case 'x': glColor3f(0.3, 0.5, 0.6); break;
                case ' ': glColor3f(1, 1, 1); break;
                default: // newline
                    draw = false;
                    xCoord = 50;
                    yCoord += SIDE_LENGTH;
            }
            if (draw) {
                glBegin(GL_QUADS);
                glVertex2i(xCoord, yCoord);
                glVertex2i(xCoord+SIDE_LENGTH, yCoord);
                glVertex2i(xCoord+SIDE_LENGTH, yCoord+SIDE_LENGTH);
                glVertex2i(xCoord, yCoord+SIDE_LENGTH);
                glEnd();
                xCoord += SIDE_LENGTH;
            }
        }
        inFile.close();
    }

    else if (currentScreen == summary) {
        Rect end(black, {400, 250}, {100, 25},
                 "You scored" + to_string(points) + "out of " + to_string(MAX_POINTS));
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
    }

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