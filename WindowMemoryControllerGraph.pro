TEMPLATE = app
CONFIG += console c++11
QT += network

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

DEFINES += ENABLE_SERVICE

INCLUDEPATH += ../HomeDemo/utils \
    appservice/libapp/include \
    appservice/interface \
    appservice/

SOURCES += main.cpp \
    ../HomeDemo/utils/loghandler.cpp \
    appmain.cpp \
    appservice/appmanagerservice.cpp \
    appservice/appstackmanager.cpp \
    appservice/interface/service/BaseAppDeploy.cpp \
    appservice/interface/service/IBaseAppService.cpp \
    appservice/libapp/src/AppProxy.cpp \
    appservice/libapp/src/IOnAppListener.cpp \
    systemservice/systemservice.cpp \
    ipc/ipctransceiver.cpp \
    graph.cpp \
    utils/statisticlogger.cpp \
    utils/stringhelper.cpp \
    windowservice/windowservice.cpp

HEADERS += \
    appmain.h \
    appservice/AppNameDef.h \
    appservice/AppRoleDef.h \
    appservice/appmanagerservice.h \
    appservice/interface/AppMsgDef.h \
    appservice/interface/IApp.h \
    appservice/appstackmanager.h \
    appservice/interface/proxy/BaseAppMsgDef.h \
    appservice/interface/service/BaseAppDeploy.h \
    appservice/interface/service/IBaseAppService.h \
    appservice/libapp/include/AppProxy.h \
    appservice/libapp/include/IOnAppListener.h \
    systemservice/systemservice.h \
    ipc/ipctransceiver.h \
    graph.h \
    utils/singleton.h \
    utils/statisticlogger.h \
    utils/stringhelper.h \
    utils/throttler.h \
    windowservice/windowservice.h

RESOURCES += \
    data/data.qrc
