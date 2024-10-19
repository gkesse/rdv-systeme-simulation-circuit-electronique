#include "rdv_app_component_selector.h"
#include "rdv_app_tool_view.h"
#include "rdv_app_item_library.h"
#include "rdv_app_library_item.h"

ComponentSelector *ComponentSelector::m_pSelf = nullptr;

ComponentSelector::ComponentSelector(KateMDI::ToolView *parent)
    : ItemSelector(parent)
{
    qCDebug(RDV_LOG) << " création " << this;

    setWhatsThis(
        i18n("Ajoutez des composants au schéma de circuit en les faisant glisser dans le circuit.<br><br>"
             "Pour ajouter plusieurs composants du même type, double-cliquez sur un composant et cliquez plusieurs fois dans le circuit pour placer le composant. Cliquez avec le bouton droit de la souris pour arrêter le placement.<br><br>"
             "Certains composants (tels que les sous-circuits) peuvent être supprimés en cliquant avec le bouton droit sur l'élément et en sélectionnant \"Supprimer\"."));

    setListCaption(i18n("Component"));

    LibraryItemList *items = ItemLibrary::itemLibrary()->items();
    qCDebug(RDV_LOG) << " il y a " << items->count() << " items";
    const LibraryItemList::iterator end = items->end();
    for (LibraryItemList::iterator it = items->begin(); it != end; ++it)
    {
        if ((*it)->type() == LibraryItem::lit_component)
            addItem((*it)->name(), (*it)->activeID(), (*it)->category(), (*it)->icon());
    }
}

ComponentSelector::~ComponentSelector()
{
}

ComponentSelector *ComponentSelector::self(KateMDI::ToolView *parent)
{
    if (!m_pSelf)
    {
        assert(parent);
        m_pSelf = new ComponentSelector(parent);
        m_pSelf->setObjectName("Component Selector");
    }
    return m_pSelf;
}
