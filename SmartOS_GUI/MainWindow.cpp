#include "MainWindow.h"

#include "Globals.h"
#include "HistoryDialog.h"
#include "ProcessScheduler/ProcessSchedulerWidget.h"
#include "ProcessScheduler/SchedulingDialog.h"
#include "WelcomeWidget.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include <SmartOS.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , stackedWidget(new QStackedWidget)
    , welcomeWidget(nullptr)
    , processSchedulerWidget(nullptr)
{
    setWindowIcon(QIcon(":/resources/smartos.png"));
    setWindowTitle(tr("SmartOS Simulator"));
    setCentralWidget(stackedWidget);

    setupUi();
}

MainWindow::~MainWindow()
{}

void MainWindow::addHistory(const QString& info)
{
    historyList.push_front(info);
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
    historyList.push_front(tr("Show About"));

    QMessageBox aboutBox(QMessageBox::NoIcon, tr("About Menu"),
                         tr("<center><b>SmartOS v%1</b></center><br>"
                            "Operating Systems Concepts Simulator<br>"
                            "Available under <b>GPLv3 Licence</b><br>"
                            "<center>Nicholas Bailey</center>")
                             .arg(QString::fromStdString(SmartOS::getVersionNumber())),
                         QMessageBox::Ok);

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
    if (welcomeWidget == nullptr) {
        welcomeWidget = new WelcomeWidget(this);
        stackedWidget->addWidget(welcomeWidget);
    } else {
        // The first time showing the Welcome view isn't technically a user command.
        addHistory("Show Welcome View");
    }

    stackedWidget->setCurrentWidget(welcomeWidget);
}

void MainWindow::showProcessScheduler()
{
    addHistory("Show CPU Simulator");

    if (processSchedulerWidget == nullptr) {
        processSchedulerWidget = new ProcessSchedulerWidget{this};
        stackedWidget->addWidget(processSchedulerWidget);
    }

    SchedulingDialog scheduleDialog;
    scheduleDialog.exec();

    g_SmartOS->setScheduler(scheduleDialog.schedulerType());
    g_SmartOS->setTimeQuantum(scheduleDialog.quantum());
    g_SmartOS->setMaximumPriority(scheduleDialog.priorityQueues());

    stackedWidget->setCurrentWidget(processSchedulerWidget);
}
