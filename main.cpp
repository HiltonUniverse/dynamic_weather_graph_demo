#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>


#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));




    //Making HTTP request and fetching the weather API data
    QNetworkAccessManager networkManager;

    QUrl url("http://api.openweathermap.org/data/2.5/forecast/daily?q=leuven,0032&cnt=10&appid=fe37c3d28a6ebb417f52c05d92b28383");
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply* reply = networkManager.get(request);  // GET

    //Wait for the signal of QNetworkRepl,
    //connect(sender,signal,receiver) ... receiver in this case is a lambda expression
    //[=] means capture all variable by value, () is where we send parameter from
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        reply->abort();
        try {
            if(reply->error() == QNetworkReply::NoError)
            {
                QByteArray response = reply->readAll();
                // do something with the data...

                std::cout<< "The size is: "<< response.toStdString() <<std::endl;

            }
        }
        catch (const std::exception& e) {
            std::cout << e.what();
       }

    });


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
