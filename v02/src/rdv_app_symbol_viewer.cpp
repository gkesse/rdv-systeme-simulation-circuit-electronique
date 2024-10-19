#include "rdv_app_symbol_viewer.h"
#include "rdv_app_tool_view.h"

SymbolViewer *SymbolViewer::m_pSelf = nullptr;

SymbolViewer::SymbolViewer(KateMDI::ToolView *parent)
    : QWidget(static_cast<QWidget *>(parent))
{
}

SymbolViewer::~SymbolViewer()
{
}

SymbolViewer *SymbolViewer::self(KateMDI::ToolView *parent)
{
    if (!m_pSelf)
    {
        assert(parent);
        m_pSelf = new SymbolViewer(parent);
    }
    return m_pSelf;
}
