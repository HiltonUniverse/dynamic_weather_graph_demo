#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>

#include "weatherJasonParser.h"
#include <iostream>

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


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
