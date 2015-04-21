#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//    QQuickView view;
//    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
//    view.show();

    return app.exec();
}
