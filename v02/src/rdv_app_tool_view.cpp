#include "rdv_app_tool_view.h"
#include "rdv_app_main_window.h"

namespace KateMDI
{
    ToolView::ToolView(MainWindow *mainwin, Sidebar *sidebar, QWidget *parent)
        : QWidget(parent), m_mainWin(mainwin), m_sidebar(sidebar), m_visible(false), persistent(false)
    {
    }

    ToolView::~ToolView()
    {
    }

    void ToolView::setVisibleToolView(bool vis)
    {
        if (m_visible == vis)
            return;

        m_visible = vis;
        emit visibleChanged(m_visible);
    }
}