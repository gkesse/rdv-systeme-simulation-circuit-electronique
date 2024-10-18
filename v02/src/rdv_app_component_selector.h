#pragma once

#include "rdv_app_item_selector.h"

namespace KateMDI
{
    class ToolView;
}

class ComponentSelector : public ItemSelector
{
    Q_OBJECT

private:
    ComponentSelector(KateMDI::ToolView *parent);

public:
    ~ComponentSelector() override;
    static ComponentSelector *self(KateMDI::ToolView *parent = nullptr);

    static QString toolViewIdentifier() { return "ComponentSelector"; }

private:
    static ComponentSelector *m_pSelf;
};
