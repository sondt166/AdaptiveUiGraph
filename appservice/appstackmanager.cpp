#include "appstackmanager.h"

#include <algorithm>

#include <QMetaType>
#include <QDebug>

const QList<AppData> &AppStackManager::appStack() const
{
    return m_normalAppStack;
}

const AppData AppStackManager::foreground() const
{
    const AppData home(HMI_APP_NAME_HOME, HMI_ROLE_HOME,
                       WIN_NAME_HOME, E_SHOW_OPT_CLEAR_AND_ADD);

    if (!m_overlayApp.empty()) {
        return m_overlayApp;
    }

    if (m_normalAppStack.length() > 0) {
        return m_normalAppStack.last();
    }

    return home;
}

const AppData AppStackManager::currentNormalApp() const
{
    if (m_normalAppStack.empty()) {
        return {};
    }
    return m_normalAppStack.last();
}

void AppStackManager::openApp(const AppData &_app)
{
    const auto showOpt = _app.showOption();
    const auto fg = foreground();

    if (_app == fg) {
        return;
    }

    if (_app.sameRole(HMI_APP_NAME_HOME, HMI_ROLE_HOME)) {
        return goHome();
    }

    // close current overlay first
    if (!m_overlayApp.empty()) {
        m_overlayApp.clear();
    }

    switch (showOpt) {
    case E_SHOW_OPT_ADD:
        // add new app to the list
        m_normalAppStack.append(_app);
        emit sigAppStackChanged();
        break;

    case E_SHOW_OPT_ADD_OVERLAY:
        m_overlayApp = _app;
        break;

    case E_SHOW_OPT_CLEAR_DUPLICATE_AND_ADD:
        // NOTE: clear items which is EXTRACTLY the same (name, role, windowName, showOpt)
        m_normalAppStack.erase(std::remove(m_normalAppStack.begin(),
                                           m_normalAppStack.end(),
                                           _app));
        m_normalAppStack.append(_app);
        emit sigAppStackChanged();
        break;

    case E_SHOW_OPT_CLEAR_AND_ADD:
        m_normalAppStack.clear();
        m_normalAppStack.append(_app);
        emit sigAppStackChanged();
        break;

    default:
        break;
    }

    if (fg != foreground()) {
        emit sigForegroundAppChanged();
    }
}

void AppStackManager::hideApp(const QString &_appName, const QString &_appRole)
{
    const auto fg = foreground();

    if (fg.sameRole(_appName, _appRole)) {
        goBack();
        return;
    }

    removeAll(find(_appName, _appRole));
}

void AppStackManager::goHome()
{
    qDebug();
    const auto fg = foreground();

    m_overlayApp.clear();
    m_normalAppStack.clear();

    if (fg != foreground()) {
        emit sigForegroundAppChanged();
    }
    emit sigAppStackChanged();
}

void AppStackManager::goBack()
{
    const auto fg = foreground();

    if (!m_overlayApp.empty()) {
        m_overlayApp.clear();
    } else {
        if (m_normalAppStack.length() > 0) {
            m_normalAppStack.removeLast();
        }
    }

    if (fg != foreground()) {
        emit sigForegroundAppChanged();
    }
}

void AppStackManager::removeAll(const AppData &_app)
{
    // overlay?
    if (_app.isOverlay()) {
        if (_app == m_overlayApp) {
            m_overlayApp.clear();
            emit sigForegroundAppChanged();
        } else {
            // do nothing
        }
        return;
    }

    const auto fg = foreground();

    // normal app?
    m_normalAppStack.erase(std::remove(m_normalAppStack.begin(),
                                       m_normalAppStack.end(),
                                       _app));
    emit sigAppStackChanged();

    if (fg != foreground()) {
        emit sigForegroundAppChanged();
    }
}

AppData AppStackManager::find(const QString &_appName, const QString &_appRole) const
{
    if (m_overlayApp.sameRole(_appName, _appRole)) {
        return m_overlayApp;
    }
    auto result = std::find_if(m_normalAppStack.begin(), m_normalAppStack.end(),
                               [_appName, _appRole](const AppData &_item) -> bool {
        return _item.sameRole(_appName, _appRole);
    });
    if (result != m_normalAppStack.end()) {
        return *result;
    }
    return AppData();
}

void AppStackManager::clear()
{
    bool appStackChanged = false;

    if (!m_normalAppStack.empty()) {
        appStackChanged = true;
        m_normalAppStack.clear();
    }

    emit sigForegroundAppChanged();

    if (appStackChanged) {
        emit sigAppStackChanged();
    }

    m_overlayApp.clear();
}
