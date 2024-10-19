#pragma once

#include "rdv_app_include.h"

namespace KateMDI
{
    class MainWindow;
    class Splitter;
    class ToolView;

    class Sidebar : public KMultiTabBar
    {
        Q_OBJECT

    public:
        Sidebar(KMultiTabBar::KMultiTabBarPosition pos, MainWindow *mainwin, QWidget *parent);
        ~Sidebar() override;
        void setSplitter(Splitter *sp);
        void setSidebarStyle(KMultiTabBarStyle style);
        ToolView *addWidget(const QIcon &icon, const QString &text, ToolView *widget);
        bool removeWidget(ToolView *widget);
        bool showWidget(ToolView *widget);
        bool hideWidget(ToolView *widget);
        void updateLastSize();
        void updateMinimumSize();

        KMultiTabBar::KMultiTabBarPosition sidebarPosition() const { return m_pos; }
        KMultiTabBar::KMultiTabBarStyle sidebarTabStyle() const { return m_sidebarTabStyle; }

    private slots:
        void tabClicked(int);

    private:
        MainWindow *m_mainWin;
        Splitter *m_splitter;
        KMultiTabBar *m_tabBar;
        Splitter *m_ownSplit;
        int m_lastSize;
        KMultiTabBar::KMultiTabBarPosition m_pos;
        KMultiTabBar::KMultiTabBarStyle m_sidebarTabStyle;
        QMap<ToolView *, int> m_widgetToId;
        QMap<int, ToolView *> m_idToWidget;
        QList<ToolView *> m_toolviews;
    };
}
