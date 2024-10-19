#include "rdv_app_context_help.h"
#include "rdv_app_tool_view.h"

ContextHelp *ContextHelp::m_pSelf = nullptr;

ContextHelp::ContextHelp(KateMDI::ToolView *parent)
    : QWidget(parent), Ui::ContextHelpWidget()
{
    setupUi(this);
}

ContextHelp::~ContextHelp()
{
}

ContextHelp *ContextHelp::self(KateMDI::ToolView *parent)
{
    if (!m_pSelf)
    {
        assert(parent);
        m_pSelf = new ContextHelp(parent);
    }
    return m_pSelf;
}
