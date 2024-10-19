#include "rdv_app_readyspice.h"
#include "rdv_app_view.h"
#include "rdv_app_view_area.h"
#include "rdv_app_project_manager.h"
#include "rdv_app_doc_manager.h"
#include "rdv_app_document.h"
#include "rdv_app_tool_view.h"
#include "rdv_app_component_selector.h"
#include "rdv_app_sub_circuit.h"
#include "rdv_app_flow_part_selector.h"
#include "rdv_app_item_editor.h"
#include "rdv_app_context_help.h"
#include "rdv_app_language_manager.h"
#include "rdv_app_symbol_viewer.h"
#include "rdv_app_oscilloscope.h"
#include "rdv_app_scope_screen.h"

ReadySpice *ReadySpice::m_pSelf = nullptr;

ReadySpice::ReadySpice(QWidget *parent)
    : KateMDI::MainWindow(parent)
{
    setObjectName("ReadySpice");
    m_pSelf = this;

    QElapsedTimer ct;
    ct.start();

    m_bIsShown = false;
    m_pContainerDropSource = nullptr;
    m_pContainerDropReceived = nullptr;
    m_pContextMenuContainer = nullptr;
    m_pFocusedContainer = nullptr;
    m_pToolBarOverlayLabel = nullptr;

    if (QFontInfo(m_itemFont).pixelSize() > 11)
    {
        m_itemFont.setPixelSize(12);
    }

    m_pUpdateCaptionsTimer = new QTimer(this);
    connect(m_pUpdateCaptionsTimer, &QTimer::timeout, this, &ReadySpice::slotUpdateCaptions);

    setMinimumSize(400, 400);

    setupTabWidget();
    setupToolDocks();
    setupActions();
    setupView();

    KSharedConfigPtr cfg = KSharedConfig::openConfig();
    readPropertiesInConfig(cfg.data());
}

ReadySpice::~ReadySpice()
{
}

ReadySpice *ReadySpice::self()
{
    return m_pSelf;
}

void ReadySpice::load(const QUrl &url, ViewArea *viewArea)
{
    if (!url.isValid())
        return;

    loadInternal(url, false, viewArea);
}

void ReadySpice::loadInternal(const QUrl &url, bool isRecent, ViewArea *viewArea)
{
    if (url.fileName().endsWith(".readyspice", Qt::CaseInsensitive))
    {
        ProjectManager::self()->slotOpenProject(url);
        return;
    }

    if (!isRecent)
        addRecentFile(url);

    setCaption(url.toDisplayString(QUrl::PreferLocalFile));
    DocManager::self()->openURL(url, viewArea);
}

void ReadySpice::addRecentFile(const QUrl &url)
{
}

QTabWidget *ReadySpice::tabWidget() const
{
    return m_pViewContainerTabWidget;
}

void ReadySpice::setupActions()
{
}

void ReadySpice::setupExampleActions()
{
}

void ReadySpice::setupToolDocks()
{
    setToolViewStyle(KMultiTabBar::KDEV3ICON);

    KateMDI::ToolView *tv = nullptr;

    tv = createToolView(ProjectManager::toolViewIdentifier(), KMultiTabBar::Left, QIcon::fromTheme("attach"), i18n("Project"));
    tv->setObjectName("ProjectManager-ToolView");
    ProjectManager::self(tv);

    tv = createToolView(ComponentSelector::toolViewIdentifier(), KMultiTabBar::Left, QIcon::fromTheme("circuit"), i18n("Components"));
    tv->setObjectName("ComponentSelector-ToolView");
    ComponentSelector::self(tv);

    Subcircuits::subcircuits();
    Subcircuits::loadSubcircuits();

    tv = createToolView(FlowPartSelector::toolViewIdentifier(), KMultiTabBar::Left, QIcon::fromTheme("flowcode"), i18n("Flow Parts"));
    tv->setObjectName("FlowPartSelector-ToolView");
    FlowPartSelector::self(tv);

#ifdef MECHANICS
    tv = createToolView(MechanicsSelector::toolViewIdentifier(), KMultiTabBar::Left, QIcon::fromTheme("mechanics"), i18n("Mechanics"));
    tv->setObjectName("MechanicsSelector-ToolView");
    MechanicsSelector::self(tv);
#endif

    tv = createToolView(ItemEditor::toolViewIdentifier(), KMultiTabBar::Right, QIcon::fromTheme("item"), i18n("Item Editor"));
    tv->setObjectName("ItemEditor-ToolView");
    ItemEditor::self(tv);

    tv = createToolView(ContextHelp::toolViewIdentifier(), KMultiTabBar::Right, QIcon::fromTheme("help-contents"), i18n("Context Help"));
    tv->setObjectName("ContextHelp-ToolView");
    ContextHelp::self(tv);

    tv = createToolView(LanguageManager::toolViewIdentifier(), KMultiTabBar::Bottom, QIcon::fromTheme("utilities-log-viewer"), i18n("Messages"));
    tv->setObjectName("LanguageManager-ToolView");
    LanguageManager::self(tv);

#ifndef NO_GPSIM
    tv = createToolView(SymbolViewer::toolViewIdentifier(), KMultiTabBar::Right, QIcon::fromTheme("blockdevice"), i18n("Symbol Viewer"));
    tv->setObjectName("SymbolViewer-ToolView");
    SymbolViewer::self(tv);
#endif

    Oscilloscope::addOscilloscopeAsToolView(this);
#if 1
    tv = createToolView(ScopeScreen::toolViewIdentifier(), KMultiTabBar::Bottom, QIcon::fromTheme("oscilloscope"), i18n("Scope Screen (Very Rough)"));
    tv->setObjectName("ScopeScreen-ToolView");
    ScopeScreen::self(tv);
#endif

    updateSidebarMinimumSizes();
}

