#pragma once

#include "rdv_app_include.h"

class Document : public QObject
{
    Q_OBJECT

public:
    explicit Document(QObject *parent = nullptr);
    ~Document() override;
};
