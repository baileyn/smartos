#include "PCBDelegate.h"

PCBDelegate::PCBDelegate()
{}

void PCBDelegate::paint(QPainter* painter,
                        const QStyleOptionViewItem& option,
                        const QModelIndex& index) const
{
    painter->drawRect(0, 0, 10, 10);
}
