#include "graphics.h"
#include "rect.h"
#include "Quiz.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

enum screens {
    welcome,
    quizScreens,
    summary
};
enum questionNumber {
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
int i = 0;
screens currentScreen = welcome;
questionNumber currentQuestion = one;

const color white(1, 1, 1);
const color black(0, 0, 0);
const color steelBlue(70/255.0, 130/255.0, 180/255.0);
const color darkerSteelBlue(40/255.0, 100/255.0, 150/255.0);
const color green(0, 0.5, 0);
const color red(0.5, 0, 0);
color buttonColorA = steelBlue;
color buttonColorB = steelBlue;
color buttonColorC = steelBlue;
color buttonColorD = steelBlue;

Rect title(black, {400, 250}, {100, 25}, "~ THE QUIZ WHIZ ~");
Rect directions(black, {400, 350}, {100, 25}, "Ten questions, ten points!");
Rect toBegin(black, {400, 600}, {200, 100}, "Press b to begin!");

dimensions mainRectangle(300, 50);

char choice = 'y';

vector<Question> quizQuestions;

void initQuestions() {
    quizQuestions.clear();

    // Open the file
    ifstream inFile("../QuizData1.txt");

    // Read in the title and number of questions
    int numQuestions = 0;
    string newline;

    // Read in the questions
    Question q;
    string message = "";
    int number = 0;
    bool correct = false;
    while (inFile && quizQuestions.size() < 10) {
        // Question Prompt
        getline(inFile, message);
        q.setPrompt(message);

        // Clear Answers
        q.clearAnswers();

        // Answers
        for (int i = 0; i < 4; ++i) {
            // Read text
            getline(inFile, message);
            // Read correct
            inFile >> correct;
            getline(inFile, newline);
            // Add answer to question
            q.addAnswer(message, correct);
        }

        quizQuestions.push_back(q);
    }
    inFile.close();
}

void init() {
    width = 800;
    height = 800;
    srand(time(nullptr));
    initQuestions();
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
        toBegin.drawText();
    }
    if (currentScreen == quizScreens) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        Rect pointsBox(black, {725, 50}, {50, 50}, "Score: " + to_string(points) + "/" + to_string(i));
        pointsBox.drawText();

