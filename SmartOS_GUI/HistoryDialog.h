#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QStringList>

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    HistoryDialog(QStringList& historyList);

private slots:
    void accept();
};

#endif // HISTORYDIALOG_H
