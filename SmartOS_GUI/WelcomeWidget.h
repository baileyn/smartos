#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include "MainWindow.h"

#include <QWidget>

class WelcomeWidget : public QWidget
{
    Q_OBJECT
public:
    WelcomeWidget(MainWindow* mainWindow, QWidget *parent = nullptr);
};

#endif // WELCOMEWIDGET_H
