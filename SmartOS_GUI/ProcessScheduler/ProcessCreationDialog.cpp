#include "ProcessCreationDialog.h"
#include "Globals.h"

#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>

ProcessCreationDialog::ProcessCreationDialog()
    : m_memoryRequiredLine(new QLineEdit)
{
    setupUi();
}

size_t ProcessCreationDialog::pid() const
{
    return m_pid;
}

size_t ProcessCreationDialog::memoryRequired() const
{
    return m_memoryRequired;
}

void ProcessCreationDialog::setupUi()
{
    QGridLayout* layout = new QGridLayout();
    setLayout(layout);

    layout->addWidget(new QLabel("PID"), 0, 0);

    m_pidLine = new QLineEdit(
        QString::fromStdString(std::to_string(g_SmartOS->nextSequentialPID())));
    layout->addWidget(m_pidLine, 0, 1);
    layout->addWidget(new QLabel("Memory Required"), 1, 0);
    layout->addWidget(m_memoryRequiredLine, 1, 1);

    QPushButton* cancelButton = new QPushButton("Cancel");
    layout->addWidget(cancelButton, 2, 0);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    QPushButton* createButton = new QPushButton("Create");
    layout->addWidget(createButton, 2, 1);
    connect(createButton, &QPushButton::clicked, this, &QDialog::accept);
}

void ProcessCreationDialog::done(int r)
{
    if (r == QDialog::Rejected) {
        QDialog::done(r);
        return;
    }

    bool ok;

    m_pid = m_pidLine->text().toInt(&ok);

    if (!ok) {
        QMessageBox messageBox(QMessageBox::Critical, "Error!",
                               "Please enter a valid integer for the pid.");
        messageBox.exec();
        return;
    }

    m_memoryRequired = m_memoryRequiredLine->text().toInt(&ok);

    if (!ok) {
        QMessageBox messageBox(
            QMessageBox::Critical, "Error!",
            "Please enter a valid integer for the memory required.");
        messageBox.exec();
        return;
    }

    QDialog::done(r);
}
