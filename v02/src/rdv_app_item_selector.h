#pragma once

#include "rdv_app_include.h"

class ItemSelector : public QTreeWidget
{
    Q_OBJECT

public:
    explicit ItemSelector(QWidget *parent = nullptr);
    ~ItemSelector() override;
    void addItem(const QString &caption, const QString &id, const QString &category, const QIcon &icon = QIcon(), bool removable = false);

protected:
    void setListCaption(const QString &caption);
    QTreeWidgetItem *selectedItem() const;
    bool readOpenState(const QString &id);

public slots:
    virtual void slotContextMenuRequested(const QPoint &pos);

private slots:
    void slotItemSelected();

signals:
    void itemRemoved(const QString &id);
    void itemDoubleClicked(const QString &id);
    void itemClicked(const QString &id);
    void itemSelected(const QString &id);

private:
    QStringList m_categories;
};
