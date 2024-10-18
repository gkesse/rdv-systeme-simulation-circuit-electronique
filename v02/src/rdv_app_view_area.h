#pragma once

#include "rdv_app_view.h"

class ViewContainer;

class ViewArea : public QSplitter
{
    Q_OBJECT

public:
    ViewArea(QWidget *parent, ViewContainer *viewContainer, int id, bool showOpenButton);
    ~ViewArea() override;
    View *view() const;

private:
    QPointer<View> p_view;
};
