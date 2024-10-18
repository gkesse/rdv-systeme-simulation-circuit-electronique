#include "rdv_app_main_window.h"
#include "rdv_app_side_bar.h"
#include "rdv_app_splitter.h"
#include "rdv_app_tool_view.h"
#include "rdv_app_gui_client.h"

namespace KateMDI
{
    MainWindow::MainWindow(QWidget *parent)
        : KParts::MainWindow(parent)
    {
        QWidget *hb = new QWidget(this);
        QHBoxLayout *hbl = new QHBoxLayout;
        hb->setLayout(hbl);

        hb->setObjectName("MainWindow-central-HBox");
        setCentralWidget(hb);

        m_sidebars[KMultiTabBar::Left] = new Sidebar(KMultiTabBar::Left, this, hb);
        m_sidebars[KMultiTabBar::Left]->setObjectName("Main-Left-Sidebar");
        hbl->addWidget(m_sidebars[KMultiTabBar::Left]);

        m_hSplitter = new Splitter(Qt::Horizontal, hb);
        m_hSplitter->setObjectName("Main-Left-Splitter");
        hbl->addWidget(m_hSplitter);

        m_sidebars[KMultiTabBar::Left]->setSplitter(m_hSplitter);

        QWidget *vb = new QWidget(m_hSplitter);
        QVBoxLayout *vbl = new QVBoxLayout;
        vb->setLayout(vbl);
        vb->setObjectName("Main-Center-VBox");
        m_hSplitter->setCollapsible(m_hSplitter->indexOf(vb), false);

        m_sidebars[KMultiTabBar::Top] = new Sidebar(KMultiTabBar::Top, this, vb);
        m_sidebars[KMultiTabBar::Top]->setObjectName("Main-Top-Sidebar");
        vbl->addWidget(m_sidebars[KMultiTabBar::Top]);

        m_vSplitter = new Splitter(Qt::Vertical, vb);
        m_vSplitter->setObjectName("Main-Top-Splitter");
        vbl->addWidget(m_vSplitter);

        m_sidebars[KMultiTabBar::Top]->setSplitter(m_vSplitter);

        m_centralWidget = new QWidget(m_vSplitter);

        QVBoxLayout *vbCl = new QVBoxLayout;
        m_centralWidget->setLayout(vbCl);
        m_centralWidget->setObjectName("Main-Central-Vbox");
        m_vSplitter->setCollapsible(m_vSplitter->indexOf(m_centralWidget), false);

        m_sidebars[KMultiTabBar::Bottom] = new Sidebar(KMultiTabBar::Bottom, this, vb);
        m_sidebars[KMultiTabBar::Bottom]->setObjectName("Main-Bottom-Sidebar");
        m_sidebars[KMultiTabBar::Bottom]->setSplitter(m_vSplitter);
        vbl->addWidget(m_sidebars[KMultiTabBar::Bottom]);

        m_sidebars[KMultiTabBar::Right] = new Sidebar(KMultiTabBar::Right, this, hb);
        m_sidebars[KMultiTabBar::Right]->setObjectName("Main-Right-Sidebar");
        m_sidebars[KMultiTabBar::Right]->setSplitter(m_hSplitter);
        hbl->addWidget(m_sidebars[KMultiTabBar::Right]);
    }

    MainWindow::~MainWindow()
    {
        while (!m_toolviews.isEmpty())
            delete m_toolviews[0];

        delete m_centralWidget;

        for (unsigned int i = 0; i < 4; ++i)
            delete m_sidebars[i];
    }

    void MainWindow::setToolViewStyle(KMultiTabBar::KMultiTabBarStyle style)
    {
        m_sidebars[0]->setSidebarStyle(style);
        m_sidebars[1]->setSidebarStyle(style);
        m_sidebars[2]->setSidebarStyle(style);
        m_sidebars[3]->setSidebarStyle(style);
    }

    ToolView *MainWindow::createToolView(const QString &identifier, KMultiTabBar::KMultiTabBarPosition pos, const QIcon &icon, const QString &text)
    {
        if (m_idToWidget[identifier])
            return nullptr;

        if (m_restoreConfig && m_restoreConfig->hasGroup(m_restoreGroup))
        {
            KConfigGroup grRest = m_restoreConfig->group(m_restoreGroup);
            pos = KMultiTabBar::KMultiTabBarPosition(grRest.readEntry(QString("Kate-MDI-ToolView-%1-Position").arg(identifier), int(pos)));
        }

        ToolView *v = m_sidebars[pos]->addWidget(icon, text, nullptr);
        v->id = identifier;

        m_idToWidget.insert(identifier, v);
        m_toolviews.push_back(v);

        m_guiClient->registerToolView(v);

        return v;
    }
}
