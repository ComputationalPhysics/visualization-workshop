#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "diffusion.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<Diffusion>("Workshop", 1, 0, "Diffusion");

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
