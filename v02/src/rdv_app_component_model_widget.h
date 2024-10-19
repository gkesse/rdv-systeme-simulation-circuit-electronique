#pragma once

#include "rdv_app_include.h"

class ComponentModelWidget : public QWidget
{
    Q_OBJECT

public:
    ComponentModelWidget(QWidget *parent = nullptr);
    ~ComponentModelWidget() override;
};
