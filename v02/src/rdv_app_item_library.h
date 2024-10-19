#pragma once

#include "rdv_app_include.h"

class LibraryItem;

typedef QList<LibraryItem *> LibraryItemList;

class ItemLibrary : public QObject
{
    Q_OBJECT

public:
    ItemLibrary();
    ~ItemLibrary() override;
    static ItemLibrary *itemLibrary();

    LibraryItemList *items() { return &m_items; }

protected:
    LibraryItemList m_items;
};
