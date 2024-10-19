#pragma once

#include "rdv_app_include.h"

class Subcircuits : public QObject
{
    Q_OBJECT
public:
    Subcircuits();
    ~Subcircuits() override;
    static Subcircuits *subcircuits();
    static void loadSubcircuits();

private:
    static QList<int> asIntList(const QString &string);
    static QString genFileName(const int nextId);
    static void updateComponentSelector(int id, const QString &name);
};
