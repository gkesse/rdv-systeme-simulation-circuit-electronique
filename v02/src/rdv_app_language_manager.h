#pragma once

#include "rdv_app_include.h"

namespace KateMDI
{
    class ToolView;
}

class LanguageManager : public QObject
{
    Q_OBJECT

protected:
    LanguageManager(KateMDI::ToolView *parent);

public:
    ~LanguageManager();
    static LanguageManager *self(KateMDI::ToolView *parent = nullptr);

    static QString toolViewIdentifier() { return "LanguageManager"; }

private:
    static LanguageManager *m_pSelf;
};
