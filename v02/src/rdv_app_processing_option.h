#pragma once

#include "rdv_app_include.h"

class ProcessingOptions
{
public:
    ProcessingOptions();
    virtual ~ProcessingOptions();

protected:
    QString m_microID;
    bool m_bUseParentMicroID;
};
