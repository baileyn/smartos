#include "CpuWidget.h"

#include "Globals.h"

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

#include <QDebug>

CpuWidget::CpuWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* vbox = new QVBoxLayout;
    QLabel* label = new QLabel("Current Process");
    vbox->addWidget(label);
    vbox->setAlignment(label, Qt::AlignCenter);

    m_stackedWidget = new QStackedWidget;
    vbox->addWidget(m_stackedWidget);
    setLayout(vbox);
}

void CpuWidget::update()
{
    auto& pcb = g_SmartOS->cpu().currentProcess();

    if (pcb != nullptr) {
        auto widget = new ProcessWidget(pcb, true);
        m_stackedWidget->addWidget(widget);
        m_stackedWidget->setCurrentWidget(widget);
    }
}
