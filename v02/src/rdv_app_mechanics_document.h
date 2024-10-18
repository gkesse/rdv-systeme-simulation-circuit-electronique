#pragma once

#include "rdv_app_item_document.h"

class MechanicsDocument : public ItemDocument
{
    Q_OBJECT

public:
    MechanicsDocument(const QString &caption);
    ~MechanicsDocument() override;
};
