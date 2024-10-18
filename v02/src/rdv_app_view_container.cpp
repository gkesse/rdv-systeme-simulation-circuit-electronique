#include "rdv_app_view_container.h"
#include "rdv_app_readyspice.h"
#include "rdv_app_view_area.h"

ViewContainer::ViewContainer(const QString &caption, QWidget *parent)
    : QWidget(parent ? parent : ReadySpice::self()->tabWidget())
{
}

ViewContainer::~ViewContainer()
{
}

ViewArea *ViewContainer::viewArea(uint id) const
{
    if (!m_viewAreaMap.contains(id))
        return nullptr;

    return m_viewAreaMap[id];
}

uint ViewContainer::activeViewArea() const
{
    return m_activeViewArea;
}

View *ViewContainer::view() const
{
    return p_view;
}

uint ViewContainer::viewCount() const
{
    return m_viewAreaMap.size();
}

View *ViewContainer::activeView() const
{
    return view(activeViewArea());
}

View *ViewContainer::view(uint id) const
{
    ViewArea *va = viewArea(id);
    if (!va)
        return nullptr;

    QList<View *> l = va->findChildren<View *>();
    View *view = nullptr;
    if (!l.isEmpty())
        view = dynamic_cast<View *>(l.first());

    return view;
}

bool ViewContainer::closeViewContainer()
{
    bool didClose = true;
    while (didClose && !m_viewAreaMap.isEmpty())
    {
        didClose = closeViewArea(m_viewAreaMap.begin().key());
    }

    return m_viewAreaMap.isEmpty();
}

bool ViewContainer::closeViewArea(uint id)
{
    return false;
}
