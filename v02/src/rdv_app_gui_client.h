#pragma once

#include "rdv_app_include.h"

namespace KateMDI
{
    class MainWindow;
    class ToolView;

    class GUIClient : public QObject, public KXMLGUIClient
    {
        Q_OBJECT

    public:
        GUIClient(MainWindow *mw);
        ~GUIClient() override;
        void registerToolView(ToolView *tv);

    private:
        MainWindow *m_mw;
    };
}
