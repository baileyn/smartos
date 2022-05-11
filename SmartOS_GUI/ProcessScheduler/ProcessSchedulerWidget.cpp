#include "ProcessSchedulerWidget.h"

#include "ProcessCreationDialog.h"

#include "MainWindow.h"

#include <QAction>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QInputDialog>
#include <QLabel>
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
} // namespace

extern std::unique_ptr<SmartOS> g_SmartOS;

ProcessSchedulerWidget::ProcessSchedulerWidget(MainWindow* parent)
    : QWidget(parent)
    , m_mainWindow{parent}
    , m_currentStep{0}
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

    m_playAction = toolbar->addAction(QIcon(":/resources/play.png"), "");
    connect(m_playAction, &QAction::triggered, this, &ProcessSchedulerWidget::execute);

    m_stepAction = toolbar->addAction(QIcon(":/resources/step.png"), "");
    connect(m_stepAction, &QAction::triggered, this, &ProcessSchedulerWidget::executeStep);

    m_pauseAction = toolbar->addAction(QIcon(":/resources/pause.png"), "");
    connect(m_pauseAction, &QAction::triggered, this, &ProcessSchedulerWidget::pause);

    m_stopAction = toolbar->addAction(QIcon(":/resources/stop.png"), "");
    connect(m_stopAction, &QAction::triggered, this, &ProcessSchedulerWidget::stop);

    m_pauseAction->setEnabled(false);
    m_stopAction->setEnabled(false);

    m_slider = new QSlider;
    m_slider->setOrientation(Qt::Horizontal);

    m_slider->setMaximum(5);
    m_slider->setMinimum(1);

    toolbar->addWidget(m_slider);

    QWidget* spacer2 = new QWidget;
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacer2);

    m_timerDisplay = new QLabel;
    m_timerDisplay->setText(QString("Step: %1").arg(m_currentStep));
    toolbar->addWidget(m_timerDisplay);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setMenuBar(toolbar);

    m_readyQueueWidget = new ReadyQueueWidget;
    vbox->addWidget(m_readyQueueWidget);

    QHBoxLayout* hbox = new QHBoxLayout;

    m_cpuWidget = new CpuWidget;
    hbox->addWidget(m_cpuWidget);
    vbox->addLayout(hbox);

    m_executeTimer = new QTimer;
    connect(m_executeTimer, &QTimer::timeout, this, &ProcessSchedulerWidget::executeStep);

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
        m_readyQueueWidget->update();
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

            size_t maximumMemoryAvailable =
                g_SmartOS->maxMemory() - g_SmartOS->usedMemory();
            maximumMemoryAvailable /= num;

            std::uniform_int_distribution<size_t> uniform{1, maximumMemoryAvailable};

            for (int i = 0; i < num; i++) {
                size_t pid = g_SmartOS->nextSequentialPID();
                g_SmartOS->createProcessControlBlock(pid, uniform(engine));
            }

            m_readyQueueWidget->update();
        }
    }
}

void ProcessSchedulerWidget::execute()
{
    m_playAction->setEnabled(false);
    m_stepAction->setEnabled(false);
    m_pauseAction->setEnabled(true);
    m_stopAction->setEnabled(true);
    m_slider->setEnabled(false);

    m_executeTimer->setInterval(1000 / m_slider->value());

    m_executeTimer->start();
}

void ProcessSchedulerWidget::pause()
{
    m_playAction->setEnabled(true);
    m_stepAction->setEnabled(true);
    m_pauseAction->setEnabled(false);
    m_stopAction->setEnabled(false);

    m_slider->setEnabled(true);

    m_executeTimer->stop();
}

void ProcessSchedulerWidget::stop()
{
    m_playAction->setEnabled(true);
    m_stepAction->setEnabled(true);
    m_stopAction->setEnabled(false);
    m_pauseAction->setEnabled(false);

    m_slider->setEnabled(true);

    m_executeTimer->stop();

    m_currentStep = 0;
    m_timerDisplay->setText(QString("Step: %1").arg(m_currentStep));
}

void ProcessSchedulerWidget::executeStep()
{
    m_timerDisplay->setText(QString("Step: %1").arg(m_currentStep));

    m_currentStep++;
}
