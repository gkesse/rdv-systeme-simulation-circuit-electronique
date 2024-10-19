#pragma once

#include "rdv_app_include.h"

class OrientationWidget : public QWidget
{
    Q_OBJECT
public:
    OrientationWidget(QWidget *parent = nullptr);
    ~OrientationWidget() override;
};
