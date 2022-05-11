#include "ProcessSchedulerWidget.h"

#include <QPushButton>
#include <QVBoxLayout>

ProcessSchedulerWidget::ProcessSchedulerWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* vbox = new QVBoxLayout;
    setLayout(vbox);

    vbox->addWidget(new QPushButton("Plz Push"));
}
