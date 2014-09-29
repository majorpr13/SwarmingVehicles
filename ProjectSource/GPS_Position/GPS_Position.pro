#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T15:07:34
#
#-------------------------------------------------

QT       -= gui

TARGET = GPS_Position
TEMPLATE = lib

win32:TARGET_EXT += .dll

DEFINES += GPS_POSITION_LIBRARY

SOURCES += gps_position.cpp

HEADERS += gps_position.h\
        GPS_Position_global.h


# Unix lib Install
unix:!symbian {
    target.path = $$(FLIGHTVIEW_ROOT)/lib
    INSTALLS += target
}

# Windows lib install
lib.path    = $$(FLIGHTVIEW_ROOT)/lib
win32:CONFIG(release, debug|release):       lib.files   += release/GPS_Position.lib release/GPS_Position.dll
else:win32:CONFIG(debug, debug|release):    lib.files   += debug/GPS_Position.lib debug/GPS_Position.dll
INSTALLS += lib

#Header file copy
headers.path    = $$(FLIGHTVIEW_ROOT)/include
headers.files   += $$HEADERS
INSTALLS       += headers

INCLUDEPATH += $$(FLIGHTVIEW_ROOT)/include
