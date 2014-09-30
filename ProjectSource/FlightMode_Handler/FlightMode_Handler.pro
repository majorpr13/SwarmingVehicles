#-------------------------------------------------
#
# Project created by QtCreator 2014-09-30T08:21:43
#
#-------------------------------------------------

QT       -= gui

TARGET = FlightMode_Handler
TEMPLATE = lib

win32:TARGET_EXT += .dll

DEFINES += FLIGHTMODE_HANDLER_LIBRARY

SOURCES += flightmode_handler.cpp

HEADERS += flightmode_handler.h\
        FlightMode_Handler_global.h

# Unix lib Install
unix:!symbian {
    target.path = $$(FLIGHTVIEW_ROOT)/lib
    INSTALLS += target
}

# Windows lib install
lib.path    = $$(FLIGHTVIEW_ROOT)/lib
win32:CONFIG(release, debug|release):       lib.files   += release/GPS_Position.lib release/flightmode_handler.dll
else:win32:CONFIG(debug, debug|release):    lib.files   += debug/GPS_Position.lib debug/flightmode_handler.dll
INSTALLS += lib

#Header file copy
headers.path    = $$(FLIGHTVIEW_ROOT)/include
headers.files   += $$HEADERS
INSTALLS       += headers

INCLUDEPATH += $$(FLIGHTVIEW_ROOT)/include
