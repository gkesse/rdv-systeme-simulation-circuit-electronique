#include "rdv_app_doc_manager.h"

DocManager *DocManager::m_pSelf = nullptr;

DocManager::DocManager(QObject *parent)
    : QObject(parent)
{
}

DocManager::~DocManager()
{
}

DocManager *DocManager::self()
{
    if (!m_pSelf)
        m_pSelf = new DocManager();

    return m_pSelf;
}

Document *DocManager::openURL(const QUrl &url, ViewArea *viewArea)
{
    if (url.isEmpty())
        return nullptr;

    if (url.isLocalFile())
    {
        QFile file(url.toLocalFile());
        if (file.open(QIODevice::ReadOnly) == false)
        {
            KMessageBox::error(nullptr, i18n("Could not open '%1'", file.fileName()));
            return nullptr;
        }
        file.close();
    }

    return nullptr;
}
