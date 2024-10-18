#include "rdv_app_item_selector.h"
#include "rdv_app_ilv_item.h"

ItemSelector::ItemSelector(QWidget *parent)
    : QTreeWidget(parent)
{
    qCDebug(RDV_LOG) << " this=" << this;

    setDragDropMode(QAbstractItemView::DragOnly);
    setColumnCount(1);
    setHeaderLabel(i18n("Composant"));
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
    setSortingEnabled(false);
    setRootIsDecorated(true);
    setFocusPolicy(Qt::NoFocus);

    setSelectionMode(QAbstractItemView::SingleSelection); // 2015.12.10 - need to allow selection for removing items

    if (parent->layout())
    {
        parent->layout()->addWidget(this);
        qCDebug(RDV_LOG) << " ajout d'un sélecteur d'élément à la mise en page du parent " << parent;
    }
    else
    {
        qCWarning(RDV_LOG) << " disposition nulle inattendue sur le parent " << parent;
    }

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // ?

    connect(this, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(slotItemClicked(QTreeWidgetItem *, int)));
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(slotItemDoubleClicked(QTreeWidgetItem *, int)));
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &ItemSelector::customContextMenuRequested, this, &ItemSelector::slotContextMenuRequested);
    connect(this, &ItemSelector::itemSelectionChanged, this, &ItemSelector::slotItemSelected);
}

ItemSelector::~ItemSelector()
{
}

void ItemSelector::setListCaption(const QString &caption)
{
    setHeaderLabel(caption);
}

QTreeWidgetItem *ItemSelector::selectedItem() const
{
    QList<QTreeWidgetItem *> selectedList = selectedItems();
    if (selectedList.empty())
    {
        return nullptr;
    }
    if (selectedList.size() > 1)
    {
        qCWarning(RDV_LOG) << " 1 article attendu dans la sélection, obtenu " << selectedList.size();
    }
    return selectedList.first();
}

void ItemSelector::slotContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *item = itemAt(pos);
    if (!item || !(static_cast<ILVItem *>(item))->isRemovable())
    {
        return;
    }

    QMenu *menu = new QMenu(this);
    menu->addAction(i18n("Supprimer %1", item->text(0)), this, SLOT(slotRemoveSelectedItem()));
    QPoint globalPos = mapToGlobal(pos);
    menu->popup(globalPos);
}

void ItemSelector::slotItemSelected()
{
    QTreeWidgetItem *item = selectedItem();
    if (!item)
    {
        return;
    }

    emit itemSelected(item->data(0, ILVItem::DataRole_ID).toString() /* item->key( 0, 0 ) */);
}
