#include "Question.h"
#include "Quiz.h"
#include <iostream>

using namespace std;

bool testQuestion();
bool testQuiz();

int main() {

    if (testQuestion()) {
        cout << "Passed all Question test cases" << endl;
    }
    if (testQuiz()) {
        cout << "Passed all Quiz test cases" << endl;
    }

    return 0;
}

bool testQuestion() {
    bool passed = true;

    Question ques;
    if (!ques.getPrompt().empty() || ques.getPoints() != 0 || ques.getNumAnswers() != 0) {
        passed = false;
        cout << "FAILED constructor test case" << endl;
    }
    ques.setPrompt("Hello, World");
    if (ques.getPrompt() != "Hello, World") {
        passed = false;
        cout << "FAILED setPrompt(*string*) test case" << endl;
    }
    ques.setPoints(3);
    if (ques.getPoints() != 3) {
        passed = false;
        cout << "FAILED setPoints(*int*) test case" << endl;
    }
    answer response;
    answer response2;
    ques.addAnswer(response);
    ques.addAnswer(response2);
    if (ques.getNumAnswers() != 2) {
        passed = false;
        cout << "FAILED addAnswer(*answer*) test case" << endl;
    }
    ques.clearAnswers();
    if (ques.getNumAnswers() != 0) {
        passed = false;
        cout << "FAILED clearAnswers() test case" << endl;
    }
    ques.addAnswer("Correct", true);
    if (!ques.isCorrect(0)) {
        passed = false;
        cout << "FAILED addAnswer(*string*, *bool*) test case" << endl;
    }
    if (!ques.removeAnswer(0)) {
        passed = false;
        cout << "FAILED removeAnswer test case where index is valid" << endl;
    }
    if (ques.removeAnswer(-1)) {
        passed = false;
        cout << "FAILED removeAnswer test case where index is invalid" << endl;
    }
    answer response3;
    response3.text = "answer123";
    response3.correct = false;
    ques.addAnswer(response3);
    if (!ques.removeAnswer("answer123")) {
        passed = false;
        cout << "FAILED removeAnswer test case where the string is in the vector" << endl;
    }
    if (ques.removeAnswer("notAnAnswer")) {
        passed = false;
        cout << "FAILED removeAnswer test case where the string is not in the vector" << endl;
    }
    ques.clearAnswers();
    answer response4;
    response4.text = "correct";
    response4.correct = true;
    ques.addAnswer(response4);
    if (!ques.isCorrect("correct")) {
        passed = false;
        cout << "FAILED isCorrect test case where the answer is correct" << endl;
    }
    answer response5;
    response5.text = "incorrect";
    response5.correct = false;
    ques.addAnswer(response5);
    if (ques.isCorrect("incorrect")) {
        passed = false;
        cout << "FAILED isCorrect test case where the answer is incorrect" << endl;
    }
    if (!ques.isCorrect(0)) {
        passed = false;
        cout << "FAILED isCorrect test case where the index holds a correct answer" << endl;
    }
    if (ques.isCorrect(1)) {
        passed = false;
        cout << "FAILED isCorrect test case where the index holds an incorrect answer" << endl;
    }

    return passed;
}

bool testQuiz() {
    bool passed = true;

    Quiz qz;
    if (!(qz.getTitle().empty()) || qz.getTotalPointsCorrect() != 0 || qz.getTotalPointsPossible() != 0) {
        passed = false;
        cout << "FAILED constructor test case" << endl;
    }
    qz.setTitle("title");
    if (qz.getTitle() != "title") {
        passed = false;
        cout << "FAILED setTitle(*string*) test case" << endl;
    }
    Question question;
    question.setPrompt("prompt");
    question.setPoints(2);
    qz.addQuestion(question);
    if (qz.getQuestion(0).getPrompt() != "prompt" || qz.getQuestion(0).getPoints() != 2) {
        passed = false;
        cout << "FAILED addQuestion(*Question*) test case" << endl;
    }
    if (!qz.removeQuestion(0)) {
        passed = false;
        cout << "FAILED removeQuestion test case where index is valid" << endl;
    }
    if (qz.removeQuestion(-1)) {
        passed = false;
        cout << "FAILED removeQuestion test case where index is invalid" << endl;
    }
    Question question2;
    question2.setPrompt("hello");
    question2.setPoints(3);
    qz.addQuestion(question2);
    if (!qz.removeQuestion("hello")) {
        passed = false;
        cout << "FAILED removeQuestion test case where the string is in the vector" << endl;
    }
    if (qz.removeQuestion("notAnQuestion")) {
        passed = false;
        cout << "FAILED removeAnswer test case where the string is not in the vector" << endl;
    }

    return passed;
}