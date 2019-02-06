#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include "weather.h"
#include <QDebug>

#include "weatherJasonParser.h"
#include <iostream>
#include "weather.h"
#include <QQmlContext>

namespace
{
    const QString URL = "http://api.openweathermap.org/data/2.5/forecast/daily?q=leuven,0032&cnt=10&appid=fe37c3d28a6ebb417f52c05d92b28383";
}


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    WeatherJsonParser parser("leuven",&app);


    //Inject the cpp object into the qml file
    engine.rootContext()->setContextProperty("weatherInformation", &parser);

//    qmlRegisterType<weather::Weather>("weather.h",1,0,"Weather");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
