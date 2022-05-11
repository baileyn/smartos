#include "MainWindow.h"
#include <QApplication>

#include <ProcessControlBlock.h>
#include <iostream>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(800, 600);
    w.show();
    return a.exec();
}
