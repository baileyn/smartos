#ifndef PROCESSCREATIONDIALOG_H
#define PROCESSCREATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>

class ProcessCreationDialog : public QDialog
{
    Q_OBJECT
public:
    ProcessCreationDialog();
    size_t pid() const;
    size_t memoryRequired() const;

private:
    void setupUi();

    void done(int r) override;

private:
    QLineEdit* m_pidLine;
    QLineEdit* m_memoryRequiredLine;

    size_t m_pid;
    size_t m_memoryRequired;
};

#endif // PROCESSCREATIONDIALOG_H
