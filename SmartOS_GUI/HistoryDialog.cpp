#include "HistoryDialog.h"

#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

HistoryDialog::HistoryDialog(QStringList& historyList)
{
    setWindowTitle(tr("Command History"));
    setWindowIcon(QIcon(":/resources/history.png"));
    QVBoxLayout* vbox = new QVBoxLayout;

    QListWidget* listWidget = new QListWidget;
    listWidget->addItems(historyList);
    vbox->addWidget(listWidget);

    QPushButton* accept = new QPushButton(tr("Close"));
    connect(accept, &QPushButton::clicked, this, &HistoryDialog::accept);
    vbox->addWidget(accept);

    setLayout(vbox);
    adjustSize();
}

void HistoryDialog::accept()
{
    close();
}
