#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T13:07:00
#
#-------------------------------------------------

QT       -= gui

TARGET = StreamMode_Handler
TEMPLATE = lib

win32:TARGET_EXT += .dll

DEFINES += STREAMMODE_HANDLER_LIBRARY

SOURCES += streammode_handler.cpp

HEADERS += streammode_handler.h\
        StreamMode_Handler_global.h

# Unix lib Install
unix:!symbian {
    target.path = $$(FLIGHTVIEW_ROOT)/lib
    INSTALLS += target
}

# Windows lib install
lib.path    = $$(FLIGHTVIEW_ROOT)/lib
win32:CONFIG(release, debug|release):       lib.files   += release/StreamMode_Handler.lib release/StreamMode_Handler.dll
else:win32:CONFIG(debug, debug|release):    lib.files   += debug/StreamMode_Handler.lib debug/StreamMode_Handler.dll
INSTALLS += lib

#Header file copy
headers.path    = $$(FLIGHTVIEW_ROOT)/include
headers.files   += $$HEADERS
INSTALLS       += headers

INCLUDEPATH += $$(FLIGHTVIEW_ROOT)/include
