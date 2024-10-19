#include "rdv_app_side_bar.h"
#include "rdv_app_splitter.h"
#include "rdv_app_tool_view.h"
#include "rdv_app_main_window.h"

namespace KateMDI
{
    Sidebar::Sidebar(KMultiTabBar::KMultiTabBarPosition pos, MainWindow *mainwin, QWidget *parent)
        : KMultiTabBar(pos, parent), m_mainWin(mainwin), m_splitter(nullptr), m_ownSplit(nullptr), m_lastSize(0)
    {
    }

    Sidebar::~Sidebar()
    {
    }

    void Sidebar::setSplitter(Splitter *sp)
    {
        m_splitter = sp;
        Qt::Orientation splitOrient = (sidebarPosition() == KMultiTabBar::Top || sidebarPosition() == KMultiTabBar::Bottom) ? Qt::Horizontal : Qt::Vertical;
        m_ownSplit = new Splitter(splitOrient, m_splitter);
        m_ownSplit->setObjectName("own-Split");
        m_ownSplit->setChildrenCollapsible(false);
        m_splitter->setStretchFactor(m_splitter->indexOf(m_ownSplit), 0);
        m_ownSplit->hide();
    }

    void Sidebar::setSidebarStyle(KMultiTabBarStyle style)
    {
        m_sidebarTabStyle = style;
        setStyle(style);
    }

    ToolView *Sidebar::addWidget(const QIcon &icon, const QString &text, ToolView *widget)
    {
        static int id = 0;

        if (widget)
        {
            if (widget->sidebar() == this)
                return widget;

            widget->sidebar()->removeWidget(widget);
        }

        int newId = ++id;

        appendTab(icon, newId, text);

        if (!widget)
        {
            widget = new ToolView(m_mainWin, this, m_ownSplit);
            widget->hide();
            widget->icon = icon;
            widget->text = text;
        }
        else
        {
            widget->hide();
            widget->setParent(m_ownSplit);
            QPoint p;
            widget->setGeometry(p.x(), p.y(), width(), height());
            widget->m_sidebar = this;
        }

        widget->persistent = false;

        m_idToWidget.insert(newId, widget);
        m_widgetToId.insert(widget, newId);
        m_toolviews.push_back(widget);

        show();

        connect(tab(newId), qOverload<int>(&KMultiTabBarTab::clicked), this, &Sidebar::tabClicked);
        tab(newId)->installEventFilter(this);

        return widget;
    }

    bool Sidebar::removeWidget(ToolView *widget)
    {
        if (!m_widgetToId.contains(widget))
            return false;

        removeTab(m_widgetToId[widget]);

        m_idToWidget.remove(m_widgetToId[widget]);
        m_widgetToId.remove(widget);
        m_toolviews.removeAll(widget);

        bool anyVis = false;

        for (QMap<int, ToolView *>::iterator it = m_idToWidget.begin(); it != m_idToWidget.end(); ++it)
        {
            if (!anyVis)
                anyVis = it.value()->isVisible();
        }

        if (m_idToWidget.isEmpty())
        {
            m_ownSplit->hide();
            hide();
        }
        else if (!anyVis)
            m_ownSplit->hide();

        return true;
    }

    void Sidebar::tabClicked(int i)
    {
        ToolView *w = m_idToWidget[i];

        if (!w)
        {
            qCWarning(RDV_LOG) << " numéro d'onglet inattendu " << i;
            return;
        }

        if (isTabRaised(i))
        {
            showWidget(w);
            w->setFocus();
        }
        else
        {
            hideWidget(w);
            m_mainWin->centralWidget()->setFocus();
        }
    }

    bool Sidebar::showWidget(ToolView *widget)
    {
        if (!m_widgetToId.contains(widget))
            return false;

        for (QMap<int, ToolView *>::iterator it = m_idToWidget.begin(); it != m_idToWidget.end(); ++it)
            if ((it.value() != widget) && !it.value()->persistent)
            {
                it.value()->hide();
                setTab(it.key(), false);
                it.value()->setVisibleToolView(false);
            }

        setTab(m_widgetToId[widget], true);

        m_ownSplit->show();
        widget->show();

        widget->setVisibleToolView(true);

        return true;
    }

    bool Sidebar::hideWidget(ToolView *widget)
    {
        if (!m_widgetToId.contains(widget))
            return false;

        bool anyVis = false;

        updateLastSize();

        for (QMap<int, ToolView *>::iterator it = m_idToWidget.begin(); it != m_idToWidget.end(); ++it)
        {
            if (it.value() == widget)
            {
                it.value()->hide();
                continue;
            }

            if (!anyVis)
                anyVis = it.value()->isVisible();
        }

        setTab(m_widgetToId[widget], false);

        if (!anyVis)
            m_ownSplit->hide();

        widget->setVisibleToolView(false);

        return true;
    }

    void Sidebar::updateLastSize()
    {
        QList<int> s = m_splitter->sizes();

        int i = 0;
        if ((sidebarPosition() == KMultiTabBar::Right || sidebarPosition() == KMultiTabBar::Bottom))
            i = 2;

        if (s[i] > 2)
            m_lastSize = s[i];
    }

    void Sidebar::updateMinimumSize()
    {
        QSize minSize;

        QList<ToolView *>::iterator end = m_toolviews.end();
        for (QList<ToolView *>::iterator it = m_toolviews.begin(); it != end; ++it)
        {
            QSize s = (*it)->childrenRect().size();
            minSize = minSize.expandedTo(s);
        }

        minSize.setWidth(minSize.width() - 30);
        minSize.setHeight(minSize.height() - 30);

        for (QList<ToolView *>::iterator it = m_toolviews.begin(); it != end; ++it)
        {
            (*it)->setMinimumSize(minSize);
        }
    }
}
