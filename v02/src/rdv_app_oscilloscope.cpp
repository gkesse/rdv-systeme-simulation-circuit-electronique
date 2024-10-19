#include "rdv_app_oscilloscope.h"
#include "rdv_app_readyspice.h"
#include "rdv_app_tool_view.h"

Oscilloscope *Oscilloscope::m_pSelf = nullptr;

Oscilloscope::Oscilloscope(KateMDI::ToolView *parent)
    : QWidget(parent)
{
}

Oscilloscope::~Oscilloscope()
{
}

Oscilloscope *Oscilloscope::self(KateMDI::ToolView *parent)
{
    if (!m_pSelf)
    {
        assert(parent);
        m_pSelf = new Oscilloscope(parent);
    }
    return m_pSelf;
}

void Oscilloscope::addOscilloscopeAsToolView(ReadySpice *readyspice)
{
    KateMDI::ToolView *tv;
    tv = readyspice->createToolView(Oscilloscope::toolViewIdentifier(), KMultiTabBar::Bottom, QIcon::fromTheme("oscilloscope"), i18n("Oscilloscope"));

    Oscilloscope::self(tv);
}
