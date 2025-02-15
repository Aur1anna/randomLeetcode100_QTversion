#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QFile>
#include <QIcon>
#include <algorithm> // 使用 std::count_if
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 初始窗口大小
    this->resize(370, 600);
    // 设置窗口图标
    // this->setWindowIcon(QIcon("newicon.ico"));

    // 动态添加菜单项
    QMenu *settingsMenu = menuBar()->addMenu(tr("设置"));
    QAction *resetAction = new QAction(tr("重置题库"), this);
    QAction *aboutAction = new QAction(tr("关于"), this);
    settingsMenu->addAction(resetAction);
    settingsMenu->addAction(aboutAction);

    connect(resetAction, &QAction::triggered, this, &MainWindow::onResetDatabase);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);

    // 加载题库（如果 questions.json 不存在，则自动写入默认数据）
    m_questions = m_db.loadQuestions("questions.json");
    setupTable();
    updateStatus();

    connect(ui->randomButton, &QPushButton::clicked, this, &MainWindow::onRandomSelect);
    connect(ui->markSolvedButton, &QPushButton::clicked, this, &MainWindow::onMarkSolved);

    // 双击链接单元格时打开网页
    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, [this](int row, int column){
        if (column == 2) {
            QString url = ui->tableWidget->item(row, column)->data(Qt::UserRole).toString();
            QDesktopServices::openUrl(QUrl(url));
        }
    });
}

MainWindow::~MainWindow()
{
    // 程序退出前保存题库状态
    m_db.saveQuestions(m_questions, "questions.json");
    delete ui;
}

void MainWindow::setupTable()
{
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({ "       题目列表       ", "完成状态", "双击跳转链接" });
    ui->tableWidget->setRowCount(m_questions.size());

    for (int i = 0; i < m_questions.size(); ++i) {
        // 题目名称
        QTableWidgetItem *titleItem = new QTableWidgetItem(m_questions[i].title);
        ui->tableWidget->setItem(i, 0, titleItem);

        // 状态（使用复选框表示是否已解决）
        QTableWidgetItem *statusItem = new QTableWidgetItem();
        statusItem->setCheckState(m_questions[i].isSolved ? Qt::Checked : Qt::Unchecked);
        ui->tableWidget->setItem(i, 1, statusItem);

        // 链接
        QTableWidgetItem *linkItem = new QTableWidgetItem("打开链接");
        linkItem->setData(Qt::UserRole, m_questions[i].url);
        ui->tableWidget->setItem(i, 2, linkItem);
    }
}

void MainWindow::updateStatus()
{
    int solvedCount = 0;
    for (const auto &q : m_questions) {
        if (q.isSolved)
            solvedCount++;
    }
    ui->statusLabel->setText(QString("已完成：%1/%2").arg(solvedCount).arg(m_questions.size()));
}

void MainWindow::onRandomSelect()
{
    int index = m_db.getRandomUnsolvedIndex(m_questions);
    if (index == -1) {
        QMessageBox::information(this, tr("提示"), tr("所有题目已完成！"));
        return;
    }
    ui->tableWidget->selectRow(index);
}

void MainWindow::onMarkSolved()
{
    int row = ui->tableWidget->currentRow();
    if (row >= 0) {
        m_questions[row].isSolved = true;
        ui->tableWidget->item(row, 1)->setCheckState(Qt::Checked);
        updateStatus();
    }
}

void MainWindow::onResetDatabase()
{
    // 弹出确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("重置题库"),
                                  tr("重置之后所有题目完成情况将被清除，是否继续？"),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // 删除 questions.json 文件，下一次加载会生成默认数据
        if (QFile::exists("questions.json")) {
            QFile::remove("questions.json");
        }
        // 重新加载题库数据并更新界面
        loadQuestionsAndUpdate();
        QMessageBox::information(this, tr("重置题库"), tr("题库已重置。"));
    }
}

// void MainWindow::onAbout()
// {
//     // 弹出关于信息对话框
//     QMessageBox::information(this, tr("关于"),
//                              tr("欢迎使用randomLeetcode100_QTversion！"
//                                 "\n本项目是之前控制台应用程序版本的图形界面版本，使用Qt框架。"
//                                 "仅供学习或娱乐参考。"
//                                 "\n控制台应用程序版本项目地址：\n https://github.com/Aur1anna/randomLeetcode100"
//                                 "\n本项目地址：\n https://github.com/Aur1anna/randomLeetcode100_QTversion"
//                                 "\n欢迎在issue中留言~"));
// }

void MainWindow::onAbout()
{
    // 使用富文本格式
    QString aboutText = tr(
        "<h3>欢迎使用 randomLeetcode100_QTversion！</h3>"
        "<p>本项目是之前控制台应用程序版本的图形界面版本，使用 Qt 框架。</p>"
        "<p>仅供学习或娱乐参考。</p>"
        "<p>控制台应用程序版本项目地址：<a href='https://github.com/Aur1anna/randomLeetcode100'>https://github.com/Aur1anna/randomLeetcode100</a></p>"
        "<p>本项目地址：<a href='https://github.com/Aur1anna/randomLeetcode100_QTversion'>https://github.com/Aur1anna/randomLeetcode100_QTversion</a></p>"
        "<p>欢迎在 issue 中留言~</p>"
        );

    // 弹出关于信息对话框，并启用打开链接的功能
    QMessageBox aboutBox(this);
    aboutBox.setWindowTitle(tr("关于"));
    aboutBox.setTextFormat(Qt::RichText);  // 设置文本格式为富文本
    aboutBox.setText(aboutText);
    aboutBox.setTextInteractionFlags(Qt::TextBrowserInteraction);  // 允许用户与链接交互
    aboutBox.exec();
}

void MainWindow::loadQuestionsAndUpdate()
{
    m_questions = m_db.loadQuestions("questions.json");
    setupTable();
    updateStatus();
}
