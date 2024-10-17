#include "rdv_app_readyspice.h"
#include "rdv_app_view_area.h"
#include "rdv_app_project_manager.h"
#include "rdv_app_doc_manager.h"

ReadySpice::ReadySpice(QWidget *parent)
    : KateMDI::MainWindow(parent)
{
}

ReadySpice::~ReadySpice()
{
}

void ReadySpice::load(const QUrl &url, ViewArea *viewArea)
{
    if (!url.isValid())
        return;

    loadInternal(url, false, viewArea);
}

void ReadySpice::loadInternal(const QUrl &url, bool isRecent, ViewArea *viewArea)
{
    if (url.fileName().endsWith(".readyspice", Qt::CaseInsensitive))
    {
        ProjectManager::self()->slotOpenProject(url);
        return;
    }

    if (!isRecent)
        addRecentFile(url);

    // setCaption(url.toDisplayString(QUrl::PreferLocalFile));
    DocManager::self()->openURL(url, viewArea);
}

void ReadySpice::addRecentFile(const QUrl &url)
{
}
