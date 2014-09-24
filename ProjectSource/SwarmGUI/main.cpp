#include "swarmcontroller_gui.h"
#include <QApplication>
#include <QGraphicsSvgItem>
#include <QMetaType>

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

    qRegisterMetaType<sensor_msgs::Joy>("sensor_msgs::Joy");

#endif

    SwarmController_GUI w;
    w.show();

//    std::cout<<"I got into here."<<std::endl;
//    QString msgString = "CH8_OPT";
//    boost::array<u_int8_t, 16> stringArray;

//    QByteArray ba = msgString.toLocal8Bit();
//    const char *c_str2 = ba.data();
//    std::cout<<"The original message: "<<c_str2<<std::endl;
//    std::cout<<"The length of the byte array: "<<ba.length()<<std::endl;
//    for(int i = 0; i < ba.length(); i++)
//    {
//        stringArray[i] = ba.at(i);
//    }


//    for(int i = 0; i < stringArray.size(); i++)
//    {
//        ba[i] = stringArray.at(i);
//    }
//    QString newString(ba);
//    std::cout<<newString.toStdString()<<std::endl;

    return a.exec();
}
