#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "question.h"
#include "questiondatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 原有功能
    void onRandomSelect();
    void onMarkSolved();
    // 新增槽函数
    void onResetDatabase();
    void onAbout();

private:
    Ui::MainWindow *ui;
    QVector<Question> m_questions;
    QuestionDatabase m_db;
    void setupTable();
    void updateStatus();
    void loadQuestionsAndUpdate();
};

#endif // MAINWINDOW_H
