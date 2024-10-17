#pragma once

#include "rdv_app_include.h"

class ViewArea : public QSplitter
{
    Q_OBJECT

public:
    explicit ViewArea(QWidget *_parent = nullptr);
    ~ViewArea();
};
