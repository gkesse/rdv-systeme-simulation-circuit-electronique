#pragma once

#include "rdv_app_include.h"

namespace KateMDI
{
    class MainWindow : public KParts::MainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *_parent = nullptr);
        ~MainWindow() override;
    };
}
