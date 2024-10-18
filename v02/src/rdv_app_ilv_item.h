#pragma once

#include "rdv_app_include.h"

class ProjectItem;

class ILVItem : public QObject, public QTreeWidgetItem /* K3ListViewItem */
{
    Q_OBJECT

public:
    enum
    {
        DataRole_ID = Qt::UserRole,
    } ILVItemRole;

public:
    ILVItem(QTreeWidget *parent, const QString &id);
    ILVItem(QTreeWidgetItem *parent, const QString &id);
    ~ILVItem() override;

    bool isRemovable() const { return b_isRemovable; }

protected:
    bool b_isRemovable;
    ProjectItem *m_pProjectItem;
};
