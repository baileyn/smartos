#ifndef SCHEDULINGDIALOG_H
#define SCHEDULINGDIALOG_H

#include <SmartOS.h>

#include <QDialog>
#include <QLineEdit>
#include <QRadioButton>

class SchedulingDialog : public QDialog
{
    Q_OBJECT

public:
    SchedulingDialog();

    SchedulerType schedulerType() const;
    size_t quantum() const;

private:
    void done(int r) override;

private:
    QRadioButton* m_defaultButton;
    QRadioButton* m_roundRobin;
    QLineEdit* m_quantumEdit;

    size_t m_quantum;
};

#endif // SCHEDULINGDIALOG_H
