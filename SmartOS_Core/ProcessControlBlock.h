#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H

#include <QObject>
#include <QString>

class ProcessControlBlock : public QObject
{
    Q_OBJECT
public:
    explicit ProcessControlBlock(QObject *parent = nullptr);

private:
    QString m_name;
    unsigned int m_pid;
    unsigned int m_ioReqTerm;
    unsigned int m_waitTerm;
    unsigned int m_memory;
};

#endif // PROCESSCONTROLBLOCK_H
