#include "rdv_app_view_area.h"
#include "rdv_app_view_container.h"

ViewArea::ViewArea(QWidget *parent, ViewContainer *viewContainer, int id, bool showOpenButton)
    : QSplitter(parent)
{
}

ViewArea::~ViewArea()
{
}

View *ViewArea::view() const
{
    return p_view;
}
