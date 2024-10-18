#pragma once

#include "rdv_app_document.h"

class ViewContainer;

class View : public QWidget, public KXMLGUIClient
{
    Q_OBJECT

public:
    View(Document *document, ViewContainer *viewContainer, uint viewAreaId);
    ~View() override;
    Document *document() const;

protected:
    QPointer<Document> m_pDocument;
};
