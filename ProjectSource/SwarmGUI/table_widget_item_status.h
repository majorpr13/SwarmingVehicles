#ifndef STATUS_TABLE_WIDGET_H
#define STATUS_TABLE_WIDGET_H

#include <QTableWidgetItem>

enum Status
{
    OFFLINE,
    ONLINE,
    WARNING,
    ERR,
    STATUS_NR_ITEMS
};

class TableWidgetItemStatus : public QTableWidgetItem
{
public:
    TableWidgetItemStatus();

public slots:

    void StatusChanged(Status status);

};

#endif // STATUS_TABLE_WIDGET_H
