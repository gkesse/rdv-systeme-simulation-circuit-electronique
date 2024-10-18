#pragma once

#include "rdv_app_circuit_icn_document.h"

class FlowCodeDocument : public CircuitICNDocument
{
    Q_OBJECT

public:
    FlowCodeDocument(const QString &caption);
    ~FlowCodeDocument() override;
};
