#pragma once

#include "rdv_app_include.h"

namespace KateMDI
{
    class ToolView;
}

class SymbolViewer : public QWidget
{
    Q_OBJECT

private:
    SymbolViewer(KateMDI::ToolView *parent);

public:
    ~SymbolViewer() override;
    static SymbolViewer *self(KateMDI::ToolView *parent = nullptr);

    static QString toolViewIdentifier() { return "SymbolViewer"; }

private:
    static SymbolViewer *m_pSelf;
};
