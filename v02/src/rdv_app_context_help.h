#pragma once

#include "rdv_app_include.h"
#include "ui_rdv_app_context_help_widget.h"

namespace KateMDI
{
    class ToolView;
}

class ContextHelp : public QWidget, public Ui::ContextHelpWidget
{
    Q_OBJECT

private:
    ContextHelp(KateMDI::ToolView *parent);

public:
    ~ContextHelp();
    static ContextHelp *self(KateMDI::ToolView *parent = nullptr);

    static QString toolViewIdentifier() { return "ContextHelp"; }

private:
    static ContextHelp *m_pSelf;
};
