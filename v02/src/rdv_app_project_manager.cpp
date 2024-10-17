#include "rdv_app_project_manager.h"
#include "rdv_app_tool_view.h"

ProjectManager *ProjectManager::m_pSelf = nullptr;

ProjectManager::ProjectManager(KateMDI::ToolView *parent)
    : ItemSelector(parent)
{
}

ProjectManager::~ProjectManager()
{
}

ProjectManager *ProjectManager::self(KateMDI::ToolView *parent)
{
    if (!m_pSelf)
    {
        assert(parent);
        m_pSelf = new ProjectManager(parent);
        m_pSelf->setObjectName("Project Manager");
    }
    return m_pSelf;
}

void ProjectManager::slotOpenProject()
{
}

void ProjectManager::slotOpenProject(const QUrl &url)
{
}
