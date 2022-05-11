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
    m_quantumEdit = new QLineEdit;
    gridLayout->addWidget(m_roundRobin, 1, 0);
    gridLayout->addWidget(m_quantumEdit, 1, 1);

    QPushButton* submitButton = new QPushButton("Submit");
    gridLayout->addWidget(submitButton, 2, 0, 1, 2);
    connect(submitButton, &QPushButton::clicked, this, &QDialog::accept);

    setLayout(gridLayout);
}

SchedulerType SchedulingDialog::schedulerType() const
{
    if (m_roundRobin->isChecked()) {
        return SchedulerType::ROUND_ROBIN;
    }
    return SchedulerType::DEFAULT;
}

size_t SchedulingDialog::quantum() const
{
    return m_quantum;
}

void SchedulingDialog::done(int r)
{
    if (r == QDialog::Rejected) {
        QDialog::done(r);
        return;
    }

    // We only care about the time quantum if round robin is checked.
    if (m_roundRobin->isChecked()) {
        bool ok;

        m_quantum = m_quantumEdit->text().toInt(&ok);

        if (!ok) {
            QMessageBox messageBox(
                QMessageBox::Critical, "Error!",
                "Please enter a valid integer for the quantum.");
            messageBox.exec();
            return;
        }
    }

    QDialog::done(r);
}
