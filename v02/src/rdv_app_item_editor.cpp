#include "rdv_app_item_editor.h"
#include "rdv_app_tool_view.h"
#include "rdv_app_property_editor.h"
#include "rdv_app_component_model_widget.h"
#include "rdv_app_orientation_widget.h"

ItemEditor *ItemEditor::m_pSelf = nullptr;

ItemEditor::ItemEditor(KateMDI::ToolView *parent)
    : QWidget(static_cast<QWidget *>(parent))
{
    setObjectName("Item Editor");
    setWhatsThis(i18n("Cela permet de modifier les propriétés avancées des éléments sélectionnés. Faites un clic droit sur l'image de l'élément pour définir l'orientation."));

    if (parent->layout())
    {
        parent->layout()->addWidget(this);
        qCDebug(RDV_LOG) << " ajout d'un sélecteur d'élément à la mise en page du parent " << parent;
    }
    else
    {
        qCWarning(RDV_LOG) << " disposition nulle inattendue sur le parent " << parent;
    }

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(6);

    m_pNameLabel = new QLabel("");
    m_pNameLabel->setBuddy(this);
    m_pNameLabel->setTextFormat(Qt::RichText);

    QFont font;
    font.setBold(true);
    if (font.pointSize() != 0)
        font.setPointSize(int(font.pointSize() * 1.4));
    m_pNameLabel->setFont(font);

    m_pPropertyEditor = new PropertyEditor(this);
    m_pPropertyEditor->setWhatsThis(
        i18n("<p>Affiche les propriétés associées aux éléments actuellement sélectionnés.<br/>Sélectionnez une propriété pour modifier sa valeur. Si plusieurs éléments sont sélectionnés avec des valeurs différentes, la propriété apparaîtra grisée, utilisez \"Fusionner "
             "Propriétés\" pour les rendre identiques.<br/>Sélectionnez \"Par défaut\" pour définir toutes les propriétés sur leurs valeurs par défaut"));

    m_pComponentModelWidget = new ComponentModelWidget(this);

    vlayout->addWidget(m_pNameLabel);
    vlayout->addWidget(m_pPropertyEditor, 3);
    vlayout->addWidget(m_pComponentModelWidget, 5);

    QHBoxLayout *h2Layout = new QHBoxLayout();
    vlayout->addLayout(h2Layout);
    h2Layout->setMargin(6);
    h2Layout->addItem(new QSpacerItem(1, 1));
    m_pOrientationWidget = new OrientationWidget(this);
    h2Layout->addWidget(m_pOrientationWidget);
    m_pOrientationWidget->setWhatsThis(i18n("Change the orientation of the selected item by selecting the appropriate button"));
    h2Layout->addItem(new QSpacerItem(1, 1));

    slotClear();
}

ItemEditor::~ItemEditor()
{
}

ItemEditor *ItemEditor::self(KateMDI::ToolView *parent)
{
    if (!m_pSelf)
    {
        assert(parent);
        m_pSelf = new ItemEditor(parent);
    }
    return m_pSelf;
}

void ItemEditor::slotClear()
{
}
