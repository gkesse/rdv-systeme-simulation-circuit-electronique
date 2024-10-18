#include "rdv_app_gui_client.h"
#include "rdv_app_main_window.h"
#include "rdv_app_tool_view.h"

namespace KateMDI
{
    GUIClient::GUIClient(MainWindow *mw)
        : QObject(mw), KXMLGUIClient(mw), m_mw(mw)
    {
    }

    GUIClient::~GUIClient()
    {
    }

    void GUIClient::registerToolView(ToolView *tv)
    {
        QString aname = QString("kate_mdi_toolview_") + tv->id;
        KConfigGroup grSh = KSharedConfig::openConfig()->group("Shortcuts");
    }
}
