#include "SchedulingDialog.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>

SchedulingDialog::SchedulingDialog()
    : m_quantum{2}
{
    setWindowFlag(Qt::WindowCloseButtonHint, false);
    setWindowTitle("Scheduling Algorithm");

    QGridLayout* gridLayout = new QGridLayout;

    m_defaultButton = new QRadioButton("Default Scheduler");
    m_defaultButton->setChecked(true);

    gridLayout->addWidget(m_defaultButton, 0, 0);

    m_roundRobin = new QRadioButton("Round Robin");
    m_quantumSpinBox = new QSpinBox;
    m_quantumSpinBox->setMaximum(10);
    m_quantumSpinBox->setValue(5);
    m_quantumSpinBox->setMinimum(1);

    gridLayout->addWidget(m_roundRobin, 1, 0);
    gridLayout->addWidget(m_quantumSpinBox, 1, 1);

    m_mlfq = new QRadioButton("Multi-Level Feedback Queue");
    m_priorityQueues = new QSpinBox;
    m_priorityQueues->setMaximum(10);
    m_priorityQueues->setValue(5);
    m_priorityQueues->setMinimum(1);

    gridLayout->addWidget(m_mlfq, 2, 0);
    gridLayout->addWidget(m_priorityQueues, 2, 1);

    QPushButton* submitButton = new QPushButton("Submit");
    gridLayout->addWidget(submitButton, 3, 0, 1, 2);
    connect(submitButton, &QPushButton::clicked, this, &QDialog::accept);

    setLayout(gridLayout);
}

SchedulerType SchedulingDialog::schedulerType() const
{
    if (m_roundRobin->isChecked()) {
        return SchedulerType::ROUND_ROBIN;
    } else if (m_mlfq->isChecked()) {
        return SchedulerType::MLFQ;
    }

    return SchedulerType::DEFAULT;
}

size_t SchedulingDialog::quantum() const
{
    return m_quantumSpinBox->value();
}

size_t SchedulingDialog::priorityQueues() const
{
    return m_priorityQueues->value();
}
