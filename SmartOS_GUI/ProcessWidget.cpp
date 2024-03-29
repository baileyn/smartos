#include "ProcessWidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QPainter>

#include <QDebug>

ProcessWidget::ProcessWidget(ProcessControlBlockPtr& pcb, bool detailed, QWidget* parent)
    : QWidget{parent}
    , m_pcb{pcb}
    , m_detailed{detailed}
    , m_pid{nullptr}
    , m_memory{nullptr}
    , m_cpuUsage{nullptr}
    , m_ioReq{nullptr}
    , m_waitTerm{nullptr}
    , m_blockEvent{nullptr}
    , m_processType{nullptr}
{
    QGridLayout* gridLayout = new QGridLayout;

    m_pid = new QLabel(QString("%1").arg(pcb->pid()));
    m_memory = new QLabel(QString("%1").arg(pcb->memory()));

    gridLayout->addWidget(new QLabel("PID"), 0, 0);
    gridLayout->addWidget(m_pid, 0, 1);

    gridLayout->addWidget(new QLabel("Memory"), 1, 0);
    gridLayout->addWidget(m_memory, 1, 1);

    if (detailed) {
        m_cpuUsage = new QLabel(QString("%1").arg(pcb->cpuUsageTerm()));
        m_ioReq = new QLabel(QString("%1").arg(pcb->ioReqTerm()));
        m_waitTerm = new QLabel(QString("%1").arg(pcb->waitTerm()));

        gridLayout->addWidget(new QLabel("CPU Usage"), 2, 0);
        gridLayout->addWidget(m_cpuUsage, 2, 1);

        gridLayout->addWidget(new QLabel("IO"), 3, 0);
        gridLayout->addWidget(m_ioReq, 3, 1);

        gridLayout->addWidget(new QLabel("Wait"), 4, 0);
        gridLayout->addWidget(m_waitTerm, 4, 1);
    }

    m_processType = new QLabel;

    switch (m_pcb->processType()) {
    case ProcessType::CPU_BOUND:
        m_processType->setText("CPU BOUND");
        break;
    case ProcessType::INTERACTIVE:
        m_processType->setText("INTERACTIVE");
        break;
    case ProcessType::MIXED:
        m_processType->setText("MIXED");
        break;
    default:
        m_processType->setText("WRONG");
    }

    gridLayout->addWidget(new QLabel("Type"), detailed ? 5 : 2, 0);
    gridLayout->addWidget(m_processType, detailed ? 5 : 2, 1);

    setLayout(gridLayout);
}

void ProcessWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter{this};
    painter.drawRoundedRect(3, 3, width() - 5, height() - 5, 3, 3);
}
