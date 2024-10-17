#pragma once

#include "rdv_app_item_selector.h"

namespace KateMDI
{
    class ToolView;
}

class ProjectManager : public ItemSelector
{
    Q_OBJECT

public:
    ~ProjectManager();
    static ProjectManager *self(KateMDI::ToolView *parent = nullptr);

private:
    ProjectManager(KateMDI::ToolView *parent);

public slots:
    void slotOpenProject();
    void slotOpenProject(const QUrl &url);

private:
    static ProjectManager *m_pSelf;
};
