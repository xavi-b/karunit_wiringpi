TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += qml quick xml
TARGET          = karunit_wiringpi_plugin
DESTDIR         = $$PWD/../karunit/app/plugins

unix {
target.path = /usr/local/bin/plugins
INSTALLS += target
}

LIBS += -lwiringPi

WiringPi.target = /usr/local/lib/libwiringPi.so
WiringPi.commands += cd $$PWD/third-party/WiringPi && ./build
QMAKE_EXTRA_TARGETS += WiringPi
PRE_TARGETDEPS += $$WiringPi.target

LIBS += -L/usr/local/lib/ -lwiringPi
INCLUDEPATH += $$PWD/third-party/WiringPi

LIBS += -L$$PWD/../karunit/plugininterface/ -lkarunit_plugininterface
INCLUDEPATH += $$PWD/../karunit/plugininterface

LIBS += -L$$PWD/../karunit/common/ -lkarunit_common
INCLUDEPATH += $$PWD/../karunit/common

LIBS += -L$$PWD/../karunit/third-party/xblog/lib -lxblog
INCLUDEPATH += $$PWD/../karunit/third-party/xblog/include

SUBDIRS += \
    src/ \
    res/

include(src/src.pri)
include(res/res.pri)
