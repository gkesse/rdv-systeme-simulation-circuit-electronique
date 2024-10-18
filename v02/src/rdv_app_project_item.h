#pragma once

#include "rdv_app_linker_option.h"

class ProjectManager;
class ILVItem;

class ProjectItem : public QObject, public LinkerOptions, public ProcessingOptions
{
    Q_OBJECT

public:
    enum Type
    {
        ProjectType = 1 << 0,
        FileType = 1 << 1,
        ProgramType = 1 << 2,
        LibraryType = 1 << 3
    };

    enum
    {
        AllTypes = ProjectType | FileType | ProgramType | LibraryType
    };

    enum OutputType
    {
        ProgramOutput = 1 << 0,
        ObjectOutput = 1 << 1,
        LibraryOutput = 1 << 2,
        UnknownOutput = 1 << 3
    };

    enum
    {
        AllOutputs = ProgramOutput | ObjectOutput | LibraryOutput | UnknownOutput
    };

public:
    ProjectItem(ProjectItem *parent, Type type, ProjectManager *projectManager);
    ~ProjectItem() override;

protected:
    QPointer<ILVItem> m_pILVItem;
    ProjectManager *m_pProjectManager;
    ProjectItem *m_pParent;
    Type m_type;
};
