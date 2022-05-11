#include "CpuWidget.h"

#include "Globals.h"

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

CpuWidget::CpuWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* vbox = new QVBoxLayout;
    QLabel* label = new QLabel("Current Process");
    vbox->addWidget(label);
    vbox->setAlignment(label, Qt::AlignCenter);

    setLayout(vbox);
}

void CpuWidget::update()
{
    if (m_currentProcess != nullptr) {
        layout()->removeWidget(m_currentProcess);
        delete m_currentProcess;
    }

    m_currentProcess = new ProcessWidget(g_SmartOS->cpu().currentProcess());
    layout()->addWidget(m_currentProcess);
}
