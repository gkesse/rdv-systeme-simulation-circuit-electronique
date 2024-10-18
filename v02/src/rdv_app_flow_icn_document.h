#pragma once

#include "rdv_app_icn_document.h"

class FlowICNDocument : public ICNDocument
{
    Q_OBJECT

public:
    FlowICNDocument(const QString &caption);
    ~FlowICNDocument() override;
};
