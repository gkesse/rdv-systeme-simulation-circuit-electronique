#pragma once

#include "rdv_app_include.h"

class PropertyEditor;
class OrientationWidget;
class ComponentModelWidget;

namespace KateMDI
{
    class ToolView;
}

class ItemEditor : public QWidget
{
    Q_OBJECT

private:
    ItemEditor(KateMDI::ToolView *parent);

public:
    ~ItemEditor() override;
    static ItemEditor *self(KateMDI::ToolView *parent);

    static QString toolViewIdentifier() { return "ItemEditor"; }

protected:
    PropertyEditor *m_pPropertyEditor;
    QLabel *m_pNameLabel;
    OrientationWidget *m_pOrientationWidget;
    ComponentModelWidget *m_pComponentModelWidget;

public slots:
    void slotClear();

private:
    static ItemEditor *m_pSelf;
};
