#include "swarmcontroller_gui.h"
#include <QApplication>
#include <QGraphicsSvgItem>
#include <QMetaType>

int main(int argc, char *argv[])
{

    ros::init(argc,argv,"Swarm_GUI");

    QApplication a(argc, argv);

    qRegisterMetaType<mavlink_common::HEARTBEAT>("mavlink_common::HEARTBEAT");
    qRegisterMetaType<mavlink_common::ATTITUDE>("mavlink_common::ATTITUDE");
    qRegisterMetaType<mavlink_common::GPS_RAW_INT>("mavlink_common::GPS_RAW_INT");
    qRegisterMetaType<mavlink_common::GLOBAL_POSITION_INT>("mavlink_common::GLOBAL_POSITION_INT");
    qRegisterMetaType<mavlink_common::SYS_STATUS>("mavlink_common::SYS_STATUS");
    qRegisterMetaType<mavlink_common::RC_CHANNELS_RAW>("mavlink_common::RC_CHANNELS_RAW");
    qRegisterMetaType<sensor_msgs::Joy>("sensor_msgs::Joy");
    SwarmController_GUI w;
    w.show();

    return a.exec();
}
