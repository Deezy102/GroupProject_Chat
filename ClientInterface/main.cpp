/**
* \file
* \brief Данный файл отвечает за реализацию main'а клиента
*
*/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickView>
#include <QQmlProperty>
#include "client.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Client client;


    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("client", &client);
    //context->setContextProperty("chttext", "jopaq23r42");

    QQuickView view;
    view.engine()->rootContext()->setContextProperty("client", &client);
    view.setSource(QUrl::fromLocalFile("ChatPage.qml"));



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
