#ifndef READYQUEUEWIDGET_H
#define READYQUEUEWIDGET_H

#include <QListWidget>
#include <QWidget>

class ReadyQueueWidget : public QWidget
{
    Q_OBJECT

public:
    ReadyQueueWidget(QWidget* parent = nullptr);

    void update();

private:
    QListWidget* m_listWidget;
};

#endif // READYQUEUEWIDGET_H
