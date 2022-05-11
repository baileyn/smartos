#ifndef PROCESSSCHEDULERWIDGET_H
#define PROCESSSCHEDULERWIDGET_H

#include <QPaintEvent>
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

private:
    MainWindow* m_mainWindow;
};

#endif // PROCESSSCHEDULERWIDGET_H
