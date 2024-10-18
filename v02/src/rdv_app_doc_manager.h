#pragma once

#include "rdv_app_include.h"

class View;
class ViewArea;
class Document;
class CircuitDocument;
class FlowCodeDocument;
class MechanicsDocument;
class TextDocument;

class DocManager : public QObject
{
    Q_OBJECT

private:
    explicit DocManager(QObject *parent = nullptr);

public:
    ~DocManager() override;
    static DocManager *self();
    Document *openURL(const QUrl &url, ViewArea *viewArea = nullptr);
    void giveDocumentFocus(Document *toFocus, ViewArea *viewAreaForNew = nullptr);

protected:
    Document *findDocument(const QUrl &url) const;
    CircuitDocument *openCircuitFile(const QUrl &url, ViewArea *viewArea = nullptr);
    View *createNewView(Document *document, ViewArea *viewArea = nullptr);
    FlowCodeDocument *openFlowCodeFile(const QUrl &url, ViewArea *viewArea = nullptr);
    MechanicsDocument *openMechanicsFile(const QUrl &url, ViewArea *viewArea = nullptr);
    TextDocument *openTextFile(const QUrl &url, ViewArea *viewArea = nullptr);

private:
    static DocManager *m_pSelf;
};
