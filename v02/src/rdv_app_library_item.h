#pragma once

#include "rdv_app_include.h"

typedef Item *(*createItemPtr)(ItemDocument *itemDocument, bool newItem, const char *id);

class LibraryItem
{

public:
    enum Type
    {
        lit_flowpart,
        lit_component,
        lit_mechanical,
        lit_drawpart,
        lit_subcircuit,
        lit_other
    };

public:
    LibraryItem(QStringList idList, const QString &name, const QString &category, QIcon icon, Type type, createItemPtr createItem);
    LibraryItem(QStringList idList, const QString &name, const QString &category, const QString &iconName, Type type, createItemPtr createItem);
    LibraryItem(QStringList idList, const QString &name, const QString &category, Type type, createItemPtr createItem);
    ~LibraryItem();

private:
    QStringList m_idList;
    QString m_name;
    QString m_category;
    QIcon m_icon;
    createItemPtr createItem;
    int m_type;
};
