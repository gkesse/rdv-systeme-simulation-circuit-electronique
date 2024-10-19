#include "rdv_app_ilv_item.h"

ILVItem::ILVItem(QTreeWidget *parent, const QString &id)
    : QTreeWidgetItem(parent, 0)
{
    setData(0, DataRole_ID, QVariant(id));
    b_isRemovable = false;
    m_pProjectItem = nullptr;
}

ILVItem::ILVItem(QTreeWidgetItem *parent, const QString &id)
    : QTreeWidgetItem(parent, 0)
{
    setData(0, DataRole_ID, QVariant(id));
    b_isRemovable = false;
    m_pProjectItem = nullptr;
}

ILVItem::~ILVItem()
{
}
