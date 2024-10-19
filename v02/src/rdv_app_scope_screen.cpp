#include "rdv_app_scope_screen.h"
#include "rdv_app_tool_view.h"

ScopeScreen::ScopeScreen(KateMDI::ToolView *parent)
    : QWidget(parent)
{
}

ScopeScreen::~ScopeScreen()
{
}

ScopeScreen *ScopeScreen::self(KateMDI::ToolView *parent)
{
    static ScopeScreen *pSelf = nullptr;
    if (pSelf)
        return pSelf;
    assert(parent);
    pSelf = new ScopeScreen(parent);
    return pSelf;
}
