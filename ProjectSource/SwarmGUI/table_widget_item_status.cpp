#include "table_widget_item_status.h"

TableWidgetItemStatus::TableWidgetItemStatus()
    :QTableWidgetItem()
{
    StatusChanged(OFFLINE);
}

void TableWidgetItemStatus::StatusChanged(Status status)
{
    switch(status)
    {
    case OFFLINE:
        setBackground(QBrush(Qt::gray));
        break;
    case ONLINE:
        setBackground(QBrush(Qt::green));
        break;
    case WARNING:
        setBackground(QBrush(Qt::yellow));
        break;
    case ERR:
        setBackground(QBrush(Qt::red));
        break;
    default:
        throw;
    }
}
