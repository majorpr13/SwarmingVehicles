#include "table_status_widget.h"

#include <QStandardItemModel>
#include <QHeaderView>

#include "table_widget_item_status.h"

TableStatusWidget::TableStatusWidget(QWidget *parent) :
    QTableWidget(parent)
{

    setColumnCount(6);

    QTableWidgetItem *item0 = new QTableWidgetItem("Vehicle ID");
    QTableWidgetItem *item1 = new QTableWidgetItem("Connection");
    QTableWidgetItem *item2 = new QTableWidgetItem("ACTIVE");
    QTableWidgetItem *item3 = new QTableWidgetItem("GPS Sat");
    QTableWidgetItem *item4 = new QTableWidgetItem("Battery V");
    QTableWidgetItem *item5 = new QTableWidgetItem("Battery A");

    item0->setTextAlignment(Qt::AlignCenter);
    item1->setTextAlignment(Qt::AlignCenter);
    item2->setTextAlignment(Qt::AlignCenter);
    item3->setTextAlignment(Qt::AlignCenter);
    item4->setTextAlignment(Qt::AlignCenter);
    item5->setTextAlignment(Qt::AlignCenter);

    setHorizontalHeaderItem(0, item0);
    setHorizontalHeaderItem(1, item1);
    setHorizontalHeaderItem(2, item2);
    setHorizontalHeaderItem(3, item3);
    setHorizontalHeaderItem(4, item4);
    setHorizontalHeaderItem(5, item5);

    //horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //table can not be edited
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    //no horizontal scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //turn off header
    verticalHeader()->setVisible(false);
}



//!
//! \brief Add an entry for this table
//! \param strList List of entries
//!
bool TableStatusWidget::addEntry(const int &VehicleID)
{

    if(!m_VehicleInformationP.contains(VehicleID))
    {
        int row_number = this->rowCount();

        this->insertRow(row_number);

        setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Vehicle ID")));
        setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Connection")));
        setHorizontalHeaderItem(2, new QTableWidgetItem(QString("ACTIVE")));
        setHorizontalHeaderItem(3, new QTableWidgetItem(QString("GPS Sat")));
        setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Battery V")));
        setHorizontalHeaderItem(5, new QTableWidgetItem(QString("Battery A")));

        QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(VehicleID));
        QTableWidgetItem *item1 = new QTableWidgetItem("~");
        QTableWidgetItem *item2 = new QTableWidgetItem("~");
        QTableWidgetItem *item3 = new QTableWidgetItem("~");
        QTableWidgetItem *item4 = new QTableWidgetItem("~");
        QTableWidgetItem *item5 = new QTableWidgetItem("~");

        item0->setTextAlignment(Qt::AlignCenter);
        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);

        setItem(row_number,0,item0);
        setItem(row_number,1,item1);
        setItem(row_number,2,item2);
        setItem(row_number,3,item3);
        setItem(row_number,4,item4);
        setItem(row_number,5,item5);


        TableEntry newEntry;
        newEntry.Vehicle_ID = item0;
        newEntry.Connection = item1;
        newEntry.Armed = item2;
        newEntry.GPS_Number = item3;
        newEntry.Battery_V = item4;
        newEntry.Battery_A = item5;

        m_VehicleInformationP.insert(VehicleID,newEntry);
        return true;
    }

    return false;

}

void TableStatusWidget::removeEntry(const int &VehicleID)
{
    int row_number = 0;

    for(int i = 0; i < this->rowCount(); i++)
    {
        if(this->item(i,0)->text() == QString::number(VehicleID))
            row_number = i;
    }

    delete(m_VehicleInformationP[VehicleID].Armed);
    delete(m_VehicleInformationP[VehicleID].Battery_A);
    delete(m_VehicleInformationP[VehicleID].Battery_V);
    delete(m_VehicleInformationP[VehicleID].Connection);
    delete(m_VehicleInformationP[VehicleID].GPS_Number);
    delete(m_VehicleInformationP[VehicleID].Vehicle_ID);

    m_VehicleInformationFull.remove(VehicleID);
    m_VehicleInformationP.remove(VehicleID);
    this->removeRow(row_number);
}


//!
//! \brief Change the latency of a row
//! \param entryName Row to change latency of
//! \param latency number to change to
//!
void TableStatusWidget::ChangeConnection(const int &VehicleID, const bool &Connection)
{
    QString valid;
    QColor bgcolor;

    if(!m_VehicleInformationP.contains(VehicleID))
        return;
    if(Connection == true)
    {
        valid = "GOOD";
        bgcolor = Qt::green;
        m_VehicleInformationP[VehicleID].Connection->setText(valid);
        m_VehicleInformationP[VehicleID].Connection->setBackgroundColor(bgcolor);
    }
    else
    {
        valid = "LOST";
        bgcolor = Qt::red;
        m_VehicleInformationP[VehicleID].Connection->setText(valid);
        m_VehicleInformationP[VehicleID].Connection->setBackgroundColor(bgcolor);
    }
}

