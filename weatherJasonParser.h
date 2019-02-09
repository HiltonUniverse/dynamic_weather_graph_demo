#ifndef JSONOBJECTFACTOR_H
#define JSONOBJECTFACTOR_H
#include "weather.h"

#include <QString>
#include <QObject>
#include <QJsonObject>

class JsonFetch;

class WeatherJsonParser: public QObject
{
    Q_OBJECT

signals:
    void parseCompleted(weather::Weather);

private slots:
    void fetchWeatheJson(QJsonObject weatherObject);

public:
    WeatherJsonParser(const QString & cityName,QObject* parent=nullptr);

private:
    JsonFetch* m_json_fetch;

};

#endif // JSONOBJECTFACTOR_H
