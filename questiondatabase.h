#ifndef QUESTIONDATABASE_H
#define QUESTIONDATABASE_H

#include <QObject>
#include <QVector>
#include <QString>
#include "question.h"

class QuestionDatabase : public QObject
{
    Q_OBJECT
public:
    explicit QuestionDatabase(QObject *parent = nullptr);

    // 从 JSON 文件加载题库，若文件不存在则生成默认数据
    QVector<Question> loadQuestions(const QString &filePath);
    // 保存题库状态到 JSON 文件
    void saveQuestions(const QVector<Question> &questions, const QString &filePath);
    // 随机返回一个未解决题目的索引，若全部已解决则返回 -1
    int getRandomUnsolvedIndex(const QVector<Question> &questions);
};

#endif // QUESTIONDATABASE_H
