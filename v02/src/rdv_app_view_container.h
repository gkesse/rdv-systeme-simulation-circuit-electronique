#pragma once

#include "rdv_app_view.h"

class ViewArea;

typedef QMap<uint, ViewArea *> ViewAreaMap;

class ViewContainer : public QWidget
{
    Q_OBJECT

public:
    explicit ViewContainer(const QString &caption, QWidget *parent = nullptr);
    ~ViewContainer() override;
    ViewArea *viewArea(uint id) const;
    uint activeViewArea() const;
    View *view() const;
    uint viewCount() const;
    View *activeView() const;
    View *view(uint id) const;
    bool closeViewContainer();
    bool closeViewArea(uint id);

protected:
    ViewAreaMap m_viewAreaMap;
    int m_activeViewArea;
    QPointer<View> p_view;
};
