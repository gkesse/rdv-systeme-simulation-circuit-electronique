#pragma once

#include "rdv_app_include.h"

class ReadySpice;

namespace KateMDI
{
    class ToolView;
}

class Oscilloscope : public QWidget
{
    Q_OBJECT

private:
    Oscilloscope(KateMDI::ToolView *parent);

public:
    ~Oscilloscope() override;
    static Oscilloscope *self(KateMDI::ToolView *parent = nullptr);
    static void addOscilloscopeAsToolView(ReadySpice *readyspice);

    static QString toolViewIdentifier() { return "Oscilloscope"; }

private:
    static Oscilloscope *m_pSelf;
};