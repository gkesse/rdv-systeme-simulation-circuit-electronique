#pragma once

#include "rdv_app_include.h"

class KtlQCanvas;

class KtlQCanvasItem : public QObject
{
    Q_OBJECT

public:
    KtlQCanvasItem(KtlQCanvas *canvas);
    ~KtlQCanvasItem() override;
};
