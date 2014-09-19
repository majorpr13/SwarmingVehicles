#-------------------------------------------------
#
# Project created by QtCreator 2014-09-08T16:53:36
#
#-------------------------------------------------

#QT       -= gui

QT += widgets svg

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg

#lessThan(QT_MAJOR_VERSION, 5): QT += gui

TARGET = QTFlightView
TEMPLATE = lib

unix:QMAKE_CXXFLAGS += -std=gnu++0x

win32:TARGET_EXT += .dll

DEFINES += QTFLIGHTVIEW_LIBRARY

SOURCES += \
    qfi_ADI.cpp \
    qfi_ALT.cpp \
    qfi_ASI.cpp \
    qfi_HSI.cpp \
    qfi_PFD.cpp \
    qfi_TC.cpp \
    qfi_VSI.cpp \
    WidgetADI.cpp \
    WidgetALT.cpp \
    WidgetASI.cpp \
    WidgetHSI.cpp \
    WidgetPFD.cpp \
    WidgetSix.cpp \
    WidgetTC.cpp \
    WidgetVSI.cpp \
    LayoutSquare.cpp

HEADERS +=\
        qtflightview_global.h \
    qfi_ADI.h \
    qfi_ALT.h \
    qfi_ASI.h \
    qfi_HSI.h \
    qfi_PFD.h \
    qfi_TC.h \
    qfi_VSI.h \
    WidgetADI.h \
    WidgetALT.h \
    WidgetASI.h \
    WidgetHSI.h \
    WidgetPFD.h \
    WidgetSix.h \
    WidgetTC.h \
    WidgetVSI.h \
    LayoutSquare.h

FORMS += \
    MainWindow.ui \
    WidgetADI.ui \
    WidgetALT.ui \
    WidgetASI.ui \
    WidgetHSI.ui \
    WidgetPFD.ui \
    WidgetSix.ui \
    WidgetTC.ui \
    WidgetVSI.ui


# Unix lib Install
unix:!symbian {
    target.path = $$(FLIGHTVIEW_ROOT)/lib
    INSTALLS += target
}

# Windows lib install
lib.path    = $$(FLIGHTVIEW_ROOT)/lib
win32:CONFIG(release, debug|release):       lib.files   += release/qtflightview.lib release/qtflightview.dll
else:win32:CONFIG(debug, debug|release):    lib.files   += debug/qtflightview.lib debug/qtflightview.dll
INSTALLS += lib

headers.path    = $$(FLIGHTVIEW_ROOT)/include
headers.files   += $$HEADERS
INSTALLS       += headers
