#pragma once

#include "rdv_app_document.h"

class TextDocument : public Document
{
    Q_OBJECT

public:
    TextDocument(const QString &caption);
    ~TextDocument() override;
};
