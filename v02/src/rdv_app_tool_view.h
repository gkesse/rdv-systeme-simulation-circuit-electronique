#pragma once

#include "rdv_app_include.h"

namespace KateMDI
{
    class MainWindow;

    class ToolView : public QWidget
    {
        Q_OBJECT

        friend class Sidebar;
        friend class MainWindow;
        friend class GUIClient;

    protected:
        ToolView(MainWindow *mainwin, class Sidebar *sidebar, QWidget *parent);

    public:
        ~ToolView() override;

    protected:
        void setVisibleToolView(bool vis);

        Sidebar *sidebar() { return m_sidebar; }

    signals:
        void visibleChanged(bool visible);

    private:
        Sidebar *m_sidebar;
        MainWindow *m_mainWin;
        bool m_visible;
        bool persistent;
        QIcon icon;
        QString text;
        QString id;
    };
}