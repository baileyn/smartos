#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#include <ProcessControlBlock.h>

#include <QWidget>

class ProcessWidget : public QWidget
{
    Q_OBJECT

public:
    ProcessWidget(ProcessControlBlockPtr& pcb, QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event) override;

private:
    ProcessControlBlockPtr& m_pcb;
};

#endif // PROCESSWIDGET_H
