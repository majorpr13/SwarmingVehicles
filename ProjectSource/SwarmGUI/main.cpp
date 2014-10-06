#include "swarmcontroller_gui.h"
#include <QApplication>
#include <QGraphicsSvgItem>
#include <QMetaType>
#include "gps_position.h"
#include "parameterrequestwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef ROS_LIBS
    ros::init(argc,argv,"Swarm_GUI");

    qRegisterMetaType<mavlink_common::HEARTBEAT>("mavlink_common::HEARTBEAT");
    qRegisterMetaType<mavlink_common::ATTITUDE>("mavlink_common::ATTITUDE");
    qRegisterMetaType<mavlink_common::GPS_RAW_INT>("mavlink_common::GPS_RAW_INT");
    qRegisterMetaType<mavlink_common::GLOBAL_POSITION_INT>("mavlink_common::GLOBAL_POSITION_INT");
    qRegisterMetaType<mavlink_common::SYS_STATUS>("mavlink_common::SYS_STATUS");
    qRegisterMetaType<mavlink_common::RC_CHANNELS_RAW>("mavlink_common::RC_CHANNELS_RAW");
    qRegisterMetaType<mavlink_common::PARAM_REQUEST_READ>("mavlink_common::PARAM_REQUEST_READ");
    qRegisterMetaType<mavlink_common::PARAM_VALUE>("mavlink_common::PARAM_VALUE");

    qRegisterMetaType<sensor_msgs::Joy>("sensor_msgs::Joy");

#endif

//    SwarmController_GUI w;
//    w.show();

    parameterRequestWindow w;
    w.show();

    return a.exec();
}
