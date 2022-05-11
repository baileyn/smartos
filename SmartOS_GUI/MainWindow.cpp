#include "MainWindow.h"

#include "HistoryDialog.h"
#include "ProcessSchedulerWidget.h"
#include "SmartOS.h"
#include "WelcomeWidget.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), stackedWidget(new QStackedWidget), processSchedulerWidget(nullptr), welcomeWidget(nullptr)
{
    setWindowIcon(QIcon(":/resources/smartos.png"));
    setWindowTitle(tr("SmartOS Simulator"));
    setCentralWidget(stackedWidget);

    setupUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    setupMenuBar();
    showWelcome();
}

void MainWindow::setupMenuBar()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* welcomeAction = fileMenu->addAction(tr("&Welcome"));
    connect(welcomeAction, &QAction::triggered, this, &MainWindow::showWelcome);

    fileMenu->addSeparator();
    QAction* historyAction = fileMenu->addAction(tr("&History"));
    connect(historyAction, &QAction::triggered, this, &MainWindow::showHistory);

    fileMenu->addSeparator();
    QAction* exitAction = fileMenu->addAction(tr("&Exit"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::exit);

    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* aboutAction = helpMenu->addAction(tr("&About"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::exit()
{
    close();
}

void MainWindow::showAbout()
{
    historyList.push_back(tr("Show About"));

    QMessageBox aboutBox(
                QMessageBox::NoIcon,
                tr("About Menu"),
                                   tr("<center><b>SmartOS v%1</b></center><br>"
                                      "Operating Systems Concepts Simulator<br>"
                                      "Available under <b>GPLv3 Licence</b><br>"
                                      "<center>Nicholas Bailey</center>").arg(VERSION.toString()),
                QMessageBox::Ok
                );
    aboutBox.setWindowIcon(QIcon(":/resources/about.png"));
    aboutBox.exec();
}

void MainWindow::showHistory()
{
    HistoryDialog historyDialog(historyList);
    historyDialog.exec();
}

void MainWindow::showWelcome()
{
    if(welcomeWidget == nullptr) {
        welcomeWidget = new WelcomeWidget(this);
        stackedWidget->addWidget(welcomeWidget);
    }

    stackedWidget->setCurrentWidget(welcomeWidget);
}

void MainWindow::showProcessScheduler()
{
    if(processSchedulerWidget == nullptr) {
        processSchedulerWidget = new ProcessSchedulerWidget;
        stackedWidget->addWidget(processSchedulerWidget);
    }

    stackedWidget->setCurrentWidget(processSchedulerWidget);
}
