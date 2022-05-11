#include "CpuWidget.h"

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

CpuWidget::CpuWidget(CentralProcessingUnit& cpu, QWidget* parent)
    : QWidget(parent)
    , m_cpu{cpu}
{
    QVBoxLayout* vbox = new QVBoxLayout;
    QLabel* label = new QLabel("Current Process");
    vbox->addWidget(label);
    vbox->setAlignment(label, Qt::AlignCenter);
}

void CpuWidget::update()
{
    if (m_currentProcess != nullptr) {
        layout()->removeWidget(m_currentProcess);
        delete m_currentProcess;
    }

    m_currentProcess = new ProcessWidget(m_cpu.currentProcess());
    layout()->addWidget(m_currentProcess);
}
