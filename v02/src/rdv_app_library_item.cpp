#include "rdv_app_library_item.h"

LibraryItem::LibraryItem(QStringList idList, const QString &name, const QString &category, QIcon icon, Type type, createItemPtr _createItem)
{
    m_idList = idList;
    m_name = name;
    m_category = category;
    m_icon = icon;
    m_type = type;
    createItem = _createItem;
}

LibraryItem::LibraryItem(QStringList idList, const QString &name, const QString &category, const QString &iconName, Type type, createItemPtr _createItem)
{
    m_idList = idList;
    m_name = name;
    m_category = category;
    m_icon = QIcon(QStandardPaths::locate(QStandardPaths::AppDataLocation, "icons/" + iconName));
    m_type = type;
    createItem = _createItem;
}

LibraryItem::LibraryItem(QStringList idList, const QString &name, const QString &category, Type type, createItemPtr _createItem)
{
    m_idList = idList;
    m_name = name;
    m_category = category;
    m_type = type;
    createItem = _createItem;
}

LibraryItem::~LibraryItem()
{
}
