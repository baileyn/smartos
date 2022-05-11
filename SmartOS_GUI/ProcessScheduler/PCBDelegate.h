#ifndef PCBDELEGATE_H
#define PCBDELEGATE_H

#include <QModelIndex>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>

class PCBDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    PCBDelegate();

    void paint(QPainter* painter,
               const QStyleOptionViewItem& option,
               const QModelIndex& index) const override;
};

#endif // PCBDELEGATE_H
