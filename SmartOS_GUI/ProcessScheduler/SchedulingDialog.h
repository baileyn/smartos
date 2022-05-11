#ifndef SCHEDULINGDIALOG_H
#define SCHEDULINGDIALOG_H

#include <SmartOS.h>

#include <QDialog>
#include <QRadioButton>
#include <QSpinBox>

class SchedulingDialog : public QDialog
{
    Q_OBJECT

public:
    SchedulingDialog();

    SchedulerType schedulerType() const;
    size_t quantum() const;
    size_t priorityQueues() const;

private:
    QRadioButton* m_defaultButton;
    QRadioButton* m_roundRobin;
    QSpinBox* m_quantumSpinBox;

    QRadioButton* m_mlfq;
    QSpinBox* m_priorityQueues;

    size_t m_quantum;
};

#endif // SCHEDULINGDIALOG_H
