#ifndef TABLE_STATUS_WIDGET_H
#define TABLE_STATUS_WIDGET_H

#include <QTableWidget>
#include <QtDesigner/QtDesigner>

#include "Definitions.h"


#ifdef ROS_LIBS
#include <mavlink_common/HEARTBEAT.h>
#include <mavlink_common/SYS_STATUS.h>
#include <mavlink_common/GPS_RAW_INT.h>
#endif


class TableStatusWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableStatusWidget(QWidget *parent = 0);

public slots:

    void updateElapsedTime(const int VehicleID, const int elapsedTime);


    //!
    //! \brief Set the entries for this table
    //! \param strList List of entries
    //!
    bool addEntry(const int &VehicleID);

    void removeEntry(const int &VehicleID);


    //!
    //! \brief Change the latency of a row
    //! \param entryName Row to change latency of
    //! \param latency number to change to
    //!
    void ChangeConnection(const int &VehicleID, const bool &Connection);

    void ChangeArmed(const int &VehicleID, const bool &ArmStatus);

    void ChangeBatteryLow(const int &VehicleID, const double &VoltageLow);

    void ChangeAmpHigh(const int &VehicleID, const double &AmperageHigh);

#ifdef ROS_LIBS
    void ChangeBatteryVoltage(const mavlink_common::SYS_STATUS &status);
    void ChangeSatellite(const mavlink_common::GPS_RAW_INT &status);
#endif

private slots:

signals:

private:

    struct TableEntry
    {
        QTableWidgetItem *Vehicle_ID;
        QTableWidgetItem *Connection;
        QTableWidgetItem *Armed;
        QTableWidgetItem *GPS_Number;
        QTableWidgetItem *Battery_V;
        QTableWidgetItem *Battery_A;
    };

    //! Map of entry names and the items in the row
    QMap<int, TableEntry> m_VehicleInformationP;

    //! Map of entry names and the items in the row
    QMap<int, StructureDefinitions::TableDefinition> m_VehicleInformationFull;

};

#endif // TABLE_STATUS_WIDGET_H
