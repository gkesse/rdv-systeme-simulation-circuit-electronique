#pragma once

#include "rdv_app_item_selector.h"

namespace KateMDI
{
    class ToolView;
}

class FlowPartSelector : public ItemSelector
{
    Q_OBJECT

private:
    FlowPartSelector(KateMDI::ToolView *parent);

public:
    ~FlowPartSelector();
    static FlowPartSelector *self(KateMDI::ToolView *parent = nullptr);

    static QString toolViewIdentifier() { return "FlowPartSelector"; }

private:
    static FlowPartSelector *m_pSelf;
};
