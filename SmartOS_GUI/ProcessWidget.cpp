#include "ProcessWidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QPainter>

#include <QDebug>

ProcessWidget::ProcessWidget(ProcessControlBlockPtr& pcb, QWidget* parent)
    : QWidget{parent}
    , m_pcb{pcb}
{
    QGridLayout* gridLayout = new QGridLayout;

    gridLayout->addWidget(new QLabel("PID"), 0, 0);
    gridLayout->addWidget(new QLabel(QString("%1").arg(pcb->pid())), 0, 1);

    gridLayout->addWidget(new QLabel("Memory"), 1, 0);
    gridLayout->addWidget(new QLabel(QString("%1").arg(pcb->memory())), 1, 1);

    setLayout(gridLayout);
}

void ProcessWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter{this};
    painter.drawRoundedRect(3, 3, width() - 5, height() - 5, 3, 3);
}
