#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "waves.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<Waves>("Workshop", 1, 0, "Waves");

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