void TableStatusWidget::ChangeArmed(const int &VehicleID, const bool &ArmStatus)
{
    QString valid;

    if(!m_VehicleInformationP.contains(VehicleID))
        return;
    if(ArmStatus == true)
    {
        valid = "ARMED";
        m_VehicleInformationP[VehicleID].Armed->setText(valid);
    }
    else
    {
        valid = "DISARMED";
        m_VehicleInformationP[VehicleID].Armed->setText(valid);
    }

}

void TableStatusWidget::updateElapsedTime(const int VehicleID, const int elapsedTime)
{
    if(!m_VehicleInformationP.contains(VehicleID))
        return;
    m_VehicleInformationP[VehicleID].Connection->setText(QString::number(elapsedTime));
    QColor color;
    color = Qt::green;
    if(elapsedTime < 2000)
        m_VehicleInformationP[VehicleID].Connection->setBackgroundColor(color);
    else if((elapsedTime >= 2000) && (elapsedTime <= 5000))
    {
         color = Qt::yellow;
         m_VehicleInformationP[VehicleID].Connection->setBackgroundColor(color);
    }
    else if(elapsedTime >5000)
    {
         color = Qt::red;
         m_VehicleInformationP[VehicleID].Connection->setBackgroundColor(color);
    }

}

void TableStatusWidget::ChangeBatteryVoltage(const mavlink_common::SYS_STATUS &status)
{
    int VehicleID = status.sysid;
    if(!m_VehicleInformationP.contains(VehicleID))
        return;

    m_VehicleInformationP[VehicleID].Battery_V->setText(QString::number(status.voltage_battery / 1000.0));
    m_VehicleInformationP[VehicleID].Battery_A->setText(QString::number(status.current_battery / 10000.0));

    m_VehicleInformationFull[VehicleID].Battery_V = status.voltage_battery / 1000.0;
    m_VehicleInformationFull[VehicleID].Battery_A = status.current_battery / 10000.0;

    double battery_voltage = status.voltage_battery / 1000.0;
    double battery_current = status.current_battery / 10000.0;

    //Check battery voltage and update background
    if(battery_voltage > (3.7 * m_VehicleInformationFull[VehicleID].Cell_Count))
    {
        m_VehicleInformationP[VehicleID].Battery_V->setBackgroundColor(Qt::white);
    }

    else if(battery_voltage > (3.2 * m_VehicleInformationFull[VehicleID].Cell_Count))
    {
        m_VehicleInformationP[VehicleID].Battery_V->setBackgroundColor(Qt::yellow);
    }

    else
    {
        m_VehicleInformationP[VehicleID].Battery_V->setBackgroundColor(Qt::red);
    }

    //Check amperage consumption and update background
//    if(battery_current < (m_VehicleInformationFull[VehicleID].Battery_A - 0.25 * m_VehicleInformationFull[VehicleID].Battery_A))
//    {
//        m_VehicleInformationP[VehicleID].Battery_V->setBackgroundColor(Qt::white);
//    }

//    else if(status.voltage_battery < (m_VehicleInformationFull[VehicleID].Battery_A - 0.1 * m_VehicleInformationFull[VehicleID].Battery_A))
//    {
//        m_VehicleInformationP[VehicleID].Battery_V->setBackgroundColor(Qt::yellow);
//    }

//    else
//    {
//        m_VehicleInformationP[VehicleID].Battery_V->setBackgroundColor(Qt::red);
//    }


}


void TableStatusWidget::ChangeSatellite(const mavlink_common::GPS_RAW_INT &status)
{
    int VehicleID = status.sysid;
    if(!m_VehicleInformationP.contains(VehicleID))
        return;

    m_VehicleInformationP[VehicleID].GPS_Number->setText(QString::number(status.satellites_visible));

    switch(status.fix_type)
    {
    case 3:
        m_VehicleInformationP[VehicleID].GPS_Number->setBackgroundColor(Qt::green);
        break;
    case 2:
        m_VehicleInformationP[VehicleID].GPS_Number->setBackgroundColor(Qt::yellow);
        break;
    default:
        m_VehicleInformationP[VehicleID].GPS_Number->setBackgroundColor(Qt::red);
        break;
    }

    m_VehicleInformationFull[VehicleID].GPS_Sat = status.satellites_visible;
    m_VehicleInformationFull[VehicleID].GPSFix = status.fix_type;
}

void TableStatusWidget::ChangeBatteryLow(const int &VehicleID, const double &VoltageLow)
{
    if(!m_VehicleInformationFull.contains(VehicleID))
        return;

    m_VehicleInformationFull[VehicleID].Cell_Count = VoltageLow;
}

void TableStatusWidget::ChangeAmpHigh(const int &VehicleID, const double &AmperageHigh)
{
    if(!m_VehicleInformationFull.contains(VehicleID))
        return;

    m_VehicleInformationFull[VehicleID].Battery_AH = AmperageHigh;
}
