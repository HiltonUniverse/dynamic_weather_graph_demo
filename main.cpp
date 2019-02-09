#include "weather.h"
#include "weatherJasonParser.h"
#include "chartmodel.h"

#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QDebug>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ChartModel chartModel(&app);

    //Inject the cpp object into the qml file -> one time instantiate to all QML
//    engine.rootContext()->setContextProperty("cpp_chart_model", &chartModel);
    qmlRegisterType<ChartModel>("MainLib",1,0,"ChartModel");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
