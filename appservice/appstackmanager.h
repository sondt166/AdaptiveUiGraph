#ifndef APPSTACKMANAGER_H
#define APPSTACKMANAGER_H

#include <QObject>
#include <QList>

#include "AppMsgDef.h"
#include "AppNameDef.h"
#include "AppRoleDef.h"
#include "WindowNameDef.h"

#include "utils/singleton.h"

class AppStackManager : public QObject
{
    Q_OBJECT
    MAKE_SINGLETON(AppStackManager);
public:

    const QList<AppData> &appStack() const;
    const AppData foreground() const;
    const AppData currentNormalApp() const;

    void openApp(const AppData &_app);
    void hideApp(const QString &_appName, const QString &_appRole);
    void goHome();
    void goBack();
    void clear();

    AppData find(const QString &_appName, const QString &_appRole) const;

signals:
    void sigForegroundAppChanged();
    void sigAppStackChanged();

private:
    void removeAll(const AppData &_app);

    AppData m_overlayApp {};
    QList<AppData> m_normalAppStack {};
};

#endif // APPSTACKMANAGER_H
