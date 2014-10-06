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


INCLUDEPATH += /home/dempsy/catkin_ws/devel/include
INCLUDEPATH += /home/dempsy/catkin_ws/src/Ardupilot_ROS/ardupilotmega-ros/mavlink_ardupilotmega/include/mavlink_ardupilotmega


unix {
exists(/opt/ros/hydro/lib/) {

    DEFINES     += ROS_LIBS
    INCLUDEPATH += /opt/ros/hydro/include
    INCLUDEPATH += /opt/ros/hydro/lib

        LIBS += -L/opt/ros/hydro/lib -lroscpp
        LIBS += -L/opt/ros/hydro/lib -lroscpp_serialization
        LIBS += -L/opt/ros/hydro/lib -lrostime
        LIBS += -L/opt/ros/hydro/lib -lxmlrpcpp
        LIBS += -L/opt/ros/hydro/lib -lcpp_common
        LIBS += -L/opt/ros/hydro/lib -lrosconsole_log4cxx
        LIBS += -L/opt/ros/hydro/lib -lrosconsole_backend_interface
        LIBS += -L/opt/ros/hydro/lib -lroslib
        LIBS += -L/opt/ros/hydro/lib -lrospack
        LIBS += -L/opt/ros/hydro/lib -lmessage_filters
        LIBS += -L/opt/ros/hydro/lib -lclass_loader
        LIBS += -L/opt/ros/hydro/lib -lconsole_bridge
        LIBS += -L/opt/ros/hydro/lib -lrosconsole
        LIBS += -L/opt/ros/hydro/lib -limage_transport
        LIBS += -L/opt/ros/hydro/lib -lcv_bridge

}
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GPS_Position/release/ -lGPS_Position
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GPS_Position/debug/ -lGPS_Position
else:unix:!macx:!symbian: LIBS += -L$$OUT_PWD/../GPS_Position/ -lGPS_Position

INCLUDEPATH += $$PWD/../GPS_Position
DEPENDPATH += $$PWD/../GPS_Position



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../USBJoy_Handler/release/ -lUSBJoy_Handler
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../USBJoy_Handler/debug/ -lUSBJoy_Handler
else:unix:!macx:!symbian: LIBS += -L$$OUT_PWD/../USBJoy_Handler/ -lUSBJoy_Handler

INCLUDEPATH += $$PWD/../USBJoy_Handler
DEPENDPATH += $$PWD/../USBJoy_Handler


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../RC_Handler/release/ -lRC_Handler
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../RC_Handler/debug/ -lRC_Handler
else:unix:!macx:!symbian: LIBS += -L$$OUT_PWD/../RC_Handler/ -lRC_Handler

INCLUDEPATH += $$PWD/../RC_Handler
DEPENDPATH += $$PWD/../RC_Handler

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Command_Helper/release/ -lCommand_Helper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Command_Helper/debug/ -lCommand_Helper
else:unix:!macx:!symbian: LIBS += -L$$OUT_PWD/../Command_Helper/ -lCommand_Helper

INCLUDEPATH += $$PWD/../Command_Helper
DEPENDPATH += $$PWD/../Command_Helper
