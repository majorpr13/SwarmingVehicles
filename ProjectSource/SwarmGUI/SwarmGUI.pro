#-------------------------------------------------
#
# Project created by QtCreator 2014-09-08T12:38:05
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SwarmGUI
TEMPLATE = app


SOURCES += main.cpp\
    swarmcontroller_gui.cpp \
    table_status_widget.cpp \
    table_widget_item_status.cpp \
    vehicledatadisplay.cpp \
    rosparse.cpp \
    vehiclestate.cpp \
    heartbeattimer.cpp \
    initialization.cpp \
    conversions.cpp \
    cmdconversions.cpp

HEADERS  += swarmcontroller_gui.h \
    table_status_widget.h \
    table_widget_item_status.h \
    vehicledatadisplay.h \
    rosparse.h \
    vehiclestate.h \
    heartbeattimer.h \
    Definitions.h \
    initialization.h \
    conversions.h \
    cmdconversions.h

FORMS    += swarmcontroller_gui.ui \
    vehicledatadisplay.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QTFlightView/release/ -lQTFlightView
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QTFlightView/debug/ -lQTFlightView
else:unix:!macx: LIBS += -L$$OUT_PWD/../QTFlightView/ -lQTFlightView

INCLUDEPATH += $$PWD/../QTFlightView
DEPENDPATH += $$PWD/../QTFlightView
INCLUDEPATH += $$PWD/../include


INCLUDEPATH += /home/scoriolinux/catkin_ws/devel/include
INCLUDEPATH += /home/scoriolinux/catkin_ws/src/Ardupilot_ROS/ardupilotmega-ros/mavlink_ardupilotmega/include/mavlink_ardupilotmega


unix {
exists(/opt/ros/indigo/lib/) {

    DEFINES     += ROS_LIBS
    INCLUDEPATH += /opt/ros/indigo/include
    INCLUDEPATH += /opt/ros/indigo/lib

        LIBS += -L/opt/ros/indigo/lib -lroscpp
        LIBS += -L/opt/ros/indigo/lib -lroscpp_serialization
        LIBS += -L/opt/ros/indigo/lib -lrostime
        LIBS += -L/opt/ros/indigo/lib -lxmlrpcpp
        LIBS += -L/opt/ros/indigo/lib -lcpp_common
        LIBS += -L/opt/ros/indigo/lib -lrosconsole_log4cxx
        LIBS += -L/opt/ros/indigo/lib -lrosconsole_backend_interface
        LIBS += -L/opt/ros/indigo/lib -lroslib
        LIBS += -L/opt/ros/indigo/lib -lrospack
        LIBS += -L/opt/ros/indigo/lib -lmessage_filters
        LIBS += -L/opt/ros/indigo/lib -lclass_loader
        LIBS += -L/opt/ros/indigo/lib -lconsole_bridge
        LIBS += -L/opt/ros/indigo/lib -lrosconsole
        LIBS += -L/opt/ros/indigo/lib -limage_transport
        LIBS += -L/opt/ros/indigo/lib -lcv_bridge

}
}
