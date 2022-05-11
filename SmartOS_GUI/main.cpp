#include "Globals.h"
#include "MainWindow.h"

#include <QApplication>
#include <QDebug>

#include <iostream>

const size_t MEMORY = 1024;
std::unique_ptr<SmartOS> g_SmartOS = std::make_unique<SmartOS>(MEMORY);

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(800, 600);
    w.show();
    return a.exec();
}
