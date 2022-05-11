#include "ProcessCreationDialog.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

ProcessCreationDialog::ProcessCreationDialog()
    : m_memoryRequired(new QLineEdit)
{
    setupUi();
}

void ProcessCreationDialog::submit()
{
    close();
}

void ProcessCreationDialog::setupUi()
{
    QGridLayout* layout = new QGridLayout();
    setLayout(layout);

    layout->addWidget(new QLabel("Memory Required"), 0, 0);
    layout->addWidget(m_memoryRequired, 0, 1);

    QPushButton* createButton = new QPushButton("Create");
    layout->addWidget(createButton, 1, 0, 1, 2);

    connect(createButton, &QPushButton::clicked, this, &ProcessCreationDialog::submit);
}
