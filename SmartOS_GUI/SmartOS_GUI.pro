#-------------------------------------------------
#
# Project created by QtCreator 2018-04-09T09:16:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smartos
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    HistoryDialog.cpp \
    HelpDialog.cpp \
    ProcessSchedulerWidget.cpp \
    WelcomeWidget.cpp

HEADERS += \
        MainWindow.h \
    HistoryDialog.h \
    HelpDialog.h \
    ProcessSchedulerWidget.h \
    WelcomeWidget.h

RESOURCES += \
    smartos.qrc

LIBS += SmartOS_Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SmartOS_Core/release/ -lSmartOS_Core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SmartOS_Core/debug/ -lSmartOS_Core
else:unix: LIBS += -L$$OUT_PWD/../SmartOS_Core/ -lSmartOS_Core

INCLUDEPATH += $$PWD/../SmartOS_Core
DEPENDPATH += $$PWD/../SmartOS_Core
