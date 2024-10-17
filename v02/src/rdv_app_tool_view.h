#pragma once

#include "rdv_app_include.h"

namespace KateMDI
{
    class ToolView : public QWidget
    {
        Q_OBJECT

    public:
        explicit ToolView(QWidget *_parent = nullptr);
        ~ToolView() override;
    };
}