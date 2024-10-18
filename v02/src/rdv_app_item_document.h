#pragma once

#include "rdv_app_document.h"

class ItemDocument : public Document
{
    Q_OBJECT

public:
    ItemDocument(const QString &caption);
    ~ItemDocument() override;
};
