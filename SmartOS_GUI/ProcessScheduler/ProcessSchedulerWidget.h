#ifndef PROCESSSCHEDULERWIDGET_H
#define PROCESSSCHEDULERWIDGET_H

#include "BlockedQueueWidget.h"
#include "CpuWidget.h"
#include "ReadyQueueWidget.h"

#include <QAction>
#include <QLabel>
#include <QPaintEvent>
#include <QSlider>
#include <QTimer>
#include <QWidget>

class MainWindow;

class ProcessSchedulerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProcessSchedulerWidget(MainWindow* parent = nullptr);

    void paintEvent(QPaintEvent* paintEvent) override;

signals:

public slots:
    void addProcessControlBlock();
    void addRandomProcessControlBlocks();
    void execute();
    void pause();
    void stop();

    void executeStep();

private:
    void update();

private:
    MainWindow* m_mainWindow;
    ReadyQueueWidget* m_readyQueueWidget;
    BlockedQueueWidget* m_blockedQueueWidget;
    CpuWidget* m_cpuWidget;

    int m_currentStep;

    QAction* m_playAction;
    QAction* m_stepAction;
    QAction* m_pauseAction;
    QAction* m_stopAction;

    QSlider* m_slider;
    QLabel* m_timerDisplay;
    QTimer* m_executeTimer;
};

#endif // PROCESSSCHEDULERWIDGET_H
