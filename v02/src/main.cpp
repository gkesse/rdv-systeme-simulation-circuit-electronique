#include "rdv_app_readyspice.h"

int main(int _argc, char **_argv)
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);

    QApplication app(_argc, _argv);
    qDebug() << "Démarrage de l'application...";

    KLocalizedString::setApplicationDomain("readyspice");

    KAboutData about(
        "readyspice",
        i18n("ReadySpice"),
        READYSPICE_VERSION_STRING,
        i18n("Système de simulation de circuits électroniques."),
        KAboutLicense::GPL_V2,
        i18n("(C) 2024-2024 | Développeurs ReadySpice"),
        "",
        "https://readydev.ovh/home",
        "readydev.team@outlook.com");

    about.addAuthor(
        i18n("Gerard KESSE"),
        i18n("Développeur, ReadySpice"),
        "readydev.team@outlook.com");

    about.addCredit(
        i18n("ReadyDev"),
        i18n("Site Web, Cours et Tutoriels, Plateforme de développement continu"),
        "readydev.team@outlook.com");

    KAboutData::setApplicationData(about);
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("readydev")));

    QCommandLineParser parser;

    about.setupCommandLine(&parser);

    parser.addPositionalArgument(
        QStringLiteral("url"),
        i18n("Document à ouvrir."),
        QStringLiteral("[url]"));

    parser.process(app);
    about.processCommandLine(&parser);

    const QStringList iconDirs = QStandardPaths::locateAll(
        QStandardPaths::GenericDataLocation,
        "readyspice/icons",
        QStandardPaths::LocateDirectory);

    const QStringList picsDirs = QStandardPaths::locateAll(
        QStandardPaths::GenericDataLocation,
        "readyspice/pics",
        QStandardPaths::LocateDirectory);

    QIcon::setThemeSearchPaths(QIcon::themeSearchPaths() << iconDirs);
    QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << iconDirs << picsDirs);

    ReadySpice *readyspice = new ReadySpice;

    if (parser.positionalArguments().count() > 0)
    {
        const QUrl url = QUrl::fromUserInput(
            parser.positionalArguments().at(0),
            QDir::currentPath(),
            QUrl::AssumeLocalFile);
        readyspice->load(url);
    }

    readyspice->show();
    return app.exec();
}
