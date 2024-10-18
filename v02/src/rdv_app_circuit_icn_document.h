#pragma once

#include "rdv_app_icn_document.h"

class CircuitICNDocument : public ICNDocument
{
    Q_OBJECT

public:
    CircuitICNDocument(const QString &caption);
    ~CircuitICNDocument() override;
};
