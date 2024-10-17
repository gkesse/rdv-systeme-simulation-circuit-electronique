#pragma once

#include "rdv_app_include.h"

class ItemSelector : public QTreeWidget
{
    Q_OBJECT

public:
    explicit ItemSelector(QWidget *_parent = nullptr);
    ~ItemSelector() override;
};
