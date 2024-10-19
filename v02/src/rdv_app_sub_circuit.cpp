#include "rdv_app_sub_circuit.h"
#include "rdv_app_component_selector.h"

Subcircuits::Subcircuits()
    : QObject()
{
}

Subcircuits::~Subcircuits()
{
}

Subcircuits *Subcircuits::subcircuits()
{
    static Subcircuits *_subcircuits = new Subcircuits();
    return _subcircuits;
}

void Subcircuits::loadSubcircuits()
{
    KSharedConfigPtr config = KSharedConfig::openConfig();
    KConfigGroup configGrSubcirc = config->group("Subcircuits");

    QList<int> idList = asIntList(configGrSubcirc.readEntry<QString>(QString("Ids"), QString()));
    const QList<int>::iterator idListEnd = idList.end();
    for (QList<int>::iterator it = idList.begin(); it != idListEnd; ++it)
    {
        QFile file(genFileName(*it));
        if (file.open(QIODevice::ReadOnly) == false)
        {
            *it = -1;
        }
        else
        {
            KConfigGroup configGrSubcNr = config->group("Subcircuit_" + QString::number(*it));
            updateComponentSelector(*it, configGrSubcNr.readEntry("Name"));
        }
        file.close();
    }
    idList.removeAll(-1);

    configGrSubcirc.writeEntry("Ids", idList);
}

QList<int> Subcircuits::asIntList(const QString &string)
{
    QList<QByteArray> entries = string.toLatin1().split(',');
    QList<int> list;
    for (const QByteArray &s : entries)
        list << s.toInt();
    return list;
}

QString Subcircuits::genFileName(const int nextId)
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/subcircuit_" + QString::number(nextId) + ".circuit";
}

void Subcircuits::updateComponentSelector(int id, const QString &name)
{
    if (name.isEmpty())
        return;

    ComponentSelector::self()->addItem(name, "sc/" + QString::number(id), i18n("Subcircuits"), QIcon::fromTheme("application-x-circuit"), true);
}
