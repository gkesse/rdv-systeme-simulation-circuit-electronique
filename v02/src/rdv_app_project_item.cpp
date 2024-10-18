#include "rdv_app_project_item.h"

ProjectItem::ProjectItem(ProjectItem *parent, Type type, ProjectManager *projectManager)
    : QObject()
{
    m_pParent = parent;
    m_pILVItem = nullptr;
    m_pProjectManager = projectManager;
    m_type = type;
}

ProjectItem::~ProjectItem()
{
}
