#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#include <ProcessControlBlock.h>

#include <QLabel>
#include <QWidget>

class ProcessWidget : public QWidget
{
    Q_OBJECT

public:
    ProcessWidget(ProcessControlBlockPtr& pcb, bool detailed = false, QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event) override;

    void update();

private:
    ProcessControlBlockPtr& m_pcb;

    bool m_detailed;

    QLabel* m_pid;
    QLabel* m_memory;
    QLabel* m_cpuUsage;
    QLabel* m_ioReq;
    QLabel* m_waitTerm;
    QLabel* m_blockEvent;
    QLabel* m_processType;
};

#endif // PROCESSWIDGET_H
