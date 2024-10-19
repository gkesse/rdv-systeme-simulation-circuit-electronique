#pragma once

#include "rdv_app_include.h"

class PropertyEditor : public QTableWidget
{
    Q_OBJECT

public:
    PropertyEditor(QWidget *parent = nullptr);
    ~PropertyEditor() override;
};
