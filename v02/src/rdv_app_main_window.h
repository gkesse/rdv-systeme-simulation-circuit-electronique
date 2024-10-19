#pragma once

#include "rdv_app_include.h"

namespace KateMDI
{
    class Sidebar;
    class Splitter;
    class ToolView;
    class GUIClient;

    class MainWindow : public KParts::MainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;
        void setToolViewStyle(KMultiTabBar::KMultiTabBarStyle style);
        ToolView *createToolView(const QString &identifier, KMultiTabBar::KMultiTabBarPosition pos, const QIcon &icon, const QString &text);
        void updateSidebarMinimumSizes();

    private:
        Sidebar *m_sidebars[4];
        Splitter *m_hSplitter;
        Splitter *m_vSplitter;
        QWidget *m_centralWidget;
        QList<ToolView *> m_toolviews;
        QMap<QString, ToolView *> m_idToWidget;
        KConfig *m_restoreConfig;
        QString m_restoreGroup;
        GUIClient *m_guiClient;
    };
}
