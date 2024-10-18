#pragma once

#include "rdv_app_include.h"

class ItemSelector : public QTreeWidget
{
    Q_OBJECT

public:
    explicit ItemSelector(QWidget *parent = nullptr);
    ~ItemSelector() override;

protected:
    void setListCaption(const QString &caption);
    QTreeWidgetItem *selectedItem() const;

public slots:
    virtual void slotContextMenuRequested(const QPoint &pos);

private slots:
    void slotItemSelected();

signals:
    void itemRemoved(const QString &id);
    void itemDoubleClicked(const QString &id);
    void itemClicked(const QString &id);
    void itemSelected(const QString &id);
};
