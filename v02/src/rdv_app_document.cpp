#include "rdv_app_document.h"
#include "rdv_app_readyspice.h"

Document::Document(const QString &caption)
    : QObject(ReadySpice::self()), b_modified(false)
{
}

Document::~Document()
{
}

bool Document::isModified() const
{
    return b_modified;
}
