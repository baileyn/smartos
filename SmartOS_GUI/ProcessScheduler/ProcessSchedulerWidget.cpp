#include "ProcessSchedulerWidget.h"

#include "ProcessCreationDialog.h"

#include <QBoxLayout>
#include <QIcon>
#include <QInputDialog>
#include <QPushButton>
#include <QSlider>
#include <QToolBar>
#include <QVBoxLayout>

#include <memory>

#include <SmartOS.h>

#include <QDebug>

extern std::unique_ptr<SmartOS> g_SmartOS;

ProcessSchedulerWidget::ProcessSchedulerWidget(QWidget* parent)
    : QWidget(parent)
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

    QWidget* spacer2 = new QWidget;
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacer2);

    QSlider* slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    toolbar->addWidget(slider);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setMenuBar(toolbar);
    vbox->addWidget(new QPushButton("Plz Push"));

    setLayout(vbox);
}

void ProcessSchedulerWidget::addProcessControlBlock()
{
    ProcessCreationDialog processCreationDialog;

    if (processCreationDialog.exec() == QDialog::Accepted) {
        g_SmartOS->createProcessControlBlock(
            processCreationDialog.pid(), processCreationDialog.memoryRequired());
    }
}

void ProcessSchedulerWidget::addRandomProcessControlBlocks()
{
    QInputDialog inputDialog;
    inputDialog.setOkButtonText("Create All");

    if (inputDialog.exec() == QInputDialog::Accepted) {
        QString text = inputDialog.textValue();

        bool parsed;
        int num = text.toInt(&parsed);

        if (parsed) {
            for (int i = 0; i < num; i++) {
                g_SmartOS->createProcessControlBlock(0, 1);
            }
        }
    }
}
