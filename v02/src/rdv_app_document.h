#pragma once

#include "rdv_app_include.h"

class Document : public QObject
{
    Q_OBJECT

public:
    Document(const QString &caption);
    ~Document() override;
    virtual bool isModified() const;

    const QUrl &url() const { return m_url; }

protected:
    bool b_modified;

private:
    QUrl m_url;
};
