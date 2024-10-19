#include "rdv_app_language_manager.h"
#include "rdv_app_readyspice.h"

LanguageManager *LanguageManager::m_pSelf = nullptr;

LanguageManager::LanguageManager(KateMDI::ToolView *parent)
    : QObject(ReadySpice::self())
{
}

LanguageManager::~LanguageManager()
{
}

LanguageManager *LanguageManager::self(KateMDI::ToolView *parent)
{
    if (!m_pSelf)
    {
        assert(parent);
        m_pSelf = new LanguageManager(parent);
    }
    return m_pSelf;
}
