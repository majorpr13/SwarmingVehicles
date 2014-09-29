#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T16:28:50
#
#-------------------------------------------------

QT       -= gui

TARGET = RC_Handler
TEMPLATE = lib

win32:TARGET_EXT += .dll

DEFINES += RC_HANDLER_LIBRARY

SOURCES += rc_handler.cpp

HEADERS += rc_handler.h\
        RC_Handler_global.h

# Unix lib Install
unix:!symbian {
    target.path = $$(FLIGHTVIEW_ROOT)/lib
    INSTALLS += target
}

# Windows lib install
lib.path    = $$(FLIGHTVIEW_ROOT)/lib
win32:CONFIG(release, debug|release):       lib.files   += release/RC_Handler.lib release/RC_Handler.dll
else:win32:CONFIG(debug, debug|release):    lib.files   += debug/RC_Handler.lib debug/RC_Handler.dll
INSTALLS += lib

#Header file copy
headers.path    = $$(FLIGHTVIEW_ROOT)/include
headers.files   += $$HEADERS
INSTALLS       += headers

INCLUDEPATH += $$(FLIGHTVIEW_ROOT)/include

