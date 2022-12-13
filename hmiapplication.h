#ifndef HMIAPPLICATION_H
#define HMIAPPLICATION_H

#include <AppMsgDef.h>
#include <AppNameDef.h>
#include <AppRoleDef.h>
#include <WindowNameDef.h>
#include <appmanagerservice.h>

class HMIApplication
{
    AppManagerService* m_appManagerService;
public:
    HMIApplication();
    void initialize();
    void sourceHMIDummyData();
    void nonOverlayHMIDummyData();
    void overlayHMIDummyData();
};

#endif // HMIAPPLICATION_H
