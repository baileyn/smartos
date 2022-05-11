#ifndef PROCESSCREATIONDIALOG_H
#define PROCESSCREATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>

class ProcessCreationDialog : public QDialog
{
    Q_OBJECT
public:
    ProcessCreationDialog();

public slots:
    void submit();

private:
    void setupUi();

private:
    QLineEdit* m_memoryRequired;
};

#endif // PROCESSCREATIONDIALOG_H
