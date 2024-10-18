#pragma once

#include "rdv_app_include.h"

namespace KateMDI
{
    class Splitter : public QSplitter
    {
        Q_OBJECT

    public:
        Splitter(Qt::Orientation o, QWidget *parent = nullptr);
        ~Splitter() override;
    };
}
