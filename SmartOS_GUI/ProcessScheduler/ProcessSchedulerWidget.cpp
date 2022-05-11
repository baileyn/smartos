#include "ProcessSchedulerWidget.h"

#include "PCBDelegate.h"
#include "ProcessCreationDialog.h"

#include "MainWindow.h"

#include <QBoxLayout>
#include <QIcon>
#include <QInputDialog>
#include <QListView>
#include <QPushButton>
#include <QSlider>
#include <QStringListModel>
#include <QToolBar>
#include <QVBoxLayout>

#include <memory>
#include <random>

#include <SmartOS.h>

#include <QDebug>

// Anonymous namespace so we don't clutter anything.
namespace
{
std::random_device r;
std::mt19937 engine(r());
}

extern std::unique_ptr<SmartOS> g_SmartOS;

ProcessSchedulerWidget::ProcessSchedulerWidget(MainWindow* parent)
    : QWidget(parent)
    , m_mainWindow{parent}
{
    QToolBar* toolbar = new QToolBar;

    toolbar->setIconSize(QSize{24, 24});
    toolbar->setFixedHeight(32);

    QAction* addAction = toolbar->addAction(QIcon(":/resources/add.png"), "");
    connect(addAction, &QAction::triggered, this, &ProcessSchedulerWidget::addProcessControlBlock);

    QAction* addRandomAction =
        toolbar->addAction(QIcon(":/resources/addRandom.png"), "");
    connect(addRandomAction, &QAction::triggered, this,
            &ProcessSchedulerWidget::addRandomProcessControlBlocks);

    QWidget* spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacer);

    toolbar->addAction(QIcon(":/resources/play.png"), "");
    toolbar->addAction(QIcon(":/resources/step.png"), "");
    toolbar->addAction(QIcon(":/resources/pause.png"), "");
    toolbar->addAction(QIcon(":/resources/stop.png"), "");

    QSlider* slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    toolbar->addWidget(slider);

    QWidget* spacer2 = new QWidget;
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacer2);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setMenuBar(toolbar);
    vbox->addWidget(new QPushButton("Plz Push"));

    setLayout(vbox);
}

void ProcessSchedulerWidget::paintEvent(QPaintEvent* paintEvent)
{
    QWidget::paintEvent(paintEvent);
}

void ProcessSchedulerWidget::addProcessControlBlock()
{
    ProcessCreationDialog processCreationDialog;

    if (processCreationDialog.exec() == QDialog::Accepted) {
        m_mainWindow->addHistory(
            QString("Add new Process Control Block with PID %1")
                .arg(processCreationDialog.pid()));
        g_SmartOS->createProcessControlBlock(
            processCreationDialog.pid(), processCreationDialog.memoryRequired());
    }
}

void ProcessSchedulerWidget::addRandomProcessControlBlocks()
{
    QInputDialog inputDialog;
    inputDialog.setLabelText(
        "How many random Process Control Blocks would you like to generate?");
    inputDialog.setOkButtonText("Create All");

    if (inputDialog.exec() == QInputDialog::Accepted) {
        QString text = inputDialog.textValue();

        bool parsed;
        int num = text.toInt(&parsed);

        if (parsed) {
            m_mainWindow->addHistory(
                QString("Add %1 random process control blocks.").arg(num));

            size_t maximumMemoryAvailable = g_SmartOS->maxMemory() - g_SmartOS->usedMemory();

            std::uniform_int_distribution<size_t> uniform{1, maximumMemoryAvailable};

            for (int i = 0; i < num; i++) {
                size_t pid = g_SmartOS->nextSequentialPID();
                g_SmartOS->createProcessControlBlock(pid, uniform(engine));
            }
        }
    }
}
