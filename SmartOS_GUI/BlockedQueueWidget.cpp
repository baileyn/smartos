#include "BlockedQueueWidget.h"

#include "Globals.h"
#include "ProcessWidget.h"

#include <QLabel>
#include <QListWidgetItem>
#include <QPainter>
#include <QVBoxLayout>

#include <QDebug>

BlockedQueueWidget::BlockedQueueWidget(QWidget* parent)
    : QWidget{parent}
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QLabel* label = new QLabel("Blocked Queue");
    mainLayout->addWidget(label);
    mainLayout->setAlignment(label, Qt::AlignCenter);

    m_listWidget = new QListWidget;

    mainLayout->addWidget(m_listWidget);
    setLayout(mainLayout);

    update();
}

void BlockedQueueWidget::update()
{
    m_listWidget->clear();

    for (auto& pcb : g_SmartOS->blockedQueue()) {
        if (pcb == nullptr) {
            continue;
        }

        ProcessWidget* processWidget = new ProcessWidget(pcb);

        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(0, 62));
        m_listWidget->addItem(item);
        m_listWidget->setItemWidget(item, processWidget);
    }
}
