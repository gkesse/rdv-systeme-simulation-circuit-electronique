#pragma once

#include "rdv_app_item_selector.h"

namespace KateMDI
{
    class ToolView;
}

class ProjectManager : public ItemSelector
{
    Q_OBJECT

private:
    ProjectManager(KateMDI::ToolView *parent);

public:
    ~ProjectManager();
    static ProjectManager *self(KateMDI::ToolView *parent = nullptr);

    static QString toolViewIdentifier() { return "ProjectManager"; }

public slots:
    void slotOpenProject();
    void slotOpenProject(const QUrl &url);

private:
    static ProjectManager *m_pSelf;
};
