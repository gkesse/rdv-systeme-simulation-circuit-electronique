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

void ItemSelector::addItem(const QString &caption, const QString &id, const QString &_category, const QIcon &icon, bool removable)
{
    qCDebug(RDV_LOG) << "id=" << id;
    ILVItem *parentItem = nullptr;

    QString category = _category;
    if (!category.startsWith("/"))
    {
        category.prepend('/');
    }

    do
    {
        category.remove(0, 1);
        QString cat;
        category.replace("\\/", "|");
        int pos = category.indexOf('/');
        if (pos == -1)
            cat = category;
        else
            cat = category.left(pos);

        cat.replace("|", "/");

        if (m_categories.indexOf(cat) == -1)
        {
            m_categories.append(cat);

            if (parentItem)
            {
                parentItem = new ILVItem(parentItem, "");
            }
            else
            {
                parentItem = new ILVItem(this, "");
            }

            parentItem->setExpanded(readOpenState(cat));

            parentItem->setText(0, cat);
        }
        else
        {
            QList<QTreeWidgetItem *> foundList = findItems(cat, Qt::MatchExactly);
            if (foundList.size() > 1)
            {
                qCWarning(RDV_LOG) << "trouvé plusieurs catégories pour '" << cat << "'";
            }
            parentItem = dynamic_cast<ILVItem *>(foundList.front());
        }

        category.remove(0, pos);
    } while (category.contains('/'));

    if (!parentItem)
    {
        qCCritical(RDV_LOG) << "Erreur inattendue lors de la recherche d'un élément parent pour la liste de catégories";
        return;
    }

    ILVItem *item = new ILVItem(parentItem, id);
    item->setIcon(0, icon);
    item->setText(0, caption);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    item->setRemovable(removable);
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

bool ItemSelector::readOpenState(const QString &id)
{
    KSharedConfigPtr configPtr = KSharedConfig::openConfig();
    KConfigGroup configGroup = configPtr->group(objectName());
    return configGroup.readEntry<bool>(id + "IsOpen", true);
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
