#ifndef PROCESSSCHEDULERWIDGET_H
#define PROCESSSCHEDULERWIDGET_H

#include <QPaintEvent>
#include <QWidget>

class ProcessSchedulerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProcessSchedulerWidget(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* paintEvent) override;

signals:

public slots:
    void addProcessControlBlock();
    void addRandomProcessControlBlocks();
};

#endif // PROCESSSCHEDULERWIDGET_H
