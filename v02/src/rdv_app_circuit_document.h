#pragma once

#include "rdv_app_circuit_icn_document.h"

class CircuitDocument : public CircuitICNDocument
{
    Q_OBJECT

public:
    CircuitDocument(const QString &caption);
    ~CircuitDocument() override;
};
