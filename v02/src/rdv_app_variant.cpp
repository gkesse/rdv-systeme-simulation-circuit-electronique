#include "rdv_app_variant.h"

Variant::Variant(const QString &id, Type::Value type)
{
}

Variant::~Variant()
{
}

void Variant::setCaption(const QString &caption)
{
    setToolbarCaption(caption);
    setEditorCaption(caption);
}

void Variant::setToolbarCaption(const QString &caption)
{
    m_toolbarCaption = caption;
}

void Variant::setEditorCaption(const QString &caption)
{
    m_editorCaption = caption;
}