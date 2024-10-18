#include "rdv_app_view.h"
#include "rdv_app_view_container.h"
#include "rdv_app_view_area.h"

View::View(Document *document, ViewContainer *viewContainer, uint viewAreaId)
    : QWidget(viewContainer->viewArea(viewAreaId)), KXMLGUIClient()
{
    setObjectName("view_" + QString::number(viewAreaId));
}

View::~View()
{
}

Document *View::document() const
{
    return m_pDocument;
}
