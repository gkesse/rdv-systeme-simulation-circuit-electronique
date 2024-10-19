#include "rdv_app_item_library.h"

ItemLibrary::ItemLibrary()
{
}

ItemLibrary::~ItemLibrary()
{
}

ItemLibrary *ItemLibrary::itemLibrary()
{
    static ItemLibrary *_itemLibrary = new ItemLibrary();
    return _itemLibrary;
}
