#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include "ProcessWidget.h"

#include <CentralProcessingUnit.h>
#include <ProcessControlBlock.h>

#include <QPaintEvent>
#include <QStackedWidget>
#include <QWidget>

class CpuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CpuWidget(QWidget* parent = nullptr);

    void update();

private:
    QStackedWidget* m_stackedWidget;
};

#endif // CPUWIDGET_H