void ReadySpice::setupView()
{
}

void ReadySpice::setupTabWidget()
{
    m_pViewContainerTabWidget = new QTabWidget(centralWidget());

    if (centralWidget()->layout())
    {
        centralWidget()->layout()->addWidget(m_pViewContainerTabWidget);
    }
    else
    {
        qCWarning(RDV_LOG) << " disposition nulle inattendue pour " << centralWidget();
    }

    connect(tabWidget(), &QTabWidget::currentChanged, this, &ReadySpice::slotViewContainerActivated);

    KSharedConfigPtr cfg = KSharedConfig::openConfig();
    KConfigGroup grUi = cfg->group("UI");

    bool CloseOnHover = grUi.readEntry("CloseOnHover", false);
    tabWidget()->setTabsClosable(CloseOnHover);

    bool CloseOnHoverDelay = grUi.readEntry("CloseOnHoverDelay", false);
    tabWidget()->setTabsClosable(CloseOnHoverDelay);

    if (grUi.readEntry("ShowCloseTabsButton", true))
    {
        QToolButton *but = new QToolButton(tabWidget());
        but->setIcon(QIcon::fromTheme("tab-close"));
        but->adjustSize();
        but->hide();
        connect(but, &QToolButton::clicked, this, &ReadySpice::slotViewContainerClose);
        tabWidget()->setCornerWidget(but, Qt::TopRightCorner);
    }

    QTabBar *tabBar = tabWidget()->tabBar();
    tabBar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tabBar, &QTabBar::customContextMenuRequested, this, &ReadySpice::slotTabContext);
}

void ReadySpice::readPropertiesInConfig(KConfig *conf)
{
}

void ReadySpice::slotTabContext(const QPoint &pos)
{
    QTabBar *tabBar = tabWidget()->tabBar();
    QWidget *widget = tabWidget()->widget(tabBar->tabAt(pos));
    if (!widget)
    {
        return;
    }
    const QPoint globalPos = tabBar->mapToGlobal(pos);

    QMenu *tabMenu = new QMenu;
    tabMenu->addSection((dynamic_cast<ViewContainer *>(widget))->windowTitle());

    m_pContextMenuContainer = nullptr;

    m_viewContainerList.removeAll(static_cast<ViewContainer *>(nullptr));

    const ViewContainerList::iterator vcEnd = m_viewContainerList.end();
    for (ViewContainerList::iterator it = m_viewContainerList.begin(); it != vcEnd; ++it)
    {
        ViewContainer *viewContainer = *it;
        if (viewContainer == widget)
        {
            m_pContextMenuContainer = viewContainer;

            tabMenu->addAction(QIcon::fromTheme("tab-close"), i18n("Close"))->setData(0);

            View *view = (viewContainer->viewCount() == 1) ? viewContainer->activeView() : nullptr;

            if (view && view->document()->isModified())
                tabMenu->addAction(QIcon::fromTheme("document-save"), i18n("Save"))->setData(1);

            if (view && !view->document()->url().isEmpty())
                tabMenu->addAction(QIcon::fromTheme("view-refresh"), i18n("Reload"))->setData(2);

            if (m_viewContainerList.count() > 1)
                tabMenu->addAction(QIcon::fromTheme("tab-close-other"), i18n("Close All Others"))->setData(4);
        }
    }

    connect(tabMenu, &QMenu::triggered, this, &ReadySpice::slotTabContextActivated);

    tabMenu->exec(globalPos);
    delete tabMenu;
}

void ReadySpice::slotUpdateCaptions()
{
}

void ReadySpice::slotViewContainerActivated(int /*index*/)
{
    QWidget *viewContainer = m_pViewContainerTabWidget->currentWidget();
    if (!viewContainer)
    {
        return;
    }
    m_pFocusedContainer = dynamic_cast<ViewContainer *>(viewContainer);
    m_pFocusedContainer->setFocus();
}

void ReadySpice::slotViewContainerClose()
{
    if (m_pFocusedContainer)
        m_pFocusedContainer->closeViewContainer();
}

void ReadySpice::slotTabContextActivated(QAction *action)
{
}
