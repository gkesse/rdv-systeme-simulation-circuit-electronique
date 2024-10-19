#include "rdv_app_flow_part_selector.h"
#include "rdv_app_tool_view.h"
#include "rdv_app_item_library.h"
#include "rdv_app_library_item.h"

FlowPartSelector *FlowPartSelector::m_pSelf = nullptr;

FlowPartSelector::FlowPartSelector(KateMDI::ToolView *parent)
    : ItemSelector(static_cast<QWidget *>(parent))
{
    setWhatsThis(
        i18n("Ajoutez FlowPart au document FlowCode en les faisant glisser à cet endroit.<br><br>Pour ajouter plusieurs FlowPart du même type, double-cliquez sur un FlowPart et cliquez à plusieurs reprises dans le FlowChart pour placer le composant. Cliquez avec le bouton droit de la souris pour "
             "arrêter le placement."));

    setListCaption(i18n("Partie de flux"));

    LibraryItemList *items = ItemLibrary::itemLibrary()->items();
    const LibraryItemList::iterator end = items->end();
    for (LibraryItemList::iterator it = items->begin(); it != end; ++it)
    {
        if ((*it)->type() == LibraryItem::lit_flowpart)
            addItem((*it)->name(), (*it)->activeID(), (*it)->category(), (*it)->icon());
    }
}

FlowPartSelector::~FlowPartSelector()
{
}

FlowPartSelector *FlowPartSelector::self(KateMDI::ToolView *parent)
{
    if (!m_pSelf)
    {
        assert(parent);
        m_pSelf = new FlowPartSelector(parent);
        m_pSelf->setObjectName("Part Selector");
    }
    return m_pSelf;
}