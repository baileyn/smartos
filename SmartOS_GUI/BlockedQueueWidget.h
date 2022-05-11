#ifndef BlockedQueueWidget_H
#define BlockedQueueWidget_H

#include <QListWidget>
#include <QWidget>

class BlockedQueueWidget : public QWidget
{
    Q_OBJECT

public:
    BlockedQueueWidget(QWidget* parent = nullptr);

    void update();

private:
    QListWidget* m_listWidget;
};

#endif // BlockedQueueWidget_H
