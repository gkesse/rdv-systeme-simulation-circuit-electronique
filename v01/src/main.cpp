#include "rdv_app_main_window.h"

int main(int _argc, char **_argv)
{
    QApplication app(_argc, _argv);
    qDebug() << "Démarrage de l'application...";

    // QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);

    ReadySpice *mainWindow = new ReadySpice;
    mainWindow->show();
    return app.exec();
}
