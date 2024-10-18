#pragma once

#include "rdv_app_item_document.h"

class ICNDocument : public ItemDocument
{
    Q_OBJECT

public:
    ICNDocument(const QString &caption);
    ~ICNDocument() override;
};