        if (currentQuestion == one) {

            Rect theQuestion(black, {400, 200}, {100, 25},
                             "1. " + quizQuestions[0].getPrompt());
            theQuestion.drawText();
            // First choice
            Rect buttonALC(buttonColorA, 50, 425);
            Rect buttonARC(buttonColorA, 350, 425);
            Rect buttonAMR(buttonColorA, {200, 425}, mainRectangle, quizQuestions[0].getAnswer(0).text);
            buttonALC.drawDiamond(25, 25);
            buttonARC.drawDiamond(25, 25);
            buttonAMR.drawText();

            // Second choice
            Rect buttonBLC(buttonColorB, 450, 425);
            Rect buttonBRC(buttonColorB, 750, 425);
            Rect buttonBMR(buttonColorB, {600, 425}, mainRectangle, quizQuestions[0].getAnswer(1).text);
            buttonBLC.drawDiamond(25, 25);
            buttonBRC.drawDiamond(25, 25);
            buttonBMR.drawText();

            // Third choice
            Rect buttonCLC(buttonColorC, 50, 525);
            Rect buttonCRC(buttonColorC, 350, 525);
            Rect buttonCMR(buttonColorC, {200, 525}, mainRectangle, quizQuestions[0].getAnswer(2).text);
            buttonCLC.drawDiamond(25, 25);
            buttonCRC.drawDiamond(25, 25);
            buttonCMR.drawText();

            // Fourth choice
            Rect buttonDLC(buttonColorD, 450, 525);
            Rect buttonDRC(buttonColorD, 750, 525);
            Rect buttonDMR(buttonColorD, {600, 525}, mainRectangle, quizQuestions[0].getAnswer(3).text);
            buttonDLC.drawDiamond(25, 25);
            buttonDRC.drawDiamond(25, 25);
            buttonDMR.drawText();
        }
        if (currentQuestion == two) {
            Rect theQuestion(black, {400, 200}, {100, 25},
                             "2. " + quizQuestions[1].getPrompt());
            theQuestion.drawText();
            // First choice
            Rect buttonALC(buttonColorA, 50, 425);
            Rect buttonARC(buttonColorA, 350, 425);
            Rect buttonAMR(buttonColorA, {200, 425}, mainRectangle, quizQuestions[1].getAnswer(0).text);
            buttonALC.drawDiamond(25, 25);
            buttonARC.drawDiamond(25, 25);
            buttonAMR.drawText();

            // Second choice
            Rect buttonBLC(buttonColorB, 450, 425);
            Rect buttonBRC(buttonColorB, 750, 425);
            Rect buttonBMR(buttonColorB, {600, 425}, mainRectangle, quizQuestions[1].getAnswer(1).text);
            buttonBLC.drawDiamond(25, 25);
            buttonBRC.drawDiamond(25, 25);
            buttonBMR.drawText();

            // Third choice
            Rect buttonCLC(buttonColorC, 50, 525);
            Rect buttonCRC(buttonColorC, 350, 525);
            Rect buttonCMR(buttonColorC, {200, 525}, mainRectangle, quizQuestions[1].getAnswer(2).text);
            buttonCLC.drawDiamond(25, 25);
            buttonCRC.drawDiamond(25, 25);
            buttonCMR.drawText();

            // Fourth choice
            Rect buttonDLC(buttonColorD, 450, 525);
            Rect buttonDRC(buttonColorD, 750, 525);
            Rect buttonDMR(buttonColorD, {600, 525}, mainRectangle, quizQuestions[1].getAnswer(3).text);
            buttonDLC.drawDiamond(25, 25);
            buttonDRC.drawDiamond(25, 25);
            buttonDMR.drawText();
        }
        if (currentQuestion == three) {
            Rect theQuestion(black, {400, 200}, {100, 25},
                             "3. " + quizQuestions[2].getPrompt());
            theQuestion.drawText();
            // First choice
            Rect buttonALC(buttonColorA, 50, 425);
            Rect buttonARC(buttonColorA, 350, 425);
            Rect buttonAMR(buttonColorA, {200, 425}, mainRectangle, quizQuestions[2].getAnswer(0).text);
            buttonALC.drawDiamond(25, 25);
            buttonARC.drawDiamond(25, 25);
            buttonAMR.drawText();

            // Second choice
            Rect buttonBLC(buttonColorB, 450, 425);
            Rect buttonBRC(buttonColorB, 750, 425);
            Rect buttonBMR(buttonColorB, {600, 425}, mainRectangle, quizQuestions[2].getAnswer(1).text);
            buttonBLC.drawDiamond(25, 25);
            buttonBRC.drawDiamond(25, 25);
            buttonBMR.drawText();

            // Third choice
            Rect buttonCLC(buttonColorC, 50, 525);
            Rect buttonCRC(buttonColorC, 350, 525);
            Rect buttonCMR(buttonColorC, {200, 525}, mainRectangle, quizQuestions[2].getAnswer(2).text);
            buttonCLC.drawDiamond(25, 25);
            buttonCRC.drawDiamond(25, 25);
            buttonCMR.drawText();

            // Fourth choice
            Rect buttonDLC(buttonColorD, 450, 525);
            Rect buttonDRC(buttonColorD, 750, 525);
            Rect buttonDMR(buttonColorD, {600, 525}, mainRectangle, quizQuestions[2].getAnswer(3).text);
            buttonDLC.drawDiamond(25, 25);
            buttonDRC.drawDiamond(25, 25);
            buttonDMR.drawText();
        }
        if (currentQuestion == four) {
            Rect theQuestion(black, {400, 200}, {100, 25},
                             "4. " + quizQuestions[3].getPrompt());
            theQuestion.drawText();
            // First choice
            Rect buttonALC(buttonColorA, 50, 425);
            Rect buttonARC(buttonColorA, 350, 425);
            Rect buttonAMR(buttonColorA, {200, 425}, mainRectangle, quizQuestions[3].getAnswer(0).text);
            buttonALC.drawDiamond(25, 25);
            buttonARC.drawDiamond(25, 25);
            buttonAMR.drawText();

            // Second choice
            Rect buttonBLC(buttonColorB, 450, 425);
            Rect buttonBRC(buttonColorB, 750, 425);
            Rect buttonBMR(buttonColorB, {600, 425}, mainRectangle, quizQuestions[3].getAnswer(1).text);
            buttonBLC.drawDiamond(25, 25);
            buttonBRC.drawDiamond(25, 25);
            buttonBMR.drawText();

            // Third choice
            Rect buttonCLC(buttonColorC, 50, 525);
            Rect buttonCRC(buttonColorC, 350, 525);
            Rect buttonCMR(buttonColorC, {200, 525}, mainRectangle, quizQuestions[3].getAnswer(2).text);
            buttonCLC.drawDiamond(25, 25);
            buttonCRC.drawDiamond(25, 25);
            buttonCMR.drawText();

            // Fourth choice
            Rect buttonDLC(buttonColorD, 450, 525);
            Rect buttonDRC(buttonColorD, 750, 525);
            Rect buttonDMR(buttonColorD, {600, 525}, mainRectangle, quizQuestions[3].getAnswer(3).text);
            buttonDLC.drawDiamond(25, 25);
            buttonDRC.drawDiamond(25, 25);
            buttonDMR.drawText();
        }
        if (currentQuestion == five) {
            Rect theQuestion(black, {400, 200}, {100, 25},
                             "5. " + quizQuestions[4].getPrompt());
            theQuestion.drawText();
            // First choice
            Rect buttonALC(buttonColorA, 50, 425);
            Rect buttonARC(buttonColorA, 350, 425);
            Rect buttonAMR(buttonColorA, {200, 425}, mainRectangle, quizQuestions[4].getAnswer(0).text);
            buttonALC.drawDiamond(25, 25);
            buttonARC.drawDiamond(25, 25);
            buttonAMR.drawText();

            // Second choice
            Rect buttonBLC(buttonColorB, 450, 425);
            Rect buttonBRC(buttonColorB, 750, 425);
            Rect buttonBMR(buttonColorB, {600, 425}, mainRectangle, quizQuestions[4].getAnswer(1).text);
            buttonBLC.drawDiamond(25, 25);
            buttonBRC.drawDiamond(25, 25);
            buttonBMR.drawText();

            // Third choice
            Rect buttonCLC(buttonColorC, 50, 525);
            Rect buttonCRC(buttonColorC, 350, 525);
            Rect buttonCMR(buttonColorC, {200, 525}, mainRectangle, quizQuestions[4].getAnswer(2).text);
            buttonCLC.drawDiamond(25, 25);
            buttonCRC.drawDiamond(25, 25);
            buttonCMR.drawText();

            // Fourth choice
            Rect buttonDLC(buttonColorD, 450, 525);
            Rect buttonDRC(buttonColorD, 750, 525);
            Rect buttonDMR(buttonColorD, {600, 525}, mainRectangle, quizQuestions[4].getAnswer(3).text);
            buttonDLC.drawDiamond(25, 25);
            buttonDRC.drawDiamond(25, 25);
            buttonDMR.drawText();
        }
        if (currentQuestion == six) {
            Rect theQuestion(black, {400, 200}, {100, 25},
                             "6. " + quizQuestions[5].getPrompt());
            theQuestion.drawText();
            // First choice
            Rect buttonALC(buttonColorA, 50, 425);
            Rect buttonARC(buttonColorA, 350, 425);
            Rect buttonAMR(buttonColorA, {200, 425}, mainRectangle, quizQuestions[5].getAnswer(0).text);
            buttonALC.drawDiamond(25, 25);
            buttonARC.drawDiamond(25, 25);
            buttonAMR.drawText();

            // Second choice
            Rect buttonBLC(buttonColorB, 450, 425);
            Rect buttonBRC(buttonColorB, 750, 425);
            Rect buttonBMR(buttonColorB, {600, 425}, mainRectangle, quizQuestions[5].getAnswer(1).text);
            buttonBLC.drawDiamond(25, 25);
            buttonBRC.drawDiamond(25, 25);
            buttonBMR.drawText();

            // Third choice
            Rect buttonCLC(buttonColorC, 50, 525);
            Rect buttonCRC(buttonColorC, 350, 525);
            Rect buttonCMR(buttonColorC, {200, 525}, mainRectangle, quizQuestions[5].getAnswer(2).text);
            buttonCLC.drawDiamond(25, 25);
            buttonCRC.drawDiamond(25, 25);
            buttonCMR.drawText();

            // Fourth choice
            Rect buttonDLC(buttonColorD, 450, 525);
            Rect buttonDRC(buttonColorD, 750, 525);
            Rect buttonDMR(buttonColorD, {600, 525}, mainRectangle, quizQuestions[5].getAnswer(3).text);
            buttonDLC.drawDiamond(25, 25);
            buttonDRC.drawDiamond(25, 25);
            buttonDMR.drawText();
        }
        if (currentQuestion == seven) {
            Rect theQuestion(black, {400, 200}, {100, 25},
                             "7. " + quizQuestions[6].getPrompt());
            theQuestion.drawText();
            // First choice
            Rect buttonALC(buttonColorA, 50, 425);
            Rect buttonARC(buttonColorA, 350, 425);
            Rect buttonAMR(buttonColorA, {200, 425}, mainRectangle, quizQuestions[6].getAnswer(0).text);
            buttonALC.drawDiamond(25, 25);
            buttonARC.drawDiamond(25, 25);
            buttonAMR.drawText();

            // Second choice
            Rect buttonBLC(buttonColorB, 450, 425);
            Rect buttonBRC(buttonColorB, 750, 425);
            Rect buttonBMR(buttonColorB, {600, 425}, mainRectangle, quizQuestions[6].getAnswer(1).text);
            buttonBLC.drawDiamond(25, 25);
            buttonBRC.drawDiamond(25, 25);
            buttonBMR.drawText();

            // Third choice
            Rect buttonCLC(buttonColorC, 50, 525);
            Rect buttonCRC(buttonColorC, 350, 525);
            Rect buttonCMR(buttonColorC, {200, 525}, mainRectangle, quizQuestions[6].getAnswer(2).text);
            buttonCLC.drawDiamond(25, 25);
            buttonCRC.drawDiamond(25, 25);
            buttonCMR.drawText();

            // Fourth choice
            Rect buttonDLC(buttonColorD, 450, 525);
            Rect buttonDRC(buttonColorD, 750, 525);
            Rect buttonDMR(buttonColorD, {600, 525}, mainRectangle, quizQuestions[6].getAnswer(3).text);
            buttonDLC.drawDiamond(25, 25);
            buttonDRC.drawDiamond(25, 25);
            buttonDMR.drawText();
        }
        if (currentQuestion == eight) {
            Rect theQuestion(black, {400, 200}, {100, 25},
                             "8. " + quizQuestions[7].getPrompt());
            theQuestion.drawText();
            // First choice
            Rect buttonALC(buttonColorA, 50, 425);
            Rect buttonARC(buttonColorA, 350, 425);
            Rect buttonAMR(buttonColorA, {200, 425}, mainRectangle, quizQuestions[7].getAnswer(0).text);
            buttonALC.drawDiamond(25, 25);
            buttonARC.drawDiamond(25, 25);
            buttonAMR.drawText();

            // Second choice
            Rect buttonBLC(buttonColorB, 450, 425);
            Rect buttonBRC(buttonColorB, 750, 425);
            Rect buttonBMR(buttonColorB, {600, 425}, mainRectangle, quizQuestions[7].getAnswer(1).text);
            buttonBLC.drawDiamond(25, 25);
            buttonBRC.drawDiamond(25, 25);
            buttonBMR.drawText();

            // Third choice
            Rect buttonCLC(buttonColorC, 50, 525);
            Rect buttonCRC(buttonColorC, 350, 525);
            Rect buttonCMR(buttonColorC, {200, 525}, mainRectangle, quizQuestions[7].getAnswer(2).text);
            buttonCLC.drawDiamond(25, 25);
            buttonCRC.drawDiamond(25, 25);
            buttonCMR.drawText();

            // Fourth choice
            Rect buttonDLC(buttonColorD, 450, 525);
            Rect buttonDRC(buttonColorD, 750, 525);
            Rect buttonDMR(buttonColorD, {600, 525}, mainRectangle, quizQuestions[7].getAnswer(3).text);
            buttonDLC.drawDiamond(25, 25);
            buttonDRC.drawDiamond(25, 25);
            buttonDMR.drawText();
        }
        if (currentQuestion == nine) {
            Rect theQuestion(black, {400, 200}, {100, 25},
                             "9. " + quizQuestions[8].getPrompt());
            theQuestion.drawText();
            // First choice
            Rect buttonALC(buttonColorA, 50, 425);
            Rect buttonARC(buttonColorA, 350, 425);
            Rect buttonAMR(buttonColorA, {200, 425}, mainRectangle, quizQuestions[8].getAnswer(0).text);
            buttonALC.drawDiamond(25, 25);
            buttonARC.drawDiamond(25, 25);
            buttonAMR.drawText();

            // Second choice
            Rect buttonBLC(buttonColorB, 450, 425);
            Rect buttonBRC(buttonColorB, 750, 425);
            Rect buttonBMR(buttonColorB, {600, 425}, mainRectangle, quizQuestions[8].getAnswer(1).text);
            buttonBLC.drawDiamond(25, 25);
            buttonBRC.drawDiamond(25, 25);
            buttonBMR.drawText();

            // Third choice
            Rect buttonCLC(buttonColorC, 50, 525);
            Rect buttonCRC(buttonColorC, 350, 525);
            Rect buttonCMR(buttonColorC, {200, 525}, mainRectangle, quizQuestions[8].getAnswer(2).text);
            buttonCLC.drawDiamond(25, 25);
            buttonCRC.drawDiamond(25, 25);
            buttonCMR.drawText();

            // Fourth choice
            Rect buttonDLC(buttonColorD, 450, 525);
            Rect buttonDRC(buttonColorD, 750, 525);
            Rect buttonDMR(buttonColorD, {600, 525}, mainRectangle, quizQuestions[8].getAnswer(3).text);
            buttonDLC.drawDiamond(25, 25);
            buttonDRC.drawDiamond(25, 25);
            buttonDMR.drawText();
        }
        if (currentQuestion == ten) {
            Rect theQuestion(black, {400, 200}, {100, 25},
                             "10. " + quizQuestions[9].getPrompt());
            theQuestion.drawText();
            // First choice
            Rect buttonALC(buttonColorA, 50, 425);
            Rect buttonARC(buttonColorA, 350, 425);
            Rect buttonAMR(buttonColorA, {200, 425}, mainRectangle, quizQuestions[9].getAnswer(0).text);
            buttonALC.drawDiamond(25, 25);
            buttonARC.drawDiamond(25, 25);
            buttonAMR.drawText();

            // Second choice
            Rect buttonBLC(buttonColorB, 450, 425);
            Rect buttonBRC(buttonColorB, 750, 425);
            Rect buttonBMR(buttonColorB, {600, 425}, mainRectangle, quizQuestions[9].getAnswer(1).text);
            buttonBLC.drawDiamond(25, 25);
            buttonBRC.drawDiamond(25, 25);
            buttonBMR.drawText();

            // Third choice
            Rect buttonCLC(buttonColorC, 50, 525);
            Rect buttonCRC(buttonColorC, 350, 525);
            Rect buttonCMR(buttonColorC, {200, 525}, mainRectangle, quizQuestions[9].getAnswer(2).text);
            buttonCLC.drawDiamond(25, 25);
            buttonCRC.drawDiamond(25, 25);
            buttonCMR.drawText();

            // Fourth choice
            Rect buttonDLC(buttonColorD, 450, 525);
            Rect buttonDRC(buttonColorD, 750, 525);
            Rect buttonDMR(buttonColorD, {600, 525}, mainRectangle, quizQuestions[9].getAnswer(3).text);
            buttonDLC.drawDiamond(25, 25);
            buttonDRC.drawDiamond(25, 25);
            buttonDMR.drawText();
        }
    }
    if (currentScreen == summary) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        Rect thanks(black, {400, 300}, {200, 50}, "Thanks for playing!");
        Rect score(black, {400, 400}, {200, 50}, "You scored " + to_string(points) + "/" + to_string(MAX_POINTS));
        thanks.drawText();
        score.drawText();
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
    // b
    if (key == 98 && currentScreen == welcome) {
        currentScreen = quizScreens;
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {

    if (currentScreen == quizScreens &&
            x > 25 && x < 375 && y > 400 && y < 450) {
        buttonColorA = darkerSteelBlue;
    } else {
        buttonColorA = steelBlue;
    }
    if (currentScreen == quizScreens &&
            x > 425 && x < 775 && y > 400 && y < 450) {
        buttonColorB = darkerSteelBlue;
    } else {
        buttonColorB = steelBlue;
    }
    if (currentScreen == quizScreens &&
            x > 25 && x < 375 && y > 500 && y < 550) {
        buttonColorC = darkerSteelBlue;
    } else {
        buttonColorC = steelBlue;
    }
    if (currentScreen == quizScreens &&
            x > 425 && x < 775 && y > 500 && y < 550) {
        buttonColorD = darkerSteelBlue;
    } else {
        buttonColorD = steelBlue;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    // QUIZ
    if (currentScreen == quizScreens &&
            x > 25 && x < 375 && y > 400 && y < 450 &&
            button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (quizQuestions[i].getAnswer(0).correct) {
            buttonColorA = green;
            points++;
        } else {
            buttonColorA = red;
        }
        if (currentQuestion == one) {
            currentQuestion = two;
            i++;
        } else if (currentQuestion == two) {
            currentQuestion = three;
            i++;
        } else if (currentQuestion == three) {
            currentQuestion = four;
            i++;
        } else if (currentQuestion == four) {
            currentQuestion = five;
            i++;
        } else if (currentQuestion == five) {
            currentQuestion = six;
            i++;
        } else if (currentQuestion == six) {
            currentQuestion = seven;
            i++;
        } else if (currentQuestion == seven) {
            currentQuestion = eight;
            i++;
        } else if (currentQuestion == eight) {
            currentQuestion = nine;
            i++;
        } else if (currentQuestion == nine) {
            currentQuestion = ten;
            i++;
        } else if (currentQuestion == ten) {
            currentScreen = summary;
            i++;
        }
    }
    if (currentScreen == quizScreens &&
            x > 425 && x < 775 && y > 400 && y < 450 &&
            button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (quizQuestions[i].getAnswer(1).correct) {
            buttonColorB = green;
            points++;
        } else {
            buttonColorB = red;
        }
        if (currentQuestion == one) {
            currentQuestion = two;
            i++;
        } else if (currentQuestion == two) {
            currentQuestion = three;
            i++;
        } else if (currentQuestion == three) {
            currentQuestion = four;
            i++;
        } else if (currentQuestion == four) {
            currentQuestion = five;
            i++;
        } else if (currentQuestion == five) {
            currentQuestion = six;
            i++;
        } else if (currentQuestion == six) {
            currentQuestion = seven;
            i++;
        } else if (currentQuestion == seven) {
            currentQuestion = eight;
            i++;
        } else if (currentQuestion == eight) {
            currentQuestion = nine;
            i++;
        } else if (currentQuestion == nine) {
            currentQuestion = ten;
            i++;
        } else if (currentQuestion == ten) {
            currentScreen = summary;
        }
    }
    if (currentScreen == quizScreens &&
            x > 25 && x < 375 && y > 500 && y < 550 &&
            button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (quizQuestions[i].getAnswer(2).correct) {
            buttonColorC = green;
            points++;
        } else {
            buttonColorC = red;
        }
        if (currentQuestion == one) {
            currentQuestion = two;
            i++;
        } else if (currentQuestion == two) {
            currentQuestion = three;
            i++;
        } else if (currentQuestion == three) {
            currentQuestion = four;
            i++;
        } else if (currentQuestion == four) {
            currentQuestion = five;
            i++;
        } else if (currentQuestion == five) {
            currentQuestion = six;
            i++;
        } else if (currentQuestion == six) {
            currentQuestion = seven;
            i++;
        } else if (currentQuestion == seven) {
            currentQuestion = eight;
            i++;
        } else if (currentQuestion == eight) {
            currentQuestion = nine;
            i++;
        } else if (currentQuestion == nine) {
            currentQuestion = ten;
            i++;
        } else if (currentQuestion == ten) {
            currentScreen = summary;
        }
    }
    if (currentScreen == quizScreens &&
            x > 425 && x < 775 && y > 500 && y < 550 &&
            button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (quizQuestions[i].getAnswer(3).correct) {
            buttonColorD = green;
            points++;
        } else {
            buttonColorD = red;
        }
        if (currentQuestion == one) {
            currentQuestion = two;
            i++;
        } else if (currentQuestion == two) {
            currentQuestion = three;
            i++;
        } else if (currentQuestion == three) {
            currentQuestion = four;
            i++;
        } else if (currentQuestion == four) {
            currentQuestion = five;
            i++;
        } else if (currentQuestion == five) {
            currentQuestion = six;
            i++;
        } else if (currentQuestion == six) {
            currentQuestion = seven;
            i++;
        } else if (currentQuestion == seven) {
            currentQuestion = eight;
            i++;
        } else if (currentQuestion == eight) {
            currentQuestion = nine;
            i++;
        } else if (currentQuestion == nine) {
            currentQuestion = ten;
            i++;
        } else if (currentQuestion == ten) {
            currentScreen = summary;
        }
    }

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

    glutInitWindowSize((int) width, (int) height);
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
