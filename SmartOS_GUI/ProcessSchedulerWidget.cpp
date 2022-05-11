#include "ProcessSchedulerWidget.h"

#include <QBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QSlider>
#include <QToolBar>
#include <QVBoxLayout>

ProcessSchedulerWidget::ProcessSchedulerWidget(QWidget* parent)
    : QWidget(parent)
{
    QToolBar* toolbar = new QToolBar;

    toolbar->setIconSize(QSize{24, 24});
    toolbar->setFixedHeight(32);

    toolbar->addAction(QIcon(":/resources/add.png"), "");
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
