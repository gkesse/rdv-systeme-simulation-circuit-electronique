#pragma once

#include "rdv_app_main_window.h"
#include "rdv_app_view_container.h"

class ViewArea;
class ViewContainer;

typedef QList<QPointer<ViewContainer>> ViewContainerList;

class ReadySpice : public KateMDI::MainWindow
{
    Q_OBJECT

public:
    explicit ReadySpice(QWidget *parent = nullptr);
    ~ReadySpice() override;
    static ReadySpice *self();
    QTabWidget *tabWidget() const;

protected:
    void readPropertiesInConfig(KConfig *conf);

private:
    void setupActions();
    void setupExampleActions();
    void setupToolDocks();
    void setupView();
    void setupTabWidget();
    void loadInternal(const QUrl &url, bool isRecent, ViewArea *viewArea = nullptr);

public slots:
    void load(const QUrl &url, ViewArea *viewArea = nullptr);
    void addRecentFile(const QUrl &url);

public slots:
    void slotTabContext(const QPoint &pos);
    void slotTabContextActivated(QAction *action);

protected slots:
    void slotUpdateCaptions();
    void slotViewContainerActivated(int index);

private slots:
    void slotViewContainerClose();

private:
    static ReadySpice *m_pSelf;
    QTabWidget *m_pViewContainerTabWidget;
    bool m_bIsShown;

    QPointer<ViewContainer> m_pContextMenuContainer;
    QPointer<ViewContainer> m_pFocusedContainer;
    QPointer<ViewContainer> m_pContainerDropSource;
    QPointer<ViewContainer> m_pContainerDropReceived;

    QLabel *m_pToolBarOverlayLabel;
    QFont m_itemFont;
    QTimer *m_pUpdateCaptionsTimer;
    ViewContainerList m_viewContainerList;
};
