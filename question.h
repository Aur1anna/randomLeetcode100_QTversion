#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

struct Question {
    QString title;
    QString url;
    bool isSolved;

    Question(const QString &t = "", const QString &u = "", bool s = false)
        : title(t), url(u), isSolved(s) {}
};

#endif // QUESTION_H
