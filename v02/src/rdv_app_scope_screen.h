#pragma once

#include "rdv_app_include.h"

namespace KateMDI
{
    class ToolView;
}

class ScopeScreen : public QWidget
{
    Q_OBJECT

private:
    ScopeScreen(KateMDI::ToolView *parent);

public:
    ~ScopeScreen() override;
    static ScopeScreen *self(KateMDI::ToolView *parent = nullptr);

    static QString toolViewIdentifier() { return "ScopeScreen"; }
};
