#include "rdv_app_doc_manager.h"
#include "rdv_app_readyspice.h"
#include "rdv_app_view.h"
#include "rdv_app_view_area.h"
#include "rdv_app_view_container.h"
#include "rdv_app_circuit_document.h"
#include "rdv_app_flow_code_document.h"
#include "rdv_app_mechanics_document.h"
#include "rdv_app_text_document.h"
#include "rdv_app_document.h"

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

    if (!viewArea)
    {
        ViewContainer *currentVC = static_cast<ViewContainer *>(ReadySpice::self()->tabWidget()->currentWidget());

        if (currentVC)
        {
            ViewArea *va = currentVC->viewArea(currentVC->activeViewArea());
            if (!va->view())
                viewArea = va;
        }
    }

    Document *document = findDocument(url);

    if (document)
    {
        if (viewArea)
            createNewView(document, viewArea);
        else
            giveDocumentFocus(document, viewArea);
        return document;
    }

    QString fileName = url.fileName();
    QString extension = fileName.right(fileName.length() - fileName.lastIndexOf('.'));

    if (extension == ".circuit")
        return openCircuitFile(url, viewArea);
    else if (extension == ".flowcode")
        return openFlowCodeFile(url, viewArea);
    else if (extension == ".mechanics")
        return openMechanicsFile(url, viewArea);
    else
        return openTextFile(url, viewArea);
}

Document *DocManager::findDocument(const QUrl &url) const
{
    return nullptr;
}

View *DocManager::createNewView(Document *document, ViewArea *viewArea)
{
    return nullptr;
}

void DocManager::giveDocumentFocus(Document *toFocus, ViewArea *viewAreaForNew)
{
}

CircuitDocument *DocManager::openCircuitFile(const QUrl &url, ViewArea *viewArea)
{
    return nullptr;
}

FlowCodeDocument *DocManager::openFlowCodeFile(const QUrl &url, ViewArea *viewArea)
{
    return nullptr;
}

MechanicsDocument *DocManager::openMechanicsFile(const QUrl &url, ViewArea *viewArea)
{
    return nullptr;
}

TextDocument *DocManager::openTextFile(const QUrl &url, ViewArea *viewArea)
{
    return nullptr;
}