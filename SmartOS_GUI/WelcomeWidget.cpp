#include "WelcomeWidget.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QVBoxLayout>

WelcomeWidget::WelcomeWidget(MainWindow* mainWindow, QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* vbox = new QVBoxLayout;
    QHBoxLayout* hbox = new QHBoxLayout;
    vbox->addLayout(hbox);
    setLayout(vbox);

    QPushButton* cpuButton = new QPushButton(QIcon(":/resources/cpu.png"), "");
    cpuButton->setFixedSize(QSize(128, 128));
    cpuButton->setIconSize(QSize(100, 100));
    cpuButton->setToolTip(tr("Process scheduling"));
    connect(cpuButton, &QPushButton::clicked, mainWindow, &MainWindow::showProcessScheduler);
    hbox->addWidget(cpuButton);

    QPushButton* ramButton = new QPushButton(QIcon(":/resources/ram.png"), "");
    ramButton->setFixedSize(QSize(128, 128));
    ramButton->setIconSize(QSize(100, 100));
    ramButton->setToolTip(tr("Memory"));
    hbox->addWidget(ramButton);
}
