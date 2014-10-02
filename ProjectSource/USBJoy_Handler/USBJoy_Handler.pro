#-------------------------------------------------
#
# Project created by QtCreator 2014-10-02T12:14:53
#
#-------------------------------------------------

QT       -= gui

TARGET = USBJoy_Handler
TEMPLATE = lib

win32:TARGET_EXT += .dll

DEFINES += USBJOY_HANDLER_LIBRARY

SOURCES += usbjoy_handler.cpp

HEADERS += usbjoy_handler.h\
        USBJoy_Handler_global.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../RC_Handler/release/ -lRC_Handler
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../RC_Handler/debug/ -lRC_Handler
else:unix:!macx:!symbian: LIBS += -L$$OUT_PWD/../RC_Handler/ -lRC_Handler

INCLUDEPATH += $$PWD/../RC_Handler
DEPENDPATH += $$PWD/../RC_Handler

# Unix lib Install
unix:!symbian {
    target.path = $$(FLIGHTVIEW_ROOT)/lib
    INSTALLS += target
}

# Windows lib install
lib.path    = $$(FLIGHTVIEW_ROOT)/lib
win32:CONFIG(release, debug|release):       lib.files   += release/usbjoy_handler.lib release/usbjoy_handler.dll
else:win32:CONFIG(debug, debug|release):    lib.files   += debug/usbjoy_handler.lib debug/usbjoy_handler.dll
INSTALLS += lib

#Header file copy
headers.path    = $$(FLIGHTVIEW_ROOT)/include
headers.files   += $$HEADERS
INSTALLS       += headers

INCLUDEPATH += $$(FLIGHTVIEW_ROOT)/include


