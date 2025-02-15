QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = randomLeetcode100

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    questiondatabase.cpp \
    question.cpp

HEADERS += \
    mainwindow.h \
    questiondatabase.h \
    question.h

FORMS += \
    mainwindow.ui

# 使用静态图标资源，添加资源文件：
RC_ICONS = newicon.ico
