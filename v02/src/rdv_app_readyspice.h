#pragma once

#include "rdv_app_main_window.h"

class ViewArea;

class ReadySpice : public KateMDI::MainWindow
{
    Q_OBJECT

public:
    explicit ReadySpice(QWidget *parent = nullptr);
    ~ReadySpice() override;

private:
    void loadInternal(const QUrl &url, bool isRecent, ViewArea *viewArea = nullptr);

public slots:
    void load(const QUrl &url, ViewArea *viewArea = nullptr);
    void addRecentFile(const QUrl &url);
};
