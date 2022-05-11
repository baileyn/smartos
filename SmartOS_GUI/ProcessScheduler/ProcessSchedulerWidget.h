#ifndef PROCESSSCHEDULERWIDGET_H
#define PROCESSSCHEDULERWIDGET_H

#include <QWidget>

class ProcessSchedulerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProcessSchedulerWidget(QWidget* parent = nullptr);

signals:

public slots:
    void addProcessControlBlock();
    void addRandomProcessControlBlocks();
};

#endif // PROCESSSCHEDULERWIDGET_H
