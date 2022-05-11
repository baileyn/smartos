#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include "ProcessWidget.h"

#include <CentralProcessingUnit.h>
#include <ProcessControlBlock.h>

#include <QPaintEvent>
#include <QWidget>

class CpuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CpuWidget(QWidget* parent = nullptr);

    void update();

private:
    ProcessWidget* m_currentProcess;
};

#endif // CPUWIDGET_H
