#ifndef M2GP_CUSTOM_QUIZ_QUIZ_H
#define M2GP_CUSTOM_QUIZ_QUIZ_H

#include "Question.h"
#include <optional>
#include <vector>

using std::istream;

class Quiz {
private:
    string title;
    int totalPointsCorrect;
    int totalPointsPossible;
    int numberOfQuestions;
    vector<Question> questions;

public:
    /* Constructor */
    Quiz();

    /* Getters */
    string getTitle() const;
    int getTotalPointsCorrect() const;
    int getTotalPointsPossible() const;
    int getNumberOfQuestions() const;
    Question getQuestion(int index) const;
    Question getQuestion(string prompt) const;

    /* Setter */
    void setTitle(string title);
    void addQuestion(Question newQuestion);

    /* Remove Question either by index or prompt */
    bool removeQuestion(int index);
    bool removeQuestion(string prompt);

    /* Helper function to read Quiz data from a file */
    void readQuizFromFile(const string& filename);

    /* Interactive method to have the user take the Quiz */
    void takeQuiz(string filename, ostream& outs, istream& ins);
};

#endif //M2GP_CUSTOM_QUIZ_QUIZ_H
