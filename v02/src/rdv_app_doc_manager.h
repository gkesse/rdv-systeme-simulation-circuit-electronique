#pragma once

#include "rdv_app_include.h"

class ViewArea;
class Document;

class DocManager : public QObject
{
    Q_OBJECT

public:
    ~DocManager() override;
    static DocManager *self();
    Document *openURL(const QUrl &url, ViewArea *viewArea);

private:
    explicit DocManager(QObject *parent = nullptr);
    static DocManager *m_pSelf;
};
